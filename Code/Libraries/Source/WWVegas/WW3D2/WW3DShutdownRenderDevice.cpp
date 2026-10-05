// cl: /O2 /G7 /DNDEBUG /MD /EHsc
// BFME1 6583b3c1 WW3D_Shutdown_Bfme.cpp and ZH ww3d.cpp semantic donors.
// Native1180E0..118166 returns bool and holds the rowed DX8 device lock
// only around DX8Wrapper::Shutdown125DC0. Movie cleanup117A10 is rowed.
// Existing address-based shutdownRenderDevice spelling is retained; the
// original target public function name remains unproven. Class/global
// spellings follow the donor while capture/Lite/init slots and cleanup
// behavior are independently established from target calls and accesses.
class FrameGrabClass { public: virtual ~FrameGrabClass(); };
class StaticSortListClass { public: virtual ~StaticSortListClass(); };
class RvaWW3DDestroySlot0 { public: virtual void *release(int); };
class WW3D { public: static bool IsCapturing; static bool IsInitted; static bool Lite;
    static FrameGrabClass *Movie; static StaticSortListClass *DefaultStaticSortLists;
    static void Stop_Movie_Capture(); };
void __cdecl operator delete(void *);
extern "C" __declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int);
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct BfmeDeviceGuard { BfmeDeviceGuard() { BFME_DX8_Thread_Lock(); }
    ~BfmeDeviceGuard() { BFME_DX8_Thread_Assert(); } };
class DX8Wrapper { public: static void Shutdown(); };
bool shutdownRenderDevice()
{
    if (WW3D::IsCapturing) WW3D::Stop_Movie_Capture();
    timeEndPeriod(1);
    if (!WW3D::Lite) { BfmeDeviceGuard guard; DX8Wrapper::Shutdown(); }
    ::delete WW3D::DefaultStaticSortLists;
    WW3D::IsInitted=false;
    return true;
}
