// cl: /MD
// ?Rva005CCED5Insert@@YGPAPAURva004F711CObj@@PAPAU1@PAU1@PBVRva00468520@@@Z @0x005CCED5 37B evidence: calls rowed Create 0x004F711C then doubly-linked insert prev at +0 next at +4; caller 0x005CD018
// Creates Rva004F711CObj via rowed Create then inserts after pos and stores into *out returning out.
class Rva00468520;
struct Rva004F711CObj {
	Rva004F711CObj *m_prev00;
	Rva004F711CObj *m_next04;
	char m_rest[8];
};
Rva004F711CObj *__stdcall Rva004F711CCreate(const Rva00468520 *src);
Rva004F711CObj **__stdcall Rva005CCED5Insert(Rva004F711CObj **out, Rva004F711CObj *pos, const Rva00468520 *val)
{
	Rva004F711CObj *n = Rva004F711CCreate(val);
	Rva004F711CObj *next = pos->m_next04;
	n->m_prev00 = pos;
	n->m_next04 = next;
	next->m_prev00 = n;
	pos->m_next04 = n;
	*out = n;
	return out;
}
