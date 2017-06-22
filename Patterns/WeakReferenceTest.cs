namespace Patterns
{
    using System;
    using System.Threading;
    using NUnit.Framework;

    [TestFixture]
    public class WeakReferenceTest
    {
        [Test]
        public void TestWeakReference()
        {
            var reference = new WeakReference(new object());

            Assert.IsFalse(reference.Target == null);

            GC.Collect();
            Thread.Sleep(1000); // Чтобы сборщик мусора точно успел отработать

            Assert.IsTrue(reference.Target == null);
        }
    }
}
