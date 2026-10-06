// partial score=0.95 date=2026-10-03
// cl: /MD
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptCIH
{
public:
	virtual void vtableSlot0();
	virtual void vtableSlot1();
	virtual void vtableSlot2();
	virtual void *vtableSlot3();
	unsigned char _pad[0x40];
	void *m_44;
	AptCIH *m_parent;
	void *m_4C;
	unsigned char _pad3[8];
	int m_code;

	bool rva006E1F90(int flag);
	bool rva006CFCD0() const;
};

bool AptCIH::rva006E1F90(int flag)
{
	if (!rva006CFCD0()) {
		g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	int bits = *(int *)(*(int *)((char *)this + 0x4C) + 0x1C);
	bits = (bits << 8) >> 8;
	return (flag & bits) ||
		(*(int *)((char *)(*(AptCIH **)((char *)vtableSlot3() + 8))->vtableSlot3() + 0x10) & flag) ||
		(*(int *)((char *)vtableSlot3() + 0x10) & flag);
}
