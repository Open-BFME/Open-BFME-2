// cl: /MD
// ?rva002B3753@Rva002B3753@@QAEHXZ @0x002B3753 22B: __thiscall int predicate.
// Difference of the two dwords at +0x90 and +0x8C, masked with ~3, tested for
// zero through MSVC's neg/sbb/inc idiom. Evidence: retail
//   mov eax,[ecx+0x90]; add ecx,0x8C; sub eax,[ecx]; and al,0xFC
//   neg eax; sbb eax,eax; inc eax; ret
// caller 0x0051EDE9; no callees. Sibling Rva002B34E5 shares the 0x8C/0x90 pair.
//
// /G7 is load-bearing: the ~3 mask is encoded as `and al,0xFC` (24 fc) only
// under /O1 /G7. /G6, /G3-/G5, /O2, /Ox and /Os all emit `and eax,0xFFFFFFFC`
// (83 e0 fc) and the body comes out one byte long at 23B.
class Rva002B3753
{
	char m_pad[0x8C];
	int m_8C;
	int m_90;

public:
	int rva002B3753();
};

int Rva002B3753::rva002B3753()
{
	int *p = &m_8C;
	int diff = *(p + 1) - *p;
	return ((diff & 0xFFFFFFFC) == 0) ? 1 : 0;
}
