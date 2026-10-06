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

class AptValue;

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006EE1B0Inner
{
public:
	char m_pad1C[0x1C];
	unsigned int m_flags; // +0x1C
};

class BfmeAptValue006DCD20
{
public:
	BfmeAptValue006DCD20 *rva006DCF60(bool undefOK);

	char m_pad4C[0x4C];
	Rva006EE1B0Inner *m_inner; // +0x4C
};

// Rowed predicate at 0x006CFCD0 (Rva006CFCD0Apt.cpp). Retail calls it here;
// declaration only, definition lives in the row owner.
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};

extern AptValue *g_rva00e18078;

AptValue *rva006ee1b0(BfmeAptValue006DCD20 *entry)
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
		value->m_inner->m_flags &= 0xFDFFFFFF;
	}
	return g_rva00e18078;
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
		value->m_inner->m_flags |= 0x02000000;
	}
	return g_rva00e18078;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_rva00e18078@@3PAVAptValue@@A=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")
