// cl: /DNDEBUG /MD /EHsc
// platformsdk
// BFME1 6583b3c1 WW3D_Shutdown_Bfme.cpp and ZH ww3d.cpp semantic donors.
// Native1180E0..118166 returns bool and holds the rowed DX8 device lock
// only around DX8Wrapper::Shutdown125DC0. Movie cleanup117A10 is rowed.
// Existing address-based shutdownRenderDevice spelling is retained; the
// original target public function name remains unproven. Class/global
// spellings follow the donor while capture/Lite/init slots and cleanup
// behavior are independently established from target calls and accesses.
#include <new>
#include <windows.h>

class FrameGrabClass { public: virtual ~FrameGrabClass(); };
class StaticSortListClass { public: virtual ~StaticSortListClass(); };
class RvaWW3DDestroySlot0 { public: virtual void *release(int); };
// ww3d.cpp defines WW3D's statics private (?IsCapturing@WW3D@@0_NA, ...); spell them so.
// Lite lives in ww3d.cpp's g_WW3D_Lite (VA 0x00DEC411), which the init path writes;
// the default sort list is WW3D::DefaultStaticSortLists (0x00DEC3F0).
class WW3D { friend bool shutdownRenderDevice(); static bool IsCapturing; static bool IsInitted;
    static StaticSortListClass *DefaultStaticSortLists;
public:
    static void Stop_Movie_Capture(); };
extern unsigned char g_WW3D_Lite;
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct BfmeDeviceGuard { BfmeDeviceGuard() { BFME_DX8_Thread_Lock(); }
    ~BfmeDeviceGuard() { BFME_DX8_Thread_Assert(); } };
class DX8Wrapper { public: static void Shutdown(); };
bool shutdownRenderDevice()
{
    if (WW3D::IsCapturing) WW3D::Stop_Movie_Capture();
    timeEndPeriod(1);
    if (!g_WW3D_Lite) { BfmeDeviceGuard guard; DX8Wrapper::Shutdown(); }
    ::delete WW3D::DefaultStaticSortLists;
    WW3D::IsInitted=false;
    return true;
}
