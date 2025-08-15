#include "pch.h"
#include "CsvDocument.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

CCsvDocument::CCsvDocument(const std::string& path, char delimiter /*= ','*/)
    : CDocument(path), m_szDelimiter(delimiter)
{
    std::ifstream ifs(path);
    std::string strLine;
    if (ifs.is_open()) 
    {
        while (std::getline(ifs, strLine))
        {
            std::stringstream ss(strLine);
            std::string strField;
            std::vector<std::string> vecFields;

            while (std::getline(ss, strField, m_szDelimiter))
            {
                vecFields.push_back(strField);
            }

            m_vecRows.push_back(vecFields);
        }

        ifs.close();
    }
    else 
    {
        
    }
}

const std::vector<std::vector<std::string>>& CCsvDocument::get_rows() const
{
    return m_vecRows;
}

std::string CCsvDocument::get_type() const 
{
    return "csv";
}
