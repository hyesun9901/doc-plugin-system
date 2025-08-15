#pragma once

#include <string>
#include <vector>
#include "Document.h"

class CCsvDocument : public CDocument
{
public:
    explicit CCsvDocument(const std::string& path, char delimiter = ',');
    std::string get_type() const override;

    const std::vector<std::vector<std::string>>& get_rows() const;

private:
    char  m_szDelimiter;
    std::vector<std::vector<std::string>> m_vecRows;
};