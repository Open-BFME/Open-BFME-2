// cl: /MD
//
// ?rva006E24E0@AptCIH@@QBE_NXZ, retail 0x006E24E0, 116 bytes.
// Target evidence: this+0x4C holds a field whose +0x24 pointer is tail-called
// at the pinned 0x006F7AC0 (the per-node walker that calls this predicate back
// on each +0x54 chain node); the sprite-base predicate at 0x006CFCD0 is tested
// once, then again inside the "isSpriteInstBase()" assert at AptCIH.h line
// 0x7D (file string 0x008E8C60, message 0x008E9A78); the else path ORs the
// rowed type predicates 0x006E0260 (12), 0x006E02B0 (15), 0x006E0300 (16) and
// 0x006DCC60 (14, argument 0). Same AptCIH layout as 0x6E0B80 in the near file;
// names are address-derived.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)

class Rva006E1C40Holder;
class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
	int isCharacterInst() const;
	void *rva006E04A0() const;
	void *rva006E0F40() const;
	int rva006E0260() const; // 0x006E0260 isShapeInst
	int rva006E02B0() const; // 0x006E02B0 isTextInst
	int rva006E0300() const; // 0x006E0300
	int rva006E0350() const; // 0x006E0350
	int rva006DCC60(bool) const;
	int rva006CBEE0(bool) const;
	int isScriptFunction() const;
	BfmeAptValue006DCD20 *rva006DCEE0();
	void setGCRootCount(unsigned int);
	char m_pad00[0x4C];
	Rva006E1C40Holder *m_4c; // +0x4C
};

class Rva006F7AC0
{
public:
	bool rva006F7AC0() const;
};

class Rva006E24E0Field4C
{
public:
	char m_pad[0x24];
	Rva006F7AC0 *m_24;
};

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

bool AptCIH::rva006E24E0() const
{
	const BfmeAptValue006DCD20 *self = (const BfmeAptValue006DCD20 *)this;
	if (rva006CFCD0()) {
		if (!rva006CFCD0()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		return ((Rva006E24E0Field4C *)m_4C)->m_24->rva006F7AC0();
	}
	if ((unsigned char)self->rva006E0260()
		|| (unsigned char)self->rva006E02B0()
		|| (unsigned char)self->rva006E0300()
		|| (unsigned char)self->rva006DCC60(false))
		return true;
	return false;
}
