#include "pch.h"
#include "CppUnitTest.h"
#include "../Pr_11.4/11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            string filename = "test_bubble_sort.bin";
            ofstream testFile(filename, ios::binary);
            Note testNotes[] = {
                {"Doe", "John", 1234567890, {1, 2, 2000}},
                {"Smith", "Alice", 9876543210, {3, 4, 2001}},
                {"Johnson", "Bob", 5555555555, {5, 6, 1999}},
            };
            int numTestNotes = sizeof(testNotes) / sizeof(testNotes[0]);
            testFile.write((char*)&numTestNotes, sizeof(numTestNotes));
            testFile.write((char*)&testNotes, sizeof(testNotes));
            testFile.close();

            Bubble_Sort(filename);

            ifstream f(filename, ios::binary);
            Note sortedNotes[3];
            int numSortedNotes;
            f.read((char*)&numSortedNotes, sizeof(numSortedNotes));
            f.read((char*)&sortedNotes, sizeof(sortedNotes));
            f.close();

            Assert::AreEqual("Alice", sortedNotes[0].firstName);
            Assert::AreEqual("Bob", sortedNotes[1].firstName);
            Assert::AreEqual("John", sortedNotes[2].firstName);
		}
	};
}
