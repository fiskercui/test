
using System;
using System.Collections.Generic;


namespace testcommon
{
    enum TestType : short  //显示指定枚举的底层数据类型
    {
        testreflection,
        testevent,  //此逗号可以省略
        testclass,
        testattribute,
        testIndex
    };


    class Program
    {


        public static Dictionary<TestType, string> testDict =new Dictionary<TestType, string>{
            { TestType.testreflection , "TestReflection" },
            { TestType.testevent, "TestEvent"},
            { TestType.testclass, "TestClass"},
            { TestType.testattribute ,"AttributeTest"},
            { TestType.testIndex ,"TestIndex"},
        };

        static void startTest(TestType type)
        {
            try
            {
                string s = testDict[type];
                string className = String.Format("testcommon.{0}", s);
                Type objType = Type.GetType(className);
                if (objType == null)
                {
                    throw new Exception(String.Format("class name :{0}", className));
                }
                Object[] constructParms = new object[] { };
                TestBase obj = (TestBase)Activator.CreateInstance(objType, constructParms);
                obj.run();
            }
            catch (Exception ex)
            {
                Console.WriteLine("error msg：" + ex.Message);
            }
            
        }
        static void Main(string[] args)
        {

            //ExecuteRectangle.run();

            //startTest(TestType.testattribute);
            //startTest(TestType.testreflection);
            startTest(TestType.testIndex);
            //startTest(TestType.testevent);
        }
    }
}
