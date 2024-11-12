#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2 A/Lab_10.2 A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student student = { "Ivanenko", 2, IK, 4, 5, 5 };
			double expectedAverage = (4 + 5 + 5) / 3.0;
			Assert::AreEqual(expectedAverage, student.avg(), 0.001, L"Середній бал розраховано неправильно");
		}
	};
}
