#include "pch.h"
#include "JsonKeyValuePrint.h"
#include <json/json.h>
#include <iostream>
#include <codecvt>

bool CJsonKeyValuePrint::is_supported(CDocument& doc) const
{
	return doc.get_type() == L"json";
}

int CJsonKeyValuePrint::execute(CDocument& doc)
{
	auto& json = dynamic_cast<CJsonDocument&>(doc);
	bool bPrint = print_key_value(json.get_content());
	if (true == bPrint)
	{
		std::cout << "[" << __FUNCTION__ << "] " << "Success to Print Json Key Value!!\n";
		return ERROR_SUCCESS;
	}
	else
	{
		std::cout << "[" << __FUNCTION__ << "] " << "Failed to Print Json Key Value..\n";
		return ERROR_INVALID_DATA;
	}

}

std::wstring CJsonKeyValuePrint::get_plugin_name() const
{
	return L"JsonKeyValuePrint";
}

std::string to_utf8(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstr);
}

bool CJsonKeyValuePrint::print_key_value(const std::wstring& strJson)
{
	Json::CharReaderBuilder readerBuilder;
	Json::Value root;
	std::string errs;


	std::string strJsonCopy = to_utf8(strJson);
	std::istringstream iss(strJsonCopy);
	if (false == Json::parseFromStream(readerBuilder, iss, &root, &errs)) 
	{
		std::cerr << "[" << __FUNCTION__ << "] " << "Failed to parse JSON: " << errs << std::endl;
		return false;
	}

	// Key-Value Ãâ·Â
	for (const auto& key : root.getMemberNames()) {
		const Json::Value& value = root[key];
		if (value.isString()) {
			std::cout << key << " : " << value.asString() << std::endl;
		}
		else if (value.isInt()) {
			std::cout << key << " : " << value.asInt() << std::endl;
		}
		else if (value.isDouble()) {
			std::cout << key << " : " << value.asDouble() << std::endl;
		}
		else if (value.isBool()) {
			std::cout << key << " : " << (value.asBool() ? "true" : "false") << std::endl;
		}
		else if (value.isObject()) {
			std::cout << key << " : (object)" << std::endl;
		}
		else if (value.isArray()) {
			std::cout << key << " : (array)" << std::endl;
		}
		else if (value.isNull()) {
			std::cout << key << " : null" << std::endl;
		}
	}

	return true;
}

extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {
	return new CJsonKeyValuePrint();
}

extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
	delete p;
}