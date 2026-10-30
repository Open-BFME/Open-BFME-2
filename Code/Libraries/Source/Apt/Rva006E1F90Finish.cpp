// Native 0x006E1F90 returns a full-width 0/1 in EAX. All five callers
// test EAX, including the property setter; keep the declaration consistent.
// cl: /MD
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue;
class EAStringC;
class AptRenderingContext;
struct AptNativeHash;
class AptCIH {
private:
	virtual void unused0();
private:
	virtual void unused1();
private:
	virtual void unused2();
private:
	virtual AptNativeHash *GetNativeHashVirtual();
private:
	virtual void unused4();
private:
	virtual void unused5();
private:
	virtual void unused6();
public:
	virtual AptValue *rva006E0520(AptValue *, const EAStringC *);
public:
	void SetEventHandler(int mask);
	void DestroyGCPointers();
	void rva006dbd80();
public:
	void RemoveEventHandler(int mask);
public:
	virtual bool rva006E0560(AptValue *, const EAStringC *, AptValue *);
public:
	int rva006E1F90(int v);
public:
	int rva006E24D0();
public:
	void ClearCIH(int arg);
	// Existing rectangle workers, also used by the rowed bounds builder.
	void rva006E1DD0(void *pRect);
	void rva006E1C40(AptRenderingContext *context, int arg);
public:
	int rva006E0B80(int nLvl) const;
	int rva006E0B60() const;
	bool rva006E2460(const AptCIH *other) const;
	void *rva006E0FB0() const;
	void *rva006E1020() const;
	void *rva006E1100() const;
	void *rva006E1170() const;
	void *rva006E1090() const;
	void rva006E1F00(int mask);
	const AptCIH *rva006E0CB0() const;
	bool rva006E0C50(const AptCIH *other) const;
	bool rva006E0BF0() const;
	void rva006E11B0();
	bool rva006CFCD0() const;
	bool rva006E24E0() const;
private:
	// Partial operand view shared with the matched level-accessor donor.
	unsigned char _pad[0x40];
	void *m_44;
	AptCIH *m_parent; // +0x48
	void *m_4C;
	unsigned char _pad3[8];
	int m_code; // +0x58
};

int AptCIH::rva006E1F90(int flag)
{
	if (!rva006CFCD0()) {
		g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	int bits = *(int *)(*(int *)((char *)this + 0x4C) + 0x1C);
	bits = (bits << 8) >> 8;
	return (flag & bits) ||
		(*(int *)((char *)(*(AptCIH **)((char *)GetNativeHashVirtual() + 8))->GetNativeHashVirtual() + 0x10) & flag) ||
		(*(int *)((char *)GetNativeHashVirtual() + 0x10) & flag);
}
