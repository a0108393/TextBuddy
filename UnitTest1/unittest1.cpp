#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\TextBuddy\TextBuddy.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		// template to create other TEST_METHOD
		TEST_METHOD(SampleMethod1)
		{
			string msg = "\nWelcome to TextBuddy. test is ready for use\n\n";

			Assert::AreEqual(msg,printMessage("welcomeMessage","","test"));
		}
		
		// test_method to test sorting
		TEST_METHOD(TestMethodSorting)
		{
			// SortText test
			string expectedMsg = "\n1. a first line\n\n2. the second line\n";
			string expectedMsg1 = "\ntest is empty.\n";
			clearText("test");
			addText("the second line","test");
			addText("a first line","test");
			sortText("test");

			Assert::AreEqual(expectedMsg,displayText("test"));

			clearText("test");
			sortText("test");

			Assert::AreEqual(expectedMsg1,displayText("test"));

		}

		// test method for findText method when searchString is not found
		TEST_METHOD(TestMethodSearchingNotFound)
		{
			string expectedMsg1 = "content \"thirty one\"not found \nin file:test\n";
		
			clearText("test");
			addText("c third line","test");
			addText("the second line","test");
			addText("a first line","test");
			addText("d fourth line","test");

			Assert::AreEqual(expectedMsg1,findText("thirty one","test"));
		}

		
		// test method for findText method when file is empty
		TEST_METHOD(TestMethodSearchingEmptyFile)
		{
			string expectedMsg1 = "content \"thirty one\"not found \nin file:test\n";
		
			clearText("test");

			Assert::AreEqual(expectedMsg1,findText("thirty one","test"));
		}

		
		// test method for findText method when searchString is found
		TEST_METHOD(TestMethodSearchingFound)
		{
			string expectedMsg1 = "content found at 3. a first line \nin file:test\n";
			string expectedMsg2 = "content found at 2. the second line \nin file:test\n";
			string expectedMsg3 = "content found at 1. c third line \nin file:test\n";
		
			clearText("test");
			addText("c third line","test");
			addText("the second line","test");
			addText("a first line","test");
			addText("d fourth line","test");

			Assert::AreEqual(expectedMsg1,findText("first","test"));
			Assert::AreEqual(expectedMsg2,findText("second","test"));
			Assert::AreEqual(expectedMsg3,findText("third","test"));
		}

		// test method for findText method, contains testmethod for both cases when searchString is found and is not found
		TEST_METHOD(TestMethodSearchingFull)
		{
			// FindText test
			string expectedMsg1 = "content \"thirty\"not found \nin file:test\n";
			string expectedMsg2 = "content found at 3. a first line \nin file:test\n";
			string expectedMsg3 = "content found at 2. the second line \nin file:test\n";
			string expectedMsg4 = "content found at 1. c third line \nin file:test\n";
		
			clearText("test");
			addText("c third line","test");
			addText("the second line","test");
			addText("a first line","test");
			addText("d fourth line","test");

			Assert::AreEqual(expectedMsg1,findText("thirty","test"));
			Assert::AreEqual(expectedMsg2,findText("first","test"));
			Assert::AreEqual(expectedMsg3,findText("second","test"));
			Assert::AreEqual(expectedMsg4,findText("third","test"));
		
			clearText("test");
			Assert::AreEqual(expectedMsg1,findText("thirty","test"));
			
		}


	};
}