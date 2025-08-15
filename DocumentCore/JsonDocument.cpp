#include "pch.h"
#include "JsonDocument.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

CJsonDocument::CJsonDocument(const std::string& path) :CDocument(path)
{
    std::ifstream ifs(path);
    if (!ifs)
    {
        throw std::runtime_error("Failed to open Json: " + path);
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();
    m_strJsonText = oss.str();
}

std::string CJsonDocument::get_type() const
{
    return "json";
}
