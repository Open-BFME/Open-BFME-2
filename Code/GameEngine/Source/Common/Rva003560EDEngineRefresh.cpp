// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00355DF4@Rva003560ED@@QAEXH@Z @0x00355DF4 44B
// ?rva00355E20@Rva003560ED@@QAEXHH@Z @0x00355E20 44B
// Slots 1 and 4 of vtable 0x00C14EA4 (class of the rowed dtor 0x003560ED and
// of rva00355DDD, slot 3), shared by the derived vtable 0x00C14EBC: both call
// TheGameEngine slot 23 and, when TheWritableGlobalData's +0x11C8 flag is set,
// TheDisplay slot 73 with 0. They differ only in their ignored stack
// arguments (ret 4 / ret 8), so ICF could not fold them.
#include "GameLogicObjectLookupView.h"

template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};
class GameEngine : public VirtualSlots<23>
{
public:
	virtual void slot23();
};
class Display : public VirtualSlots<68>
{
public:
	virtual void slot68();
	virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72();
	virtual void slot73(int value);
};
class W3DDisplay
{
public:
	void rva0025D2F6();
};
class GlobalData
{
public:
	unsigned char m_pad0000[0x11C8];
	bool m_11c8; // +0x11C8
};
extern GameEngine *TheGameEngine;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
class Rva003560ED
{
public:
	void rva00355DF4(int);
	void rva00355E20(int, int);
};
void Rva003560ED::rva00355DF4(int)
{
	TheGameEngine->slot23();
	if (TheWritableGlobalData->m_11c8)
		TheDisplay->slot73(0);
}
void Rva003560ED::rva00355E20(int, int)
{
	TheGameEngine->slot23();
	if (TheWritableGlobalData->m_11c8)
		TheDisplay->slot73(0);
}

// ?rva00355E4C@Rva003561BE@@QAE_NXZ @0x00355E4C 57B
// Slot 5 of the derived vtable 0x00C14EBC (class of the rowed deleting dtor
// 0x0035686D): true without TheAudio; otherwise TheAudio slot 10, then, unless
// the +0x1C value is 1, true only when TheAudio slot 52 refuses that value.
class AudioManager : public VirtualSlots<10>
{
public:
	virtual void slot10();
	virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
	virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24();
	virtual void a25(); virtual void a26(); virtual void slot27(int value); virtual void a28(); virtual void a29();
	virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34();
	virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44();
	virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49();
	virtual void a50(); virtual void a51();
	virtual bool slot52(int value);
};
extern AudioManager *TheAudio;
class Rva003561BE
{
public:
	bool rva00355E4C();
	void rva00355E85();
private:
	unsigned char m_pad00[0x08];
	int m_08; // +0x08
	unsigned char m_pad0C[0x1C - 0x0C];
	int m_1c; // +0x1C
	int m_20; // +0x20
};
bool Rva003561BE::rva00355E4C()
{
	bool result = true;
	if (TheAudio)
	{
		TheAudio->slot10();
		if (m_1c != 1)
			result = !TheAudio->slot52(m_1c);
	}
	return result;
}

// TheGameLogic's +0x78 flag, private padding in the shared GameLogic view.
extern GameLogic *TheGameLogic;
static __forceinline void clearGameLogicFlag78()
{
	*((bool *)TheGameLogic + 0x78) = false;
}

// ?rva00355E85@Rva003561BE@@QAEXXZ @0x00355E85 92B
// Slot 3 of the derived vtable 0x00C14EBC: hands each of the +0x1C/+0x20
// values that is not 1 to TheAudio slot 27 and resets it to 1, clears
// TheGameLogic's +0x78 flag, runs TheDisplay slot 68 and the rowed
// W3DDisplay 0x0025D2F6, and clears +0x08 (the base slot 3 rva00355DDD runs
// the same slot 68 then clears +0x08).
void Rva003561BE::rva00355E85()
{
	if (m_1c != 1)
	{
		TheAudio->slot27(m_1c);
		m_1c = 1;
	}
	if (m_20 != 1)
	{
		TheAudio->slot27(m_20);
		m_20 = 1;
	}
	clearGameLogicFlag78();
	TheDisplay->slot68();
	((W3DDisplay *)TheDisplay)->rva0025D2F6();
	m_08 &= 0;
}
