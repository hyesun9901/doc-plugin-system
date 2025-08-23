#pragma once
#ifdef JSONKEYVALUEPRINT_EXPORTS
#define KEYVALUEPRINT_API __declspec(dllexport)
#else
#define KEYVALUEPRINT_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/JsonDocument.h"

//Json파일을 key value 형태로 출력해주는 플러그인
class CJsonKeyValuePrint : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::wstring get_plugin_name() const override;

private:
	bool print_key_value(const std::wstring& strContent);
};

