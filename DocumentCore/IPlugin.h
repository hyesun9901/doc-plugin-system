#pragma once
#include "Document.h"
class IPlugin {
public:
	virtual ~IPlugin() = default;
	virtual bool is_supported(CDocument& doc) const = 0;
	virtual int execute(CDocument& doc) = 0;
	virtual std::string get_plugin_name() const = 0;
};