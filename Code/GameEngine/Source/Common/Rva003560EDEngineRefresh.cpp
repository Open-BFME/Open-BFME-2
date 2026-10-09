// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00355DF4@Rva003560ED@@QAEXH@Z @0x00355DF4 44B
// ?rva00355E20@Rva003560ED@@QAEXHH@Z @0x00355E20 44B
// Slots 1 and 4 of vtable 0x00C14EA4 (class of the rowed dtor 0x003560ED and
// of rva00355DDD, slot 3), shared by the derived vtable 0x00C14EBC: both call
// TheGameEngine slot 23 and, when TheWritableGlobalData's +0x11C8 flag is set,
// TheDisplay slot 73 with 0. They differ only in their ignored stack
// arguments (ret 4 / ret 8), so ICF could not fold them.
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
class Display : public VirtualSlots<73>
{
public:
	virtual void slot73(int value);
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
	virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29();
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
private:
	unsigned char m_pad00[0x1C];
	int m_1c; // +0x1C
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
