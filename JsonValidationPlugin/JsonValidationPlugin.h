#pragma once
#ifdef JSONVALIDATION_EXPORTS
#define JSONVALIDATION_API __declspec(dllexport)
#else
#define JSONVALIDATION_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/JsonDocument.h"

//Json 형식을 검증해주는 플러그인
class JSONVALIDATION_API CJsonValidationPlugin : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::wstring get_plugin_name() const override;

private:
	bool is_json_valid(const std::wstring& strContent);
};

