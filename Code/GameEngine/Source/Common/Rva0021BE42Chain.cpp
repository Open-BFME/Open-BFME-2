// cl: /O1 /MD
// ?rva0021BE42@Rva00219B9E@@QAEHII@Z @0x0021BE42 32B
// ?rva0021BE62@Rva00219B9E@@QAEHII@Z @0x0021BE62 32B
// ?rva0021BE82@Rva00219B9E@@QAEHII@Z @0x0021BE82 32B
// Three-level lookups through rowed 0x00219B9E: the second index selects the
// 216-byte element, null yields -1 via or eax,-1, else the first index is
// forwarded through the middle entries 0x0021BDAB/0x0021BDD3/0x0021BDFB
// (each a two-level forward via 0x0021BD22/0x0021BD41 differing only by the
// +4/+8/+0xC element offset, both pinned). Same this-passthrough into rowed
// 0x00219B9E as 0x00219C00/0x00219C3E proves the Rva00219B9E owner, and the
// or-eax,-1 null path matches rowed 0x00219C93. Middle-entry owner class
// identity is unproven.
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
	void *rva0021BD22(unsigned int o);
	int rva0021BD41(unsigned int o, void *p);
	int rva0021BDAB(unsigned int o);
	int rva0021BDD3(unsigned int o);
	int rva0021BDFB(unsigned int o);
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

// Middle entries of the chain: two-level forwards through rowed 0x00219B9E
// into 0x0021BD22, then into 0x0021BD41 with the element offset (+4/+8/+0xC).
// The if/else-return form (not early return, not ternary) reproduces
// retail's jne-forward layout with the or-eax,-1 fall-through, and the
// (index, pointer) argument order reproduces the add-then-push sequence.
int Rva0021BDAccess::rva0021BDAB(unsigned int o)
{
	int r;
	void *p = rva0021BD22(o);
	if (!p)
		r = -1;
	else
		r = rva0021BD41(o, (char *)p + 4);
	return r;
}

int Rva0021BDAccess::rva0021BDD3(unsigned int o)
{
	int r;
	void *p = rva0021BD22(o);
	if (!p)
		r = -1;
	else
		r = rva0021BD41(o, (char *)p + 8);
	return r;
}

int Rva0021BDAccess::rva0021BDFB(unsigned int o)
{
	int r;
	void *p = rva0021BD22(o);
	if (!p)
		r = -1;
	else
		r = rva0021BD41(o, (char *)p + 0xC);
	return r;
}
