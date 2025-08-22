#include "pch.h"
#include "EncryptionPlugin.h"
#include <fstream>

bool CEncryptionPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == L"txt";
}

int CEncryptionPlugin::execute(CDocument& doc)
{
	auto& txt = dynamic_cast<CTxtDocument&>(doc);
	std::wstring wstrEncypt = rot13(txt.get_content());
	// 실제로 덮어쓸지/별도 저장할지

	std::wstring wstrOutPath = doc.get_path() + L".rot13.txt";
	std::wofstream ofs(wstrOutPath);
	ofs << wstrEncypt;
	//std::cout << "[Encrypt ROT13] " << doc.get_path() << " -> saved: " << outPath << "\n";
	return ERROR_SUCCESS;
}

std::wstring CEncryptionPlugin::get_plugin_name() const
{
	return L"EncryptionPlugin";
}

std::wstring CEncryptionPlugin::rot13(const std::wstring& wstrContent)
{
	std::wstring wstrOutput = wstrContent;
	for (wchar_t& c : wstrOutput) 
	{
		if ('a' <= c && c <= 'z') c = 'a' + (c - 'a' + 13) % 26;
		else if ('A' <= c && c <= 'Z') c = 'A' + (c - 'A' + 13) % 26;
	}

	return wstrOutput;
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {
	return new CEncryptionPlugin();
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}