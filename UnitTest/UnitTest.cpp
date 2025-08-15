#include "pch.h"
#include "CppUnitTest.h"
#include "DocumentCore.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(Txt)
		{
			CTxtDocument txt("C:\\CppWorks\\SamsungMedisonPT\\UnitTest\\sample.txt");
			std::string strTest = txt.get_content();
			Assert::AreEqual(strTest.c_str(), "hi hello tetet");
			Assert::AreNotEqual(strTest.c_str(), "dddd");
		}

		TEST_METHOD(Json)
		{
			CJsonDocument json("C:\\CppWorks\\SamsungMedisonPT\\UnitTest\\sample.json");
			std::string strTest2 = json.get_content();
			Assert::AreEqual(strTest2.c_str(), "{\n\"hyesun\":\"test\",\n\"hihi\":1\n}");
			Assert::AreNotEqual(strTest2.c_str(), "dddd");
		}

		TEST_METHOD(Csv)
		{
			CCsvDocument csv("C:\\CppWorks\\SamsungMedisonPT\\UnitTest\\sample.csv");
			const auto& vecRows = csv.get_rows();
			auto test = vecRows.size();
			Assert::AreEqual((int)test, 3);
		}

	};
}
