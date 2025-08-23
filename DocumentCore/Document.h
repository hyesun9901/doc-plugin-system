#pragma once
#include <string>
#ifdef DOCUMENTCORE_EXPORTS
#define DOCUMENTCORE_API __declspec(dllexport)
#else
#define DOCUMENTCORE_API __declspec(dllimport)
#endif
class  DOCUMENTCORE_API CDocument {
public:
    explicit CDocument(std::wstring wstrPath) : m_wstrPath(std::move(wstrPath)) {}
    virtual ~CDocument() = default;
    virtual std::wstring get_type() const = 0; //txt,json,csv µîµî
    
    const std::wstring& get_path() const { return m_wstrPath; }

private:
    std::wstring m_wstrPath;
};