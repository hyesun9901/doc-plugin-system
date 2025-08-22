#include "pch.h"
#include "CsvDocument.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

CCsvDocument::CCsvDocument(const std::wstring& wstrPath, wchar_t szDelimiter /*= ','*/)
    : CDocument(wstrPath), m_szDelimiter(szDelimiter)
{
    std::wifstream ifs(wstrPath);
    std::wstring strLine;
    if (ifs.is_open()) 
    {
        while (std::getline(ifs, strLine))
        {
            std::wstringstream ss(strLine);
            std::wstring strField;
            std::vector<std::wstring> vecFields;

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

const std::vector<std::vector<std::wstring>>& CCsvDocument::get_rows() const
{
    return m_vecRows;
}

std::wstring CCsvDocument::get_type() const 
{
    return L"csv";
}
