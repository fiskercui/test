using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Reflection;

namespace testcommon
{

    class TestB
    {
        public static String abc = "123";
        public static string test = "456";
        public void onTest(string param1)
        {
            Console.WriteLine("B onTest: {0}", param1);
        }

        public static int onTestB(int a)
        {
            return 10 + a;
        }
    }
    class TestReflection :TestBase
    {


        public override void run()
        {
            Console.WriteLine("----Start Reflection Test----");

            string n = "testcommon.TestB";
            Type typeB = Type.GetType(n);
            Object[] constructParms = new object[] { };
            TestB obj = (TestB)Activator.CreateInstance(typeB, constructParms);

            string nm = "onTest";
            MethodInfo mInfo = typeB.GetMethod(nm);
            mInfo.Invoke(obj, new object[] { "hehehe",});

            string nm2 = "onTestB";
            MethodInfo mInfo2 = typeB.GetMethod(nm2);
            Object ret = mInfo2.Invoke(obj, new object[] { 0, });
            Console.WriteLine("ret is {0}", ret);



            Console.WriteLine("----End Reflection Test----");
        }
    }
}
