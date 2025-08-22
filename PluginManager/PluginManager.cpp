// PluginManager.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <filesystem>
#include <memory>
#include <windows.h>
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include "PluginManager.h"
#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/DocumentCore.h"

using CreateFn  = IPlugin* (*)();
using DestroyFn = void     (*)(IPlugin*);

void CPluginManager::register_plugin_all(const std::wstring& wstrFolder)
{
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((wstrFolder + L"\\*.dll").c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) return;

	do {
		std::wstring strDllPath = wstrFolder + L"\\" + findData.cFileName;
		HMODULE hModule = LoadLibraryW(strDllPath.c_str());
		if (!hModule)
			continue;

		auto create = reinterpret_cast<CreateFn>(GetProcAddress(hModule, "CreatePlugin"));
		auto destroy = reinterpret_cast<DestroyFn>(GetProcAddress(hModule, "DestroyPlugin"));
		if (!create || !destroy)
		{
			FreeLibrary(hModule);
			continue;
		}

		IPlugin* raw = create();
		std::shared_ptr<IPlugin> sp(raw, [destroy](IPlugin* q) { destroy(q); });
		m_vecPlugins.push_back({ hModule, std::move(sp), destroy });

		std::wcout << L"[" << __FUNCTION__ << L"] "<< L"Plugin loaded: " << findData.cFileName << std::endl;

	} while (FindNextFileW(hFind, &findData));

	FindClose(hFind);
}

void CPluginManager::register_plugin(const std::wstring& wstrFolder)
{
	std::wstring wstrIniPath = wstrFolder + L"\\plugins.ini";
	WCHAR szBuffer[MAX_PATH]{ 0, };

	for (int i = 1;; ++i)
	{
		std::wstring wstrIniKey = L"Plugin" + std::to_wstring(i);
		DWORD dwLen = GetPrivateProfileStringW(L"Plugins", wstrIniKey.c_str(), nullptr, szBuffer, sizeof(szBuffer) / sizeof(wchar_t), wstrIniPath.c_str());
		if (dwLen == 0)
			break; // 더 이상 항목 없음

		std::wstring wstrDllPath = wstrFolder + L"\\" + szBuffer;

		HMODULE hModule = LoadLibraryW(wstrDllPath.c_str());
		if (!hModule)
			continue;

		auto create = reinterpret_cast<CreateFn>(GetProcAddress(hModule, "CreatePlugin"));
		auto destroy = reinterpret_cast<DestroyFn>(GetProcAddress(hModule, "DestroyPlugin"));
		if (!create || !destroy)
		{
			FreeLibrary(hModule);
			continue;
		}

		IPlugin* iplugin = create();
		std::shared_ptr<IPlugin> sp(iplugin, [destroy](IPlugin* q) { destroy(q); });
		m_vecPlugins.push_back({ hModule, std::move(sp), destroy });

		std::wcout <<L"[" << __FUNCTION__ << L"] " << szBuffer << std::endl;
	}
}

void CPluginManager::run_plugins_for_document(CDocument& doc)
{
	std::wcout << "["<<__FUNCTION__<<"] " << doc.get_path() << " (doc type = " << doc.get_type() << ") \n";
	bool bAnyPlugin = false;
	for (auto& p : m_vecPlugins) 
	{
		auto& plug = p.inst;
		if (p.inst->is_supported(doc)) 
		{
			bAnyPlugin = true;
			try {
				int nResult = p.inst->execute(doc);
				std::wcout << "[" << __FUNCTION__ << "] " << p.inst->get_plugin_name() <<"result = " << nResult << std::endl;
			}
			catch (const std::exception& e) {
				std::wcerr << "[" << __FUNCTION__ << "] "<< "[ERROR] " << p.inst->get_plugin_name() << ": " << e.what() << "\n";
			}
			catch (...) {
				std::wcerr << "[" << __FUNCTION__ << "] "<< "[ERROR] " << p.inst->get_plugin_name() << ": unknown error\n";
			}
		}
	}

	if (false == bAnyPlugin) 
	{
		std::cout << "Not exist compatible plugins...\n";
	}
}

int main()
{
	try {
		WCHAR szPath[MAX_PATH] = { 0, };
		GetModuleFileNameW(nullptr, szPath, MAX_PATH);
		PathRemoveFileSpecW(szPath); 
		std::wstring strModuleFolderPath = szPath;

		CPluginManager pm;
		pm.register_plugin(strModuleFolderPath); //현재 실행파일exe의 폴더를 등록
		//pm.register_plugin_all(strModuleFolderPath);
		
		CTxtDocument  txt(strModuleFolderPath + L"\\sample.txt");
		CJsonDocument json(strModuleFolderPath + L"\\sample.json");
		CCsvDocument csv(strModuleFolderPath + L"\\sample.csv");

		pm.run_plugins_for_document(txt);
		pm.run_plugins_for_document(json);
		pm.run_plugins_for_document(csv);
	}
	catch (const std::exception& e) {
		std::wcerr << "[ERROR] " << e.what() << std::endl;;
		return 1;
	}
	/*std::string strStop;
	std::cin >> strStop;*/
}