using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace RenderingDemo.Editor
{
    public class OpenGlCanvas : HwndHost
    {
        protected override System.Runtime.InteropServices.HandleRef BuildWindowCore(System.Runtime.InteropServices.HandleRef hwndParent)
        {
            IntPtr hwndHost = DoBuildWindowCore(hwndParent.Handle, (int)Width, (int)Height);
            return new HandleRef(this, hwndHost);
        }

        protected override void DestroyWindowCore(System.Runtime.InteropServices.HandleRef hwnd)
        {
            DoDestroyWindowCore(hwnd.Handle);
        }

        [DllImport("Engine.Dll", CallingConvention=CallingConvention.Cdecl)]
        public static extern IntPtr DoBuildWindowCore(IntPtr hwndParent, int width, int height);

        [DllImport("Engine.Dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void DoDestroyWindowCore(IntPtr hwnd);
    }
}
