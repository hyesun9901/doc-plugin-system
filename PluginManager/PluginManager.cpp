// PluginManager.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <filesystem>
#include <memory>
#include <windows.h>
#include "PluginManager.h"
#include "Document.h"
#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/DocumentCore.h"

using CreateFn  = IPlugin* (*)();
using DestroyFn = void     (*)(IPlugin*);

void CPluginManager::register_plugin(const std::wstring& folder)
{
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((folder + L"\\*.dll").c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) return;

	do {
		std::wstring strDllPath = folder + L"\\" + findData.cFileName;
		HMODULE hModule = LoadLibraryW(strDllPath.c_str());
		if (!hModule)
			continue;

		auto create = reinterpret_cast<CreateFn>(GetProcAddress(hModule, "CreatePlugin"));
		auto destroy = reinterpret_cast<DestroyFn>(GetProcAddress(hModule, "DestroyPlugin"));
		if (!create || !destroy)
		{
			FreeLibrary(hModule); continue;
		}

		IPlugin* raw = create();
		std::shared_ptr<IPlugin> sp(raw, [destroy](IPlugin* q) { destroy(q); });
		m_vecPlugins.push_back({ hModule, std::move(sp), destroy });

		std::wcout << L"[Plugin] loaded: " << findData.cFileName << std::endl;

	} while (FindNextFileW(hFind, &findData));

	FindClose(hFind);
}

void CPluginManager::run_plugins_for_document(CDocument& doc)
{
	std::cout << "["<<__FUNCTION__<<"] " << doc.get_path() << " (doc type = " << doc.get_type() << ") \n";
	bool bAnyPlugin = false;
	for (auto& p : m_vecPlugins) 
	{
		auto& plug = p.inst;
		if (p.inst->is_supported(doc)) 
		{
			bAnyPlugin = true;
			try {
				int nResult = p.inst->execute(doc);
				std::cout << "[" << __FUNCTION__ << "] " << p.inst->get_plugin_name() <<"result = " << nResult << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "[ERROR] " << p.inst->get_plugin_name() << ": " << e.what() << "\n";
			}
			catch (...) {
				std::cerr << "[ERROR] " << p.inst->get_plugin_name() << ": unknown error\n";
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
		CPluginManager pm;
		pm.register_plugin(L"C:\\CppWorks\\SamsungMedisonPT\\DocumentPlugin\\x64\\Release");

		CTxtDocument  txt("sample.txt");
		CJsonDocument json("sample.json");
		CCsvDocument csv("sample.csv");

		pm.run_plugins_for_document(txt);
		pm.run_plugins_for_document(json);
		pm.run_plugins_for_document(csv);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;;
		return 1;
	}
	/*std::string strStop;
	std::cin >> strStop;*/
}