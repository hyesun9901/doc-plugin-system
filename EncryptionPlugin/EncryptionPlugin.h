#pragma once
#ifdef ENCRYPTION_EXPORTS
#define ENCRYPTION_API __declspec(dllexport)
#else
#define ENCRYPTION_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/TxtDocument.h"

//Txt������ ��ȣȭ���ִ� �÷�����
class CEncryptionPlugin : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::wstring get_plugin_name() const override;

private:
	std::wstring rot13(const std::wstring& wstr);
};