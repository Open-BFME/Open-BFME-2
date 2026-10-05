// cl: /O1 /MD
// ?rva0021BE42@Rva00219B9E@@QAEHII@Z @0x0021BE42 32B
// ?rva0021BE62@Rva00219B9E@@QAEHII@Z @0x0021BE62 32B
// ?rva0021BE82@Rva00219B9E@@QAEHII@Z @0x0021BE82 32B
// Three-level lookups through rowed 0x00219B9E: the second index selects the
// 216-byte element, null yields -1 via or eax,-1, else the first index is
// forwarded through the middle entry 0x0021BDAB/0x0021BDD3/0x0021BDFB (each a
// two-level forward via 0x0021BD22/0x0021BD41 differing only by the +4/+8/+0xC
// element offset; not referenced here). Same this-passthrough into rowed
// 0x00219B9E as 0x00219C00/0x00219C3E proves the Rva00219B9E owner, and the
// or-eax,-1 null path matches rowed 0x00219C93. Middle entries are pinned;
// their owner class identity is unproven.
class Rva00219B9E
{
public:
	void *rva00219B9E(unsigned int index);
	int rva0021BE42(unsigned int o, unsigned int i);
	int rva0021BE62(unsigned int o, unsigned int i);
	int rva0021BE82(unsigned int o, unsigned int i);
};

class Rva0021BDAccess
{
public:
	int rva0021BDAB(unsigned int i);
	int rva0021BDD3(unsigned int i);
	int rva0021BDFB(unsigned int i);
};

int Rva00219B9E::rva0021BE42(unsigned int o, unsigned int i)
{
	void *p = rva00219B9E(i);
	return p ? ((Rva0021BDAccess *)p)->rva0021BDAB(o) : -1;
}

int Rva00219B9E::rva0021BE62(unsigned int o, unsigned int i)
{
	void *p = rva00219B9E(i);
	return p ? ((Rva0021BDAccess *)p)->rva0021BDD3(o) : -1;
}

int Rva00219B9E::rva0021BE82(unsigned int o, unsigned int i)
{
	void *p = rva00219B9E(i);
	return p ? ((Rva0021BDAccess *)p)->rva0021BDFB(o) : -1;
}
