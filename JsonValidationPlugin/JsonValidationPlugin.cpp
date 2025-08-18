#include "pch.h"
#include "JsonValidationPlugin.h"
#include <json/json.h>

bool CJsonValidationPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == "json";
}

int CJsonValidationPlugin::execute(CDocument& doc)
{
	auto& json = dynamic_cast<CJsonDocument&>(doc);
	bool bJsonValid = is_json_valid(json.get_content());
	if (true == bJsonValid)
	{
		return ERROR_SUCCESS;
	}
	else
	{
		return ERROR_INVALID_DATA;
	}

}

std::string CJsonValidationPlugin::get_plugin_name() const
{
	return "JsonValidationPlugin";
}

bool CJsonValidationPlugin::is_json_valid(const std::string& strContent)
{
	Json::CharReaderBuilder builder;
	std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

	Json::Value root;
	std::string strErrors;

	bool bJsonValid = false;
	bJsonValid = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &strErrors);

	return bJsonValid;
}
