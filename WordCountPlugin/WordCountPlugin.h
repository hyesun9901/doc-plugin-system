#pragma once
#ifdef WORDCOUNT_EXPORTS
#define WORDCOUNT_API __declspec(dllexport)
#else
#define WORDCOUNT_API __declspec(dllimport)
#endif
#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/TxtDocument.h"

class WORDCOUNT_API CWordCountPlugin : public IPlugin
{
public:
    bool is_supported(CDocument& doc) const override;
    int execute(CDocument& doc) override;
    std::string get_plugin_name() const override;

private:
    static size_t word_count(const std::string& srrContent);
};