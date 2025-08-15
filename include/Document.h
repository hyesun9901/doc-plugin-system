#include <string>
class CDocument {
public:
    explicit CDocument(std::string path) : m_strPath(std::move(path)) {}
    virtual ~CDocument() = default;
    virtual std::string get_type() const = 0; //txt,json,csv µîµî
    
    const std::string& get_path() const { return m_strPath; }

private:
    std::string m_strPath;
};