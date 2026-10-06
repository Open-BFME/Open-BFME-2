// cl: /MD
// AptValue::AddRef / Release, virtual slots 0 and 1 of the AptValue family
// (named by the APT0.19.03 Xbox donor PDB, as in AptValueVectorReleaseBFME2.cpp;
// 30+ AptValue-derived vtables point at both). Target evidence: the refCount
// field is bits 6..17 of the flags at +4 (matched getRefCount at 0x006DBB20);
// the inline setter asserts "false" at AptValue.inl:298 and clamps to the
// 12-bit maximum; Release asserts "nRefCount > 0" at AptValue.cpp:1564, and at
// zero either defers through the release vector at VA 0x00E17710 (setting
// releaseAtEnd, bit 2) or tail-calls ForceDelete (slot 2). The byte at
// VA 0x00E180EC and virtual slot 12 gate the deferral; their identities are
// not established, so both keep address/slot-derived names.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue;

class AptValueVector
{
public:
	void rva006E6C00(AptValue *pValue);
};

class Rva008981E0Value
{
public:
	int aptHasAll();
};

// VA 0x00E17710; defined by AptValueConstructorBFME2.cpp.
extern AptValueVector *g_releaseVectorAtE17710;

// VA 0x00E180EC (zero-filled .bss); tested before the slot-12 query.
bool g_aptReleaseGateAtE180EC;

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void ForceDelete();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual bool slot12();

private:
	bool isUnknown5() const { return flags.unknown5; }
	bool isReleaseAtEnd() const { return flags.releaseAtEnd; }
	void setRefCount(unsigned int nRefCount)
	{
		if (nRefCount > 0xFFF) {
			g_bfmeAptAssertAtE17734("false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 298);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
			nRefCount = 0xFFF;
		}
		flags.refCount = nRefCount;
	}

	struct {
		unsigned int unknown0:1;
		unsigned int gcMark:1;
		unsigned int releaseAtEnd:1;
		unsigned int unknown3:1;
		unsigned int isDefined:1;
		unsigned int unknown5:1;
		unsigned int refCount:12;
		unsigned int remaining:14;
	} flags;
};

void AptValue::AddRef()
{
	setRefCount(flags.refCount + 1);
}

void AptValue::Release()
{
	int nRefCount = flags.refCount;
	if (!(nRefCount > 0)) {
		g_bfmeAptAssertAtE17734("nRefCount > 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValue.cpp", 1564);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	--nRefCount;
	setRefCount(nRefCount);
	if (nRefCount == 0) {
		if (g_aptReleaseGateAtE180EC && slot12())
			return;
		if (isUnknown5()) {
			if (isReleaseAtEnd())
				return;
			if (!reinterpret_cast<Rva008981E0Value *>(g_releaseVectorAtE17710)->aptHasAll()) {
				flags.releaseAtEnd = 1;
				g_releaseVectorAtE17710->rva006E6C00(this);
				return;
			}
			ForceDelete();
			return;
		}
		ForceDelete();
	}
}
