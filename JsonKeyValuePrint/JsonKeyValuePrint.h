#pragma once
#ifdef JSONKEYVALUEPRINT_EXPORTS
#define KEYVALUEPRINT_API __declspec(dllexport)
#else
#define KEYVALUEPRINT_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/JsonDocument.h"

//Json������ key value ���·� ������ִ� �÷�����
class CJsonKeyValuePrint : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::wstring get_plugin_name() const override;

private:
	bool print_key_value(const std::wstring& strContent);
};

