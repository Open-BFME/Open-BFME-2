// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target evidence: the two 32-bit thiscall workers consume an int carrying
// the argument-object pointer. Both test masks through 0x003EDE16 and
// 0x003EDE2A, inspect byte +0xE5, and walk the pointer range at +0x1C/+0x20.
// 0x003EDFD8 also calls the argument's +0x24/+0x28 vtable slots and compares
// the latter result with the word at TheLargeGroupAudio+0x3C. Their callback calls
// resolve to 0x005697F7 and 0x00569863. The target extent is the Ghidra span
// at each start (111 and 128 bytes); the next body begins at 0x003EE058.
// 0x003EDE44 (293 bytes, ret 4; the 0x0020D8F1 range loop's callee) runs the
// same test twice, on the +0x0C/+0x14 and the +0x08/+0x10 slots, clears either
// result through the +0x20/+0x24 flags when +0xE5 is set, and picks one
// pointer-to-member callback: 0x005697F7 when only the first test holds (the
// 0x003EDF69 test), 0x00569863 when only the second does (the 0x003EDFD8
// test) and 0x00569628 when both hold and the x/y pairs from slots
// +0x00/+0x04 differ. 0x005697F7 adds the subject's weight to the sound key
// pair and 0x00569863 subtracts it; WorldBuilder's call graph names
// 0x00569863 unregisterSubject and 0x00569628 updateSubject. Those pairs
// come back through hidden pointers and are compared with SSE ucomiss, hence
// /arch:SSE (the two smaller workers match either way).
// Structural inference: the argument vtable slot types below capture only the
// observed ABI and dispatch shape.

struct Rva003EDE16
{
	bool rva003EDE16(const void *other) const;
private:
	unsigned char m_pad[0x28];
	unsigned int m_req[19];
	unsigned int m_ban[19];
};

struct Rva003EDE2A
{
	bool rva003EDE2A(const void *other) const;
private:
	unsigned char m_pad[0xC0];
	unsigned int m_req[4];
	unsigned int m_ban[4];
};

struct Rva0020DXXXElem
{
	void rva003EDC31();
	void rva003EDC16();
	void rva003EDE44(int x);
	void rva003EDF69(int x);
	void rva003EDFD8(int x);
};

// An 8-byte x/y pair returned through a hidden pointer (so not a POD in
// retail's source), compared field by field.
struct Rva004ABA81Pair
{
	Rva004ABA81Pair() {}
	__forceinline bool isExactlyEqualTo(const Rva004ABA81Pair &in) const { return x == in.x && y == in.y; }
	float x;
	float y;
};

struct Rva0020DXXXArg
{
	virtual Rva004ABA81Pair get00() = 0;
	virtual Rva004ABA81Pair get04() = 0;
	virtual void *get08() = 0;
	virtual const void *get0C() = 0;
	virtual void *get10() = 0;
	virtual const void *get14() = 0;
	virtual void *get18() = 0;
	virtual void *get1C() = 0;
	virtual bool get20() = 0;
	virtual bool get24() = 0;
	virtual int get28() = 0;
};

// The callbacks are LargeGroupAudioSoundKeyPair's subject handlers; the
// argument object is the subject they read.
class LargeGroupAudioSubject;
class LargeGroupAudioSoundKeyPair
{
public:
	void updateSubject(LargeGroupAudioSubject *subject);	// 0x00569628
	void rva005697F7(LargeGroupAudioSubject *subject);
	void unregisterSubject(LargeGroupAudioSubject *subject);	// 0x00569863
};

typedef void (LargeGroupAudioSoundKeyPair::*Rva003EDE44Callback)(LargeGroupAudioSubject *subject);

// Only the frame word at +0x3C of the LargeGroupAudio subsystem is read.
class LargeGroupAudio
{
public:
	unsigned char m_pad[0x3C];
	int m_3C;
};
extern LargeGroupAudio *TheLargeGroupAudio;

void Rva0020DXXXElem::rva003EDE44(int x)
{
	Rva0020DXXXArg *arg = (Rva0020DXXXArg *)x;
	bool isIn;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get0C())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get14()))
		isIn = true;
	else
		isIn = false;
	bool wasIn;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get08())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get10()))
		wasIn = true;
	else
		wasIn = false;
	if (*(unsigned char *)((char *)this + 0xE5) != 0)
	{
		if (arg->get20())
			isIn = false;
		if (arg->get24())
			wasIn = false;
	}
	int frame = arg->get28();
	if (frame <= TheLargeGroupAudio->m_3C)
		wasIn = false;

	Rva003EDE44Callback callback;
	if (isIn)
	{
		if (wasIn)
		{
			if (arg->get04().isExactlyEqualTo(arg->get00()))
				return;
			else
				callback = &LargeGroupAudioSoundKeyPair::updateSubject;
		}
		else
			callback = &LargeGroupAudioSoundKeyPair::rva005697F7;
	}
	else
		callback = wasIn ? &LargeGroupAudioSoundKeyPair::unregisterSubject : 0;

	if (callback)
	{
		for (void **i = *(void ***)((char *)this + 0x1C);
			i != *(void ***)((char *)this + 0x20); ++i)
			(((LargeGroupAudioSoundKeyPair *)*i)->*callback)((LargeGroupAudioSubject *)arg);
	}
}

void Rva0020DXXXElem::rva003EDF69(int x)
{
	Rva0020DXXXArg *arg = (Rva0020DXXXArg *)x;
	bool run;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get0C())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get14()))
		run = true;
	else
		run = false;
	if (*(unsigned char *)((char *)this + 0xE5) != 0 && arg->get20())
		run = false;
	if (run)
	{
		for (void **i = *(void ***)((char *)this + 0x1C);
			i != *(void ***)((char *)this + 0x20); ++i)
			((LargeGroupAudioSoundKeyPair *)*i)->rva005697F7((LargeGroupAudioSubject *)arg);
	}
}

void Rva0020DXXXElem::rva003EDFD8(int x)
{
	Rva0020DXXXArg *arg = (Rva0020DXXXArg *)x;
	bool run;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get08())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get10()))
		run = true;
	else
		run = false;
	if (*(unsigned char *)((char *)this + 0xE5) != 0 && arg->get24())
		run = false;
	int frame = arg->get28();
	if (frame <= TheLargeGroupAudio->m_3C)
		run = false;
	if (run)
	{
		for (void **i = *(void ***)((char *)this + 0x1C);
			i != *(void ***)((char *)this + 0x20); ++i)
			((LargeGroupAudioSoundKeyPair *)*i)->unregisterSubject((LargeGroupAudioSubject *)arg);
	}
}
