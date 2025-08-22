#pragma once
#include "Document.h"
class CJsonDocument : public CDocument
{
public:
    explicit CJsonDocument(const std::wstring& wstrPath);
    std::wstring get_type() const override;
    std::wstring& get_content() { return m_wstrJsonText; }

private:
    std::wstring m_wstrJsonText;
    std::string to_utf8(const std::wstring& wstr);
};
