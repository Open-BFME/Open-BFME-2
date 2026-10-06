// cl: /MD
// Bit setters for flags byte at +0x34 (33B/37B/39B):
//  ?setBit0@Rva005FC64AOwner@@QAEXE@Z @0x005FC64A 33B
//  ?setBit1@Rva005FC66BOwner@@QAEXE@Z @0x005FC66B 37B
//  ?setBit2@Rva005FC690Owner@@QAEXE@Z @0x005FC690 39B
// Evidence: three consecutive bodies (0x64A+33=0x66B, 0x66B+37=0x690) with the
// same shape; each compares the byte param against bit N of [ecx+0x34] and on
// mismatch stores (old & ~((1<<N)|(1<<(N+4)))) | ((param&1)<<N). Masks are
// 0xEE/0xDD/0xBB for N=0/1/2. Callers are the +0x18 chase thunks 0x005FC6F7,
// 0x005FC70A, 0x005FC71E. Owner identity unproven so each keeps its address
// token. Flags from OpaqueScalarDeletingDtors.cpp (/O1 /MD) plus /G7: default
// /O2 emits shl for <<1 but retail has add al,al at 0x005FC66B; /O1 /G7 gives
// add for bit1 and keeps shl for bit2 (verified via align_diff).
class Rva005FC64AOwner
{
public:
	void setBit0(unsigned char value);
	char m_pad[0x34];
	unsigned char m_flags;
};
void Rva005FC64AOwner::setBit0(unsigned char value)
{
	if (value != (m_flags & 1)) {
		m_flags = (m_flags & 0xEE) | (value & 1);
	}
}
class Rva005FC66BOwner
{
public:
	void setBit1(unsigned char value);
	char m_pad[0x34];
	unsigned char m_flags;
};
void Rva005FC66BOwner::setBit1(unsigned char value)
{
	if (value != ((m_flags >> 1) & 1)) {
		m_flags = (m_flags & 0xDD) | ((value & 1) << 1);
	}
}
class Rva005FC690Owner
{
public:
	void setBit2(unsigned char value);
	char m_pad[0x34];
	unsigned char m_flags;
};
void Rva005FC690Owner::setBit2(unsigned char value)
{
	if (value != ((m_flags >> 2) & 1)) {
		m_flags = (m_flags & 0xBB) | ((value & 1) << 2);
	}
}
