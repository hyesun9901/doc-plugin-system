#pragma once
#ifdef JSONKEYVALUEPRINT_EXPORTS
#define KEYVALUEPRINT_API __declspec(dllexport)
#else
#define KEYVALUEPRINT_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/JsonDocument.h"

class KEYVALUEPRINT_API CJsonKeyValuePrint : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::string get_plugin_name() const override;

private:
	bool print_key_value(const std::string& strContent);
};

