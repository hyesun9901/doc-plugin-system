#include "Document.h"
class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual bool is_supported(CDocument& doc) const = 0;
    virtual void execute(CDocument& doc) = 0;
};