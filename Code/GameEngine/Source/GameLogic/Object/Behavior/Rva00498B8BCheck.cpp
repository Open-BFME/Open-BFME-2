// cl: /DNDEBUG /MD
//
// ?Rva00498B8BGet@@YAEPAVObject@@@Z, retail 0x00498B8B, 36 bytes.
// Evidence: calls rowed 0x0028B511 Object::rva0028B511; flag byte at +0x108 bit 2; caller at 0x00498F5E pushes one pointer and tests al; free shape mov ecx [esp+4].

struct Rva00498B8BInner
{
	char m_pad[0x108];
	unsigned char m_flag108;
};

class Object
{
public:
	char m_pad0[4];
	Rva00498B8BInner *m_inner;
public:
	int rva0028B511() const;
};

unsigned char __cdecl Rva00498B8BGet(Object *p)
{
	if (p == 0)
		return 0;
	else
	{
		Rva00498B8BInner *inner = p->m_inner;
		if ((inner->m_flag108 & 4) != 0)
			return 0;
		return (unsigned char)(p->rva0028B511() == 1);
	}
}
