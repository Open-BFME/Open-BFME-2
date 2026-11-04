// cl: /MD
// platformsdk
//
// Static-initializer strip: file-scope globals initialized from a Win32
// import at startup. Each is one translation unit's compiler-generated
// dynamic initializer; the IAT slot each one reads names the call
// (0x00BBA918 timeGetTime,
// 0x00BBA7F8/0x00BBA834 MessageBoxA/MessageBoxW). The owning
// TUs are unrecovered, so each initializer keeps an honest address name and
// each global the name the ledger already uses for it or an address-named
// extern.

#include <windows.h>

// NetworkInterfaceFrameAdvance.cpp's frame-advance timestamps.
extern unsigned long g_00DFEA2C;
extern unsigned long g_00DFEA30;
// Read by 0x005A671F and 0x005A672D.
extern unsigned long g_00E063FC;
// Read by 0x0023027C.
bool g_00DFE718 = false;  // retail 0x009FE718

struct Rva007ADBD1ImportInits
{
	static void rva007ADBD1();
	static void rva007ADDC7();
	static void rva007ADDD3();
	static void rva007B4439();
};

// 0x007ADBD1 (20B): VA 0x00DFE718 = whether the MessageBoxA and MessageBoxW
// IAT slots hold the same address.
void Rva007ADBD1ImportInits::rva007ADBD1()
{
	g_00DFE718 = &MessageBoxA == (void *)&MessageBoxW;
}

// 0x007ADDC7 (12B): VA 0x00DFEA2C = timeGetTime().
void Rva007ADBD1ImportInits::rva007ADDC7()
{
	g_00DFEA2C = timeGetTime();
}

// 0x007ADDD3 (12B): VA 0x00DFEA30 = timeGetTime().
void Rva007ADBD1ImportInits::rva007ADDD3()
{
	g_00DFEA30 = timeGetTime();
}

// 0x007AE9E6 (12B), VA 0x00E01D48 = GetDoubleClickTime(), is the dynamic
// initializer of GadgetListBoxMultiInput.cpp's doubleClickTime.

// 0x007B4439 (12B): VA 0x00E063FC = timeGetTime().
void Rva007ADBD1ImportInits::rva007B4439()
{
	g_00E063FC = timeGetTime();
}
