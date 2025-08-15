#pragma once
#include "Document.h"
class CTxtDocument : public CDocument 
{
public:
    explicit CTxtDocument(const std::string& path);
    std::string get_type() const override;
    std::string& get_content() { return m_content; }

private:
    std::string m_content;
};

