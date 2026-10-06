// ?rva000B65FD@Rva000B65FD@@QAEHXZ
// partial score=0.95 date=2026-10-03
// rva000B65FD
// partial score=0.95 date=2026-10-03
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000B65FD@Rva000B65FD@@QAEHXZ, retail 0x000B65FD, 23B.
// Base at +8 plus nullable word at +4 of object reached via double
// dereference at +0xC. Callers 0x000B956A 0x000BDC8F. Honest address name.
//
// Retail (23B):
//   mov eax,[ecx+8]   ; base -> eax accumulator
//   mov ecx,[ecx+0xc] ; pp -> ecx
//   mov ecx,[ecx]     ; p  -> ecx
//   test ecx,ecx ; je +6
//   movzx ecx,W[ecx+4] ; jmp +2
//   xor ecx,ecx       ; the two-value phi lives in ecx
//   add eax,ecx ; ret
//
// The two shapes are mutually exclusive ONLY when the pp is consumed through a
// cached `p` local. Caching the POINTER-TO-POINTER and dereferencing it twice
// (`pp[0] ? pp[0]->m_word04 : 0`) keeps this pointer live across the test, so
// the +0xC load is emitted in ecx ahead of the branch and both arms of the phi
// materialise: retail's diamond, its load order and its register choice all
// come back together, byte-exact at 23B. Dereferencing into `p` first sinks the
// load into eax and cl forward-propagates the false arm, dropping the diamond.
struct Rva000B65FDAux
{
	char m_pad00[4];
	unsigned short m_word04;
};

class Rva000B65FD
{
public:
	int rva000B65FD();
private:
	char m_pad00[8];
	int m_base08;
	Rva000B65FDAux **m_pp0C;
};

// ?rva000B65FD@Rva000B65FD@@QAEHXZ
int Rva000B65FD::rva000B65FD()
{
	int base = m_base08;
	Rva000B65FDAux **pp = m_pp0C;
	int v = pp[0] ? pp[0]->m_word04 : 0;
	return base + v;
}
