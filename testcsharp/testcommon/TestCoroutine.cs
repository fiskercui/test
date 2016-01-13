using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace testcommon
{
    class TestCoroutine : TestBase
    {
        IEnumerator YieldSomeStuff()
        {
            yield return "hello";
            Console.WriteLine("foo!");
            yield  return  "world";
        }

        public override void run()
        { 
            IEnumerator e = YieldSomeStuff();
            while (e.MoveNext())
            {
                Console.WriteLine(e.Current);
            }
            
        }
    }


}
