// cl: /DNDEBUG /MD
// ?rva005F8F14Init@@YIXPAVRva005F8F14@@H0PAH@Z @0x005F8F14 29B evidence:
// fastcall (this, dead-edx, src, ptr) copying 32 bytes (rep movsd, count 8
// via push/pop for /O1 size) from src to this, then m_20 = *ptr; ret 8.
// Same fastcall family as 0x005F8E37/0x005F8E5A. TU-local view only.
struct Rva005F8F14Blk
{
	int m_v[8];
};

class Rva005F8F14
{
public:
	Rva005F8F14Blk m_blk;
	int m_20;
};

void __fastcall rva005F8F14Init(Rva005F8F14 *o, int dead, Rva005F8F14 *src, int *ptr)
{
	o->m_blk = src->m_blk;
	o->m_20 = *ptr;
}
