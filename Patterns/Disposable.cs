namespace Patterns
{
    using System;

    public class Disposable : IDisposable
    {
        private bool _disposed = false;

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposeManaged)
        {
            if (!_disposed)
            {
                if (disposeManaged)  
                {
                    // Free managed objects
                }

                // Free unmanaged objects
                _disposed = true;
            }
        }

        ~Disposable()
        {
            Dispose(false);
        }
    }
}
