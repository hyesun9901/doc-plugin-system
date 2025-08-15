#pragma once
#include "Document.h"
class CJsonDocument : public CDocument
{
public:
    explicit CJsonDocument(const std::string& path);
    std::string get_type() const override;
    std::string& get_content() { return m_strJsonText; }

private:
    std::string m_strJsonText;
};
