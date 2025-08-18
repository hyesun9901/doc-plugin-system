// PluginManager.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include "PluginManager.h"
#include "Document.h"
#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/TxtDocument.h"
#include "../WordCountPlugin/WordCountPlugin.h"
#include "../EncryptionPlugin/EncryptionPlugin.h"

void CPluginManager::register_plugin(std::shared_ptr<IPlugin> p)
{
	vec_Plugins.push_back(std::move(p));
}

void CPluginManager::run_plugins_for_document(CDocument& doc)
{
	std::cout << "["<<__FUNCTION__<<"] " << doc.get_path() << " (doc type = " << doc.get_type() << ") \n";
	bool bAnyPlugin = false;
	for (auto& p : vec_Plugins) 
	{
		if (p->is_supported(doc)) 
		{
			bAnyPlugin = true;
			try {
				int nResult = p->execute(doc);
				std::cout << "[" << __FUNCTION__ << "] " << p->get_plugin_name() <<"result = " << nResult << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "[ERROR] " << "WordCountPlugin" << ": " << e.what() << "\n";
			}
			catch (...) {
				std::cerr << "[ERROR] " <<  "WordCountPlugin" << ": unknown error\n";
			}
		}
	}

	if (false == bAnyPlugin) 
	{
		std::cout << "Not exist compatible plugins...\n";
	}
}

int main()
{
	try {
		CPluginManager pm;
		pm.register_plugin(std::make_shared<CWordCountPlugin>());
		pm.register_plugin(std::make_shared<CEncryptionPlugin>());
		CTxtDocument  txt("sample.txt");

		pm.run_plugins_for_document(txt);
		std::cout << txt.get_content() << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;;
		return 1;
	}
}