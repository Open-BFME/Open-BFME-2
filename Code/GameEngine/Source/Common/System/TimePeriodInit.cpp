// cl: /DNDEBUG /MD
//
// Multimedia timer initialization pair:
// 0x007B5510 (20B): calls timeBeginPeriod(1) and registers atexit(rva007B9AC0).
// 0x007B9AC0 (9B):  atexit callback that calls timeEndPeriod(1).

extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int uPeriod);
extern "C" __declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int uPeriod);
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void rva007B9AC0()
{
	timeEndPeriod(1);
}

void rva007B5510()
{
	timeBeginPeriod(1);
	atexit(rva007B9AC0);
}
