// ?rva006D9660@BfmeAptValue006DCD20@@QAEXPAVEAStringC@@PBD@Z
// partial score=0.75 date=2026-10-05
// cl: /O2 /MD /EHsc
//
// Address-derived recovery of the 249-byte Apt array-to-string joiner at RVA
// 0x006D9660. The class and its member offsets follow the rowed array helpers
// in Code/Libraries/Source/Apt/AptValue/AptValueArrayAt.cpp (m_data +0x20,
// mnCapacity +0x24, mnLength +0x28): the body walks m_data[i] for i in
// [0, mnLength), converts each element through the rowed
// ?rva006DD6C0@BfmeAptValue006DCD20@@QAEXAAVEAStringC@@@Z (0x006DD6C0) and
// appends the result to the out parameter through the rowed
// ?Rva006D4F00Append@EAStringC@@QAEAAV1@ABV1@@Z (0x006D4F00).
//
// Identity evidence from the three retail callers, all of which pass ecx =
// the array checked-cast result and push one separator:
//   0x006DA5EC  the loop's own tail, pushing (out, 0)
//   0x006D9AF1  the empty separator string literal at VA 0x00BBFB20
//   0x006DD894  the same literal inside the AptValue-to-string worker 0x006DD6C0
// The "mnElements < mnMaxElements" assertion at VA 0x00CEA954 and the
// "3\bfme2\Code\Libraries\Source\Apt\AptCIH.cpp" file string at 0x00CEA8C0
// name the retail assertion at AptCIH.cpp:0x16B; that string pair is read out
// of game.dat at the VAs the body itself pushes. The callee names here are
// private TU declarations of already-rowed functions.

#include <excpt.h>

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class EAStringC
{
public:
	EAStringC &Rva006D4F00Append(const EAStringC &other);
	EAStringC &Rva006D50A0Append(const char *text);
	void Rva006D3010Destroy();
};

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	virtual void slot1();

	int isArray() const;

	unsigned int m_flags;
	char m_pad[0x18];
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;

	void rva006D9660(EAStringC *pOut, const char *separator);
	void rva006DD6C0(EAStringC &out) const;
	BfmeAptValue006DCD20 *rva006D8A50(int nIndex);
};

// ?rva006D9660@@YAXPAVBfmeAptValue006DCD20@@PAVEAStringC@@PBD@Z
//
// void BfmeAptValue006DCD20::rva006D9660(EAStringC *pOut, const char *separator)
//
// Joins every element of the array into *pOut with `separator` between
// neighbours. The SEH scope is the retail one: the caller's out parameter is
// copied into a local before anything can throw, so the assignment below
// always commits the finished string. `mnElements < mnMaxElements` is asserted
// first, matching the immediate operands this body pushes.
void BfmeAptValue006DCD20::rva006D9660(EAStringC *pOut, const char *separator)
{
	if (!(mnLength < mnCapacity))
	{
		g_bfmeAptAssertAtE17734("mnElements < mnMaxElements", "3\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x16b);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}

	EAStringC local;
	__try
	{
		local = *pOut;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}

	for (int i = 0; i < mnLength; ++i)
	{
		BfmeAptValue006DCD20 *element = rva006D8A50(i);
		if (element)
		{
			EAStringC text;
			text.Rva006D4F00Append(local);
			element->rva006DD6C0(text);
			local.Rva006D4F00Append(text);
			text.Rva006D3010Destroy();
		}

		if (i < mnLength - 1)
			local.Rva006D50A0Append(separator);
	}
}
