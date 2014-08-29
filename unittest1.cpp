#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LineGraphTable;
namespace UnitTest1
{		
	TEST_CLASS(TestDataPoint)
	{
	public:
		
		TEST_METHOD(dp_TestConstructor)
		{
			float elems[]={1.1,2.2,2.3,4.5};
			int elems_sz=4;
			DataPoint* dp=new DataPoint();
			Assert::IsFalse(dp->numElements(),L"dp: Default Constructor n_elements>0");
			delete dp;
			dp=new DataPoint(elems_sz, elems);
			Assert::AreEqual(dp->numElements(),elems_sz,L"dp: Failed to Construct dp with array[4]");
			for(int i=0;i<4;i++)
				Assert::AreEqual(elems[i],dp->getElement(i),L"dp: Elements in dp dp not match array[4]");
		}
		TEST_METHOD(dp_TestSetters_Getters)
		{
			float elems[]={1.1,2.2,2.3,4.5};
			int elems_sz=4;
			DataPoint* dp=new DataPoint(elems_sz,elems);
			dp->setElement(0,9.99);
			Assert::AreEqual((float)9.99,dp->getElement(0),L"dp: Failed to set element");
		}
		TEST_METHOD(dp_TestAddElement)
		{
			float elems[]={1.1,2.2,2.3,4.5};
			int elems_sz=4;
			DataPoint* dp=new DataPoint(elems_sz,elems);
			dp->addElement(6.7);
			Assert::AreEqual(elems_sz+1,dp->numElements(),L"dp: Failed to add element to dp");
			Assert::AreEqual((float)6.7,dp->getElement(elems_sz),L"dp: Value of new element incorrect");
		}

	};
	TEST_CLASS(TestTable)
	{
	public:
		TEST_METHOD(tb_TestConstructor)
		{
			// TODO: Your test code here
		}
		TEST_METHOD(tb_TestSetters)
		{
			// TODO: Your test code here
		}
		TEST_METHOD(tb_TestGetters)
		{
			// TODO: Your test code here
		}
		TEST_METHOD(tb_TestIsValidTable)
		{
		}
		TEST_METHOD(tb_TestAddDataPoint)
		{
		}
		TEST_METHOD(tb_TestLoadTable)
		{
		}
		TEST_METHOD(tb_TestSaveTable)
		{
		}
		TEST_METHOD(tb_TestInitialize)
		{
		}
	};
	TEST_CLASS(TestMFCView)
	{
	public:
		TEST_METHOD(mfc_TestOpen)
		{
		}
		TEST_METHOD(mfc_TestSave)
		{
		}
		TEST_METHOD(mfc_TestViewNext)
		{
		}
		TEST_METHOD(mfc_TestViewPrev)
		{
		}
		TEST_METHOD(mfc_TestViewGoto)
		{
		}
		TEST_METHOD(mfc_TestAdd)
		{
		}
	};

}