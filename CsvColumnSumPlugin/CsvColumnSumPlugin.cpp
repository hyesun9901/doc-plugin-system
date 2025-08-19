#include "pch.h"
#include <iostream>
#include <vector>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include "CsvColumnSumPlugin.h"

bool CCsvColumnSumPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == "csv";
}

int CCsvColumnSumPlugin::execute(CDocument& doc)
{
	auto& csv = dynamic_cast<CCsvDocument&>(doc);
	const auto& rows = csv.get_rows();

	if (rows.empty()) 
	{
		std::cout << "[" << __FUNCTION__ << "] " << doc.get_path() << " is empty file\n";
		return ERROR_INVALID_DATA;
	}

	double sum = 0.0;
	size_t start = m_bisHasHeader ? 1 : 0;

	for (size_t i = start; i < rows.size(); ++i)
	{
		if (m_col >= rows[i].size())
		{
			std::cerr << "[" << __FUNCTION__ << "] " <<" Row " << i << " has insufficient columns\n";
			continue;
		}

		const std::string& cell = rows[i][m_col];
		try {
			sum += std::stod(cell);
		}
		catch (const std::exception& e) {
			std::cerr << "[" << __FUNCTION__ << "] "<< "Invalid number at row " << i << ", col " << m_col << ": " << cell << "\n";
		}
	}

	std::cout <<  "["<< __FUNCTION__ << "] " << doc.get_path() << " col#" << m_col << " -> sum=" << sum << "\n";
	
	return ERROR_SUCCESS;
}

std::string CCsvColumnSumPlugin::get_plugin_name() const
{
	return "CsvColumnSumPlugin";
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {

	wchar_t szDllPath[MAX_PATH] = {};
	if (!GetModuleFileNameW(nullptr, szDllPath, MAX_PATH)) 
	{
		return nullptr;
	}

	PathRemoveFileSpec(szDllPath);
	wchar_t szInIFullPath[MAX_PATH] = { 0, };
	const wchar_t* pszIniPath = L"CsvColumnSumPlugin.ini";
	swprintf_s(szInIFullPath, MAX_PATH, L"%s\\%s", szDllPath, pszIniPath);

	int column_index = GetPrivateProfileIntW(L"CsvColumnSumPlugin", L"column_index", 0, szInIFullPath);
	
	wchar_t buffer[16] = {};
	GetPrivateProfileStringW(L"CsvColumnSumPlugin", L"has_header", L"true", buffer, 16, szInIFullPath);
	
	bool has_header = (_wcsicmp(buffer, L"true") == 0 || _wcsicmp(buffer, L"1") == 0);

	return new CCsvColumnSumPlugin(static_cast<size_t>(column_index), has_header);
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}