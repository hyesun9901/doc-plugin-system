#include "pch.h"
#include "TxtDocument.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <codecvt>


CTxtDocument::CTxtDocument(const std::wstring& wstrPath) :CDocument(wstrPath)
{
    std::wifstream ifs(wstrPath);
    if (!ifs)
    {
        throw std::runtime_error("Failed to open TXT: " + to_utf8(wstrPath));
    }

    std::wostringstream oss;
    oss << ifs.rdbuf();
    m_wstrContent = oss.str();
}

std::wstring CTxtDocument::get_type() const
{
    return L"txt";
}

std::string CTxtDocument::to_utf8(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstr);
}
