#include "pch.h"
#include "JsonValidationPlugin.h"
#include <iostream>
#include <json/json.h>
#include <codecvt>
bool CJsonValidationPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == L"json";
}

int CJsonValidationPlugin::execute(CDocument& doc)
{
	auto& json = dynamic_cast<CJsonDocument&>(doc);
	bool bJsonValid = is_json_valid(json.get_content());
	if (true == bJsonValid)
	{
		std::cout << "[" << __FUNCTION__ << "] " << "Success to JsonValidation!!\n";
		return ERROR_SUCCESS;
	}
	else
	{
		std::cout << "[" << __FUNCTION__ << "] " << "Failed to JsonValidation..\n";
		return ERROR_INVALID_DATA;
	}

}

std::wstring CJsonValidationPlugin::get_plugin_name() const
{
	return L"JsonValidationPlugin";
}

std::string to_utf8(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstr);
}

bool CJsonValidationPlugin::is_json_valid(const std::wstring& strContent)
{
	Json::CharReaderBuilder builder;
	std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

	Json::Value root;
	std::string strErrors;

	bool bJsonValid = false;
	std::string strCopyContent = to_utf8(strContent);
	bJsonValid = reader->parse(strCopyContent.c_str(), strCopyContent.c_str() + strCopyContent.length(), &root, &strErrors);
	return bJsonValid;
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {
	return new CJsonValidationPlugin();
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}