// cl: /DNDEBUG /MD
//
// ?rva00565898@Rva00565898@@QAEPAVRva00564B1A@@PAV2@0@Z @0x00565898 (51B).
// Erase-like thiscall ret 8: new_finish = Copy(last m_finish first extra) then
// DestroyRange(new_finish m_finish) m_finish = new_finish return first. Evidence:
// calls just-landed Copy 0x00565668 plus rowed DestroyRange 0x0052C37A; callers
// 0x00565A8E/0x00566D05; neighbours Copy 0x005657B2 Tidy 0x005659CA. Extra is
// (char*)&first+3 to reproduce retail lea ebp+0xb; Copy ignores it. Pragma y-off
// forces the retail EBP frame that /O1 omits.
class Rva00564B1A
{
	char m_pad[0xc];
};

struct Rva0052BFB5Elem
{
	char m_pad[0xc];
};

Rva00564B1A *Rva00565668Copy(Rva00564B1A *first, Rva00564B1A *last, Rva00564B1A *dest, char *extra);
void Rva0052C37ADestroyRange(Rva0052BFB5Elem *first, Rva0052BFB5Elem *last);

class Rva00565898
{
public:
	Rva00564B1A *rva00565898(Rva00564B1A *first, Rva00564B1A *last);

private:
	char m_pad0[4];
	Rva00564B1A *m_finish;
};

#pragma optimize("y", off)
Rva00564B1A *Rva00565898::rva00565898(Rva00564B1A *first, Rva00564B1A *last)
{
	char *extra = (char *)&first + 3;
	Rva00564B1A *new_finish = Rva00565668Copy(last, m_finish, first, extra);
	Rva0052C37ADestroyRange((Rva0052BFB5Elem *)new_finish, (Rva0052BFB5Elem *)m_finish);
	m_finish = new_finish;
	return first;
}
#pragma optimize("", on)
