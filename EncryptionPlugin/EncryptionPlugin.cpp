#include "pch.h"
#include "EncryptionPlugin.h"
#include <fstream>

bool CEncryptionPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == "txt";
}

int CEncryptionPlugin::execute(CDocument& doc)
{
	auto& txt = dynamic_cast<CTxtDocument&>(doc);
	std::string enc = rot13(txt.get_content());
	// 실제로 덮어쓸지/별도 저장할지

	std::string outPath = doc.get_path() + ".rot13.txt";
	std::ofstream ofs(outPath);
	ofs << enc;
	//std::cout << "[Encrypt ROT13] " << doc.get_path() << " -> saved: " << outPath << "\n";
	return ERROR_SUCCESS;
}

std::string CEncryptionPlugin::get_plugin_name() const
{
	return "EncryptionPlugin";
}

std::string CEncryptionPlugin::rot13(const std::string& s)
{
	std::string out = s;
	for (char& c : out) 
	{
		if ('a' <= c && c <= 'z') c = 'a' + (c - 'a' + 13) % 26;
		else if ('A' <= c && c <= 'Z') c = 'A' + (c - 'A' + 13) % 26;
	}
	return out;
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {
	return new CEncryptionPlugin();
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}