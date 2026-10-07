// cl: /O1 /MD
// ?rva002B2590@@YGXPAXPAVRva002B2590P2@@PAVRva002B2590P3@@@Z @0x002B2590 47B.
// Filtered forward (stdcall, ret 0xC): when the second object's +0x13C slot
// matches the third object's +0x14 slot, resolve the second object through
// pinned 0x003F0588 and, when that is non-null, forward the result plus the
// first pointer into pinned 0x003EFE72 on the second object. The lone caller
// (0x0059E6B7) passes three words with a dead global load into ecx, so this
// is a free function, not a member.
//
// Target evidence (game.dat, read-only, capstone): frameless, p3/p2 held in
// ecx/esi across the compare, thiscall pair on the second object, pop esi,
// ret 0xC. 0x003F0588 reads range members at +0x170/+0x174; 0x003EFE72 is a
// ret-8 thunk into 0x004FC3DC swapping this to its first arg. Identity
// unproven: honest address-derived names.
class Rva002B2590P3
{
public:
	unsigned char m_pad00[0x14];
	void *m_14;
};

class Rva002B2590P2
{
public:
	void *rva003F0588();
	void rva003EFE72(void *result, void *extra);

public:
	unsigned char m_pad00[0x13C];
	void *m_13C;
};

void __stdcall rva002B2590(void *p1, Rva002B2590P2 *p2, Rva002B2590P3 *p3)
{
	if (p2->m_13C != p3->m_14)
		return;
	void *result = p2->rva003F0588();
	if (result == 0)
		return;
	p2->rva003EFE72(result, p1);
}
