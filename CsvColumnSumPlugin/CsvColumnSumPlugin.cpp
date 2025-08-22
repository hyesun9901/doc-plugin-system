#include "pch.h"
#include <iostream>
#include <vector>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include "CsvColumnSumPlugin.h"

bool CCsvColumnSumPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == L"csv";
}

int CCsvColumnSumPlugin::execute(CDocument& doc)
{
	auto& csv = dynamic_cast<CCsvDocument&>(doc);
	const auto& rows = csv.get_rows();

	if (rows.empty()) 
	{
		std::wcout << "[" << __FUNCTIONW__ << "] " << doc.get_path() << L" is empty file\n";
		return ERROR_INVALID_DATA;
	}

	double sum = 0.0;
	size_t start = m_bisHasHeader ? 1 : 0;

	for (size_t i = start; i < rows.size(); ++i)
	{
		if (m_col >= rows[i].size())
		{
			std::cerr << "[" << __FUNCTIONW__ << "] " <<" Row " << i << " has insufficient columns\n";
			continue;
		}

		const std::wstring& cell = rows[i][m_col];
		try {
			sum += std::stod(cell);
		}
		catch (const std::exception& e) {
			std::wcerr << "[" << __FUNCTIONW__ << "] "<< "Invalid number at row " << i << ", col " << m_col << ": " << cell << "\n";
		}
	}

	std::wcout <<  "["<< __FUNCTIONW__ << "] " << doc.get_path() << " column#" << m_col << " -> sum=" << sum << "\n";
	
	return ERROR_SUCCESS;
}

std::wstring CCsvColumnSumPlugin::get_plugin_name() const
{
	return L"CsvColumnSumPlugin";
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {

	WCHAR szDllPath[MAX_PATH] = {0,};
	if (!GetModuleFileNameW(nullptr, szDllPath, MAX_PATH)) 
	{
		return nullptr;
	}

	PathRemoveFileSpec(szDllPath);
	WCHAR szInIFullPath[MAX_PATH] = { 0, };
	const WCHAR* pszIniPath = L"CsvColumnSumPlugin.ini";
	swprintf_s(szInIFullPath, MAX_PATH, L"%s\\%s", szDllPath, pszIniPath);

	int nColumnIndex = GetPrivateProfileIntW(L"CsvColumnSumPlugin", L"column_index", 0, szInIFullPath);
	
	WCHAR szBuffer[16] = {};
	GetPrivateProfileStringW(L"CsvColumnSumPlugin", L"has_header", L"true", szBuffer, 16, szInIFullPath);
	
	bool bHasHeader = (_wcsicmp(szBuffer, L"true") == 0 || _wcsicmp(szBuffer, L"1") == 0);

	return new CCsvColumnSumPlugin(static_cast<size_t>(nColumnIndex), bHasHeader);
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}