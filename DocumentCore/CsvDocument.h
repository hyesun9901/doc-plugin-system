#pragma once

#include <string>
#include <vector>
#include "Document.h"

class CCsvDocument : public CDocument
{
public:
    CCsvDocument(const std::wstring& path, wchar_t delimiter = L',');
    std::wstring get_type() const override;

    const std::vector<std::vector<std::wstring>>& get_rows() const;

private:
    wchar_t  m_szDelimiter;
    std::vector<std::vector<std::wstring>> m_vecRows;
    std::string to_utf8(const std::wstring& wstr);
};