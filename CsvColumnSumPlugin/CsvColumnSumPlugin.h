#pragma once
#ifdef CSVCOLUMNSUM_EXPORTS
#define CSVCOLUMNSUM_API __declspec(dllexport)
#else
#define CSVCOLUMNSUM_API __declspec(dllimport)
#endif

#include "../DocumentCore/IPlugin.h"
#include "../DocumentCore/CsvDocument.h"

class CSVCOLUMNSUM_API CCsvColumnSumPlugin : public IPlugin
{
public:
	explicit CCsvColumnSumPlugin(size_t column_index, bool has_header = true)
		: m_col(column_index), m_bisHasHeader(has_header) {}

	bool is_supported(CDocument& doc) const override;
	int execute(CDocument& doc) override;
	std::string get_plugin_name() const override;

private:
	size_t m_col;
	bool m_bisHasHeader;
};

