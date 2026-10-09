// ?bfmeReleaseQueuedDeviceInterfaces@@YAXXZ
// partial score=0.88 date=2026-10-09
// cl: /O1 /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include <vector>
class CriticalSection;
class ScopedCriticalSection { CriticalSection *cs; bool locked; void Lock(); void Unlock(); public: ScopedCriticalSection(CriticalSection *p):cs(p),locked(false){Lock();} ~ScopedCriticalSection(){if(locked)Unlock();} };
void BFME_DX8_Thread_Lock(); bool BFME_DX8_Thread_Assert();
struct DeviceLock { DeviceLock(){BFME_DX8_Thread_Lock();} ~DeviceLock(){BFME_DX8_Thread_Assert();} };
struct DeviceInterfaceView { virtual unsigned long __stdcall slot00()=0; virtual unsigned long __stdcall slot04()=0; virtual unsigned long __stdcall Release()=0; };
extern _STL::vector<void*> BFMEQueuedDeviceInterfaces;
extern unsigned char BFMEQueuedDeviceCriticalSection[36];
void bfmeReleaseQueuedDeviceInterfaces()
{
 if(BFMEQueuedDeviceInterfaces.empty())return;
 DeviceLock device;
 ScopedCriticalSection lock((CriticalSection*)BFMEQueuedDeviceCriticalSection);
 for(void **i=BFMEQueuedDeviceInterfaces.begin();i!=BFMEQueuedDeviceInterfaces.end();++i) ((DeviceInterfaceView*)*i)->Release();
 BFMEQueuedDeviceInterfaces.clear();
}
