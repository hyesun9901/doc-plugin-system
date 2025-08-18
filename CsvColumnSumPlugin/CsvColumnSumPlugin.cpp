#include "pch.h"
#include <iostream>
#include <vector>
#include "CsvColumnSumPlugin.h"

bool CCsvColumnSumPlugin::is_supported(CDocument& doc) const
{
	return doc.get_type() == "csv";
}

int CCsvColumnSumPlugin::execute(CDocument& doc)
{
	auto& csv = dynamic_cast<CCsvDocument&>(doc);
	const auto& rows = csv.get_rows();

	if (rows.empty()) 
	{
		std::cout << "[" << __FUNCTION__ << "] " << doc.get_path() << " is empty file\n";
		return ERROR_INVALID_DATA;
	}

	double sum = 0.0;
	size_t start = m_bisHasHeader ? 1 : 0;

	for (size_t i = start; i < rows.size(); ++i)
	{
		if (m_col >= rows[i].size())
		{
			std::cerr << "[" << __FUNCTION__ << "] " <<" Row " << i << " has insufficient columns\n";
			continue;
		}

		const std::string& cell = rows[i][m_col];
		try {
			sum += std::stod(cell);
		}
		catch (const std::exception& e) {
			std::cerr << "[" << __FUNCTION__ << "] "<< "Invalid number at row " << i << ", col " << m_col << ": " << cell << "\n";
		}
	}

	std::cout <<  "["<< __FUNCTION__ << "] " << doc.get_path() << " col#" << m_col << " -> sum=" << sum << "\n";
	
	return ERROR_SUCCESS;
}

std::string CCsvColumnSumPlugin::get_plugin_name() const
{
	return "CsvColumnSumPlugin";
}
