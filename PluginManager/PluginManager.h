#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "../DocumentCore/IPlugin.h"

class CPluginManager 
{
public:
	void register_plugin(const std::wstring& folder); // plugins.ini 파일의 플러그인 dll만 찾아 로딩한다.
	void register_plugin_all(const std::wstring& folder); //특정 폴더 모든 *.dll을 로딩한다.
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
