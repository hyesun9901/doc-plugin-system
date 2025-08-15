#include "pch.h"
#include "TxtDocument.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

CTxtDocument::CTxtDocument(const std::string& path) :CDocument(path)
{
    std::ifstream ifs(path);
    if (!ifs)
    {
        throw std::runtime_error("Failed to open TXT: " + path);
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();
    m_content = oss.str();
}

std::string CTxtDocument::get_type() const
{
    return "txt";
}
