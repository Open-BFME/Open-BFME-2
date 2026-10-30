// cl: /DNDEBUG /MD /EHsc
// platformsdk
// BFME1 6583b3c1 WW3D_Shutdown_Bfme.cpp and ZH ww3d.cpp semantic donors.
// Native1180E0..118166 returns bool and holds the rowed DX8 device lock
// only around DX8Wrapper::Shutdown125DC0. Movie cleanup117A10 is rowed.
// WW3D::Shutdown: BFME 2 returns bool (as its Init does); callers are
// W3DDisplay's destructor after W3DShaderManager::shutdown and
// W3DDisplay::init's failed-device path, as in ZH. Class/global
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
class WW3D {
public:
    static bool Shutdown();
    static void Stop_Movie_Capture();
private:
    static bool IsCapturing; static bool IsInitted;
    static StaticSortListClass *DefaultStaticSortLists; };
extern unsigned char g_WW3D_Lite;
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct BfmeDeviceGuard { BfmeDeviceGuard() { BFME_DX8_Thread_Lock(); }
    ~BfmeDeviceGuard() { BFME_DX8_Thread_Assert(); } };
class DX8Wrapper { public: static void Shutdown(); };
bool WW3D::Shutdown()
{
    if (IsCapturing) Stop_Movie_Capture();
    timeEndPeriod(1);
    if (!g_WW3D_Lite) { BfmeDeviceGuard guard; DX8Wrapper::Shutdown(); }
    ::delete DefaultStaticSortLists;
    IsInitted=false;
    return true;
}
