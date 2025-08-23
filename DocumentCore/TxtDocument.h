#pragma once
#include "Document.h"
class DOCUMENTCORE_API CTxtDocument : public CDocument
{
public:
    explicit CTxtDocument(const std::wstring& wstrPath);
    std::wstring get_type() const override;
    std::wstring& get_content() { return m_wstrContent; }

private:
    std::string to_utf8(const std::wstring& wstr);
    std::wstring m_wstrContent;
};

