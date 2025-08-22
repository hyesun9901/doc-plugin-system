#include "pch.h"
#include "JsonDocument.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <codecvt>
CJsonDocument::CJsonDocument(const std::wstring& wstrPath) :CDocument(wstrPath)
{
    std::wifstream ifs(wstrPath);
    if (!ifs)
    {
        throw std::runtime_error("Failed to open Json: " + to_utf8(wstrPath));
    }

    std::wostringstream oss;
    oss << ifs.rdbuf();
    m_wstrJsonText = oss.str();
}

std::wstring CJsonDocument::get_type() const
{
    return L"json";
}

std::string CJsonDocument::to_utf8(const std::wstring& wstrInput)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstrInput);
}