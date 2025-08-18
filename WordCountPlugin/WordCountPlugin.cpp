#include "pch.h"
#include "WordCountPlugin.h"
#include <string>

bool CWordCountPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == "txt";
}

size_t CWordCountPlugin::word_count(const std::string& strContent)
{
    size_t cnt = 0;
    bool bInWord = false;
    for (unsigned char ch : strContent)
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
    return cnt;
}

int CWordCountPlugin::execute(CDocument& doc)

{
	auto& txt = dynamic_cast<CTxtDocument&>(doc);
    size_t wc = word_count(txt.get_content());
    //TODO: �α׷� ������ֱ�
    //TODO:�������̽����� get_version �ʿ��ҵ�
    return wc;
}

std::string CWordCountPlugin::get_plugin_name() const
{
    return "WordCountPlugin";
}
