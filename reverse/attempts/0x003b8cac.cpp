// ?rva003B8CAC@Rva003B8CAC@@QAE_NXZ
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
// ?rva003B8CAC@Rva003B8CAC@@QAE_NXZ @0x003B8CAC 52B.
// Bounded dispatch: GlobalData +0x86 gate, index +0x10 against (m_18-m_14)/4,
// clear +0x2D then tail-jmp element Rva0052C036::rva0052C036, else false.
// Evidence: retail mov eax,[0xDFE758] cmp [eax+0x86],0; index chase +0x10/+0x14/+0x18
// sar 2 bounds; mov [ecx+0x2D],0; jmp 0x0052C036 row; callers 0x002B29AB 0x002BD3C2.
class GlobalData
{
public:
	char m_pad[0x86];
	unsigned char m_86;
};

extern GlobalData *TheWritableGlobalData;

class Rva0052C036
{
public:
	bool rva0052C036();
};

class Rva003B8CAC
{
	char m_pad00[0x10];
	int m_10;
	volatile int m_14;
	int m_18;
	char m_pad1C[0x2D - 0x1C];
	unsigned char m_2D;
public:
	bool rva003B8CAC();
};

// ?rva003B8CAC@Rva003B8CAC@@QAE_NXZ present-unmatched
bool Rva003B8CAC::rva003B8CAC()
{
	if (TheWritableGlobalData->m_86 == 0)
		return false;
	int n;
	int idx = m_10;
	if (idx < 0)
		return false;
	n = m_18;
	n -= m_14;
	n >>= 2;
	if ((unsigned)idx >= (unsigned)n)
		return false;
	m_2D = 0;
	Rva0052C036 *elem = ((Rva0052C036 **)m_14)[idx];
	return elem->rva0052C036();
}
