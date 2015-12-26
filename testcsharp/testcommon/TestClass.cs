using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace testcommon
{

    class Base
    {
        public void onOverLoad()
        {
            Console.WriteLine("Base onOverLoad");
        }

        public void onOverLoad(int a)
        {
            Console.WriteLine("Base onOverLoad param a");
        }

        //public int onOverLoad()
        //{
        //    Console.WriteLine("Base onOverLoad return a");
        //}

        public void onHide()
        {
            Console.WriteLine("Base onOverLoad");
        }
        public virtual void onOverRide()
        {
            Console.WriteLine("Base onOverRide");
        }
    }

    class Derived : Base
    {
        public  new void onHide()
        {
            Console.WriteLine("Derived onOverLoad");
        }

        public override void onOverRide()
        {
            base.onOverRide();
            Console.WriteLine("Derived onOverRide");
        }
    }

    class TestClass : TestBase
    {
        public override void run()
        {
            Base b1 = new Derived();
            b1.onOverRide();


            Derived d1 = new Derived();
            d1.onHide();




        }
    }
}
