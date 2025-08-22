#include "pch.h"
#include "WordCountPlugin.h"
#include <iostream>
#include <string>

bool CWordCountPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == L"txt";
}

size_t CWordCountPlugin::word_count(const std::wstring& wstrContent)
{
    size_t cnt = 0;
    bool bInWord = false;
    for (unsigned char ch : wstrContent)
    {
        if (std::isalnum(ch)) 
        {
            if (false == bInWord)
            { 
                bInWord = true; 
                ++cnt;
            }
        }
        else
        {
            bInWord = false;
        }
    }
    std::cout << "[" << __FUNCTION__ << "] " << "word count is " << cnt << std::endl;
    return cnt;
}

int CWordCountPlugin::execute(CDocument& doc)
{
	auto& txt = dynamic_cast<CTxtDocument&>(doc);
    size_t wc = word_count(txt.get_content());
    return wc;
}

std::wstring CWordCountPlugin::get_plugin_name() const
{
    return L"WordCountPlugin";
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {
	return new CWordCountPlugin();
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}