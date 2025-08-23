#pragma once
#ifdef WORDCOUNT_EXPORTS
#define WORDCOUNT_API __declspec(dllexport)
#else
#define WORDCOUNT_API __declspec(dllimport)
#endif
#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/TxtDocument.h"

//Txt파일의 단어 수를 검증해주는 플러그인 EX)"hi hi"의 경우 단어 2개이므로 word_count함수는 2를 리턴
class CWordCountPlugin : public IPlugin
{
public:
    bool is_supported(CDocument& doc) const override;
    int execute(CDocument& doc) override;
    std::wstring get_plugin_name() const override;

private:
    static size_t word_count(const std::wstring& wstrContent);
};