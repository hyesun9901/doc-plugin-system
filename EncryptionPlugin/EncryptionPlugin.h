#pragma once
#ifdef ENCRYPTION_EXPORTS
#define ENCRYPTION_API __declspec(dllexport)
#else
#define ENCRYPTION_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/TxtDocument.h"

class ENCRYPTION_API CEncryptionPlugin : public IPlugin
{
public:
	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;

private:
	std::string rot13(const std::string& s);
};