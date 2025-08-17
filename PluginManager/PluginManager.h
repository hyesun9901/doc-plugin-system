#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "../DocumentCore/IPlugin.h"

class CPluginManager 
{
public:
	void register_plugin(std::shared_ptr<IPlugin> p);
	void run_plugins_for_document(CDocument& doc);

private:
	std::vector<std::shared_ptr<IPlugin>> vec_Plugins;
};
