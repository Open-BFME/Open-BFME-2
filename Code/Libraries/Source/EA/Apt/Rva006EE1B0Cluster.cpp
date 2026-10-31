// cl: /DNDEBUG /MD
//
// Two 95-byte AptCIH flag workers, address-derived as their identity is not
// recovered. Both assert "isSpriteInstBase()" at AptCIH.h:125, then set or
// clear bit 25 (0x02000000) in a flag dword at +0x1C of the object reached
// through the checked cast's +0x4C pointer. The checked cast
// ?rva006DCF60@BfmeAptValue006DCD20@@QAEPAV1@_N@Z is rowed at 0x006DCF60 and
// the predicate ?rva006cfcd0@BfmeAptValue006DCD20@@QAEHXZ is pinned at
// 0x006CFCD0 (isUndefined false and type 0xD or 0x12). The shared return value
// is the global at 0x00E18078 (DIR32, named address-derived).

class AptCIH;
class EAStringC;
class AptValue
{
public:
	AptCIH *c_cih(bool bUndefinedOK);
	bool isCIH(bool bUndefinedOK) const;
	bool isUndefined() const;
	bool getIsDefined() const;
	float toFloat() const;
	int toInteger() const;
	void toString(EAStringC &) const;
	virtual void AddRef();
	virtual void Release();
};
class AptNativeHash;
struct SwapSprite;
class AptCIH
{
public:
    virtual void slot0();
    virtual void changed();
    virtual void slot2();
    virtual AptNativeHash *slot3();
    char unknown04[8];
    float matrix[6];
    char unknown24[0x44-0x24];
    float *properties;
    AptCIH *parent;
    SwapSprite *instance;
    char unknown50[8];
    signed int depth:17;
    unsigned int unknownDepth17:15;
    int unknown5c;
    void *rva006CFF40() const;
    void jumpToFrame(int);
    bool rva006CFCD0() const;
    bool IsSpriteInst(bool) const;
    bool IsAnimationInst(bool) const;
    void factorySetProperty(int,float,bool);
    void factoryEnsureProperties();
    void rva006E1DD0(void *);
    void *rva006E1170() const;
    void SetEventHandler(int);
    void RemoveEventHandler(int);
    int rva006E1F90(int);
};

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006EE1B0Inner
{
public:
	char m_pad18[0x18];
	int m_frame;          // +0x18
	unsigned int m_flags; // +0x1C
};

class BfmeAptValue006DCD20 : public AptValue
{
public:
	BfmeAptValue006DCD20(int);
	BfmeAptValue006DCD20 *rva006DCF60(bool undefOK);
	BfmeAptValue006DCD20 *checkedString();
	bool isCIH(bool bUndefinedOK) const;
	bool isUndefined() const;
	int isCharacterInst() const;
	int isInteger() const;
	int isString() const;
	int rva006E02B0() const;
	int rva006E03A0() const;
	void *rva006E0F40() const;
	int toInteger() const;
	virtual ~BfmeAptValue006DCD20();
	unsigned int m_flags; // +0x04
};

// Rowed predicate at 0x006CFCD0 (Rva006CFCD0Apt.cpp). Retail calls it here;
// declaration only, definition lives in the row owner.
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};

extern AptValue *gpUndefinedValue;

AptValue *stop(BfmeAptValue006DCD20 *entry)
{
	if (((const Rva006CFCD0 *)entry->rva006DCF60(false))->isSpriteInstBase())
	{
		BfmeAptValue006DCD20 *value = entry->rva006DCF60(false);
		if (!((const Rva006CFCD0 *)value)->isSpriteInstBase())
		{
			g_bfmeAptAssertAtE17734("isSpriteInstBase()",
				"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((Rva006EE1B0Inner *)((AptCIH *)value)->instance)->m_flags &= 0xFDFFFFFF;
	}
	return gpUndefinedValue;
}

AptValue *rva006ee210(BfmeAptValue006DCD20 *entry)
{
	if (((const Rva006CFCD0 *)entry->rva006DCF60(false))->isSpriteInstBase())
	{
		BfmeAptValue006DCD20 *value = entry->rva006DCF60(false);
		if (!((const Rva006CFCD0 *)value)->isSpriteInstBase())
		{
			g_bfmeAptAssertAtE17734("isSpriteInstBase()",
				"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((Rva006EE1B0Inner *)((AptCIH *)value)->instance)->m_flags |= 0x02000000;
	}
	return gpUndefinedValue;
}

// Two 154-byte Ghidra-unlisted siblings: step the sprite one frame forward
// (0x006EE270) or back (0x006EE310) from the +0x18 current frame through the
// rowed AptCIH::jumpToFrame 0x006E2C10, then clear the same bit 25 the stop
// worker above clears. Both carry the AptCIH.h:125 isSpriteInstBase()
// assert before each inner access. Address-derived names.

static __forceinline Rva006EE1B0Inner *spriteInst(BfmeAptValue006DCD20 *value)
{
	if (!((const Rva006CFCD0 *)value)->isSpriteInstBase())
	{
		g_bfmeAptAssertAtE17734("isSpriteInstBase()",
			"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return (Rva006EE1B0Inner *)((AptCIH *)value)->instance;
}

AptValue *nextFrame(BfmeAptValue006DCD20 *entry)
{
	((AptCIH *)entry->rva006DCF60(false))->jumpToFrame(spriteInst(entry->rva006DCF60(false))->m_frame + 1);
	spriteInst(entry->rva006DCF60(false))->m_flags &= 0xFDFFFFFF;
	return gpUndefinedValue;
}

AptValue *PrevFrame(BfmeAptValue006DCD20 *entry)
{
	((AptCIH *)entry->rva006DCF60(false))->jumpToFrame(spriteInst(entry->rva006DCF60(false))->m_frame - 1);
	spriteInst(entry->rva006DCF60(false))->m_flags &= 0xFDFFFFFF;
	return gpUndefinedValue;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
