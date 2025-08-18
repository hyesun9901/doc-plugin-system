#pragma once
#ifdef JSONVALIDATION_EXPORTS
#define JSONVALIDATION_API __declspec(dllexport)
#else
#define JSONVALIDATION_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/JsonDocument.h"

class JSONVALIDATION_API CJsonValidationPlugin : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::string get_plugin_name() const override;

private:
	bool is_json_valid(const std::string& strContent);
};

