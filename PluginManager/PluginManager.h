#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "../DocumentCore/IPlugin.h"

class CPluginManager 
{
public:
	void register_plugin(const std::wstring& folder);
	void run_plugins_for_document(CDocument& doc);

private:
	//std::vector<std::shared_ptr<IPlugin>> vec_Plugins;

	struct Entry {
		HMODULE hMod{};
		std::shared_ptr<IPlugin> inst;
		void (*destroy)(IPlugin*) {};
	};
	std::vector<Entry> m_vecPlugins;
};
