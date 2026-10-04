// ?rva006FD3F0@@YAPAVAptString@@PAVAptValue@@0@Z
// partial score=0.9 date=2026-10-04
// cl: /O2 /GX /DNDEBUG /MD
// /GX (rather than the sibling file's bare /MD, and not /O1) is the pairing that
// emits retail's frame: a bare SEH setup with no push ebp / mov ebp,esp, no
// local stack reservation and no separate funclet call -- the __try body stays
// inline. /O1 splits the filter and body into helpers instead.
// ?rva006FD3F0@@YAPEAVRva006D7D00@@0@Z @0x006FD3F0 203B (cdecl).
//
// Apt string-pair conversion callback, sitting immediately after the rowed
// 0x006FD340 in Rva006FD340Cluster.cpp and sharing its AptValue/EAStringC views
// and its /O2 /DNDEBUG /MD flags.
//
// Retail: asks the pooled AptString::Create 0x006D7210 for a result and takes
// its EAStringC at +8 (the vtable+8 layout Rva006D7D00Cluster.cpp models). Each
// of the two by-value AptValue arguments is folded into that string: when the
// value is a string (isString 0x006DC0D0) the address-pinned opaque accessor
// 0x006DCE50 returns storage whose +8 is the value's own EAStringC, which is
// assigned (operator= 0x006D3030) or appended (Rva006D4F00Append 0x006D4F00)
// respectively; otherwise the unrowed AptValue-to-EAStringC converter 0x006DD6C0
// fills the destination directly for the first argument, and fills a scoped
// temporary that is appended and then destroyed for the second. The result is
// returned after the SEH frame is restored.
//
// The SEH frame wraps the scoped temporary, whose constructor (clear, 0x006D2F90)
// and destructor (0x006D3010) retail calls directly -- the same pairing
// Rva006e9730Cluster.cpp records. They are expressed as named calls rather than
// a C++ lifetime because a scoped object with a destructor inside __try is
// rejected outright (C2712), and the frame has to stay in this function to
// place the frame-setup and teardown instructions where retail has them.
//
// 0x006DD6C0 and 0x006DCE50 are address-derived pins (reverse/symbols.csv)
// whose own bodies remain unclaimed; only the calls are reproduced here.

#include <excpt.h>

class EAStringC
{
public:
	EAStringC &rva006D2F90Construct();                    // 0x006D2F90
	void rva006D3010Destroy();                            // 0x006D3010
	EAStringC &operator=(const EAStringC &);               // 0x006D3030
	EAStringC &Rva006D4F00Append(const EAStringC &);       // 0x006D4F00
};

// The real EAStringC carries a data pointer and a small inline buffer; retail's
// scoped temporary occupies only one dword at [esp+0x0c] (the scope cookie at
// [esp+0x10]), so it is modelled as the single pointer the methods thread.
class Rva006EAStringCPointer
{
	void *m_pData;
public:
	void rva006D2F90Construct();
	void rva006D3010Destroy();
};

// 0x006DD6C0 fills `out` in place from the AptValue in ecx (ret 4 thiscall);
// 0x006DCE50 returns storage whose +8 is the value's own EAStringC, exactly as
// AptValueToIntegerBFME2.cpp reads it in toInteger. The two views stay in the
// one established BfmeAptValue006DCD20 class rather than being multiplied
// together, which would add a second vtable and change the frame.
class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	bool isString() const;                                // 0x006DC0D0
	void rva006DD6C0(EAStringC *out);
};

// The additional opaque accessor, reached on the same values.
class AptValue : public BfmeAptValue006DCD20
{
public:
	void *rva006DCE50();
};

// Returned by the pooled factory; the EAStringC member sits at +8.
class AptString
{
public:
	static AptString *Create();                          // 0x006D7210
	char m_pad[8];
	EAStringC m_str;
};

AptString *__cdecl rva006FD3F0(AptValue *arg1, AptValue *arg2)
{
	AptString *result = AptString::Create();
	EAStringC *dest = &result->m_str;
	__try
	{
		if (arg1->isString())
			*dest = *((EAStringC *)((char *)arg1->rva006DCE50() + 8));
		else
			arg1->rva006DD6C0(dest);
		if (arg2->isString())
			dest->Rva006D4F00Append(*((EAStringC *)((char *)arg2->rva006DCE50() + 8)));
		else
		{
			Rva006EAStringCPointer temp;
			temp.rva006D2F90Construct();
			arg2->rva006DD6C0((EAStringC *)&temp);
			dest->Rva006D4F00Append((const EAStringC &)temp);
			temp.rva006D3010Destroy();
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
	return result;
}