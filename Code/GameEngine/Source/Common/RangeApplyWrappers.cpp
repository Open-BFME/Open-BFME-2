// cl: /DNDEBUG /MD /EHsc
//
// Wave-3 F34 shape family: range-apply wrappers. Each body walks a begin/end
// pointer pair (at +0x58/+0x5C for the pointer array, +0x8/+0xC for the
// inline-element arrays) and calls a pinned method per element, forwarding
// the wrapper's stack args. Identities beyond these shapes are not
// recovered.
//

class Rva005C8F50Elem
{
public:
	void rva005C8F50(int a, int b);
	unsigned char m_data[0x48];
};

class Rva005C834AOwner
{
public:
	void rva005C834A(int a, int b);
private:
	unsigned char m_pad00[8];
	Rva005C8F50Elem *m_begin;
	Rva005C8F50Elem *m_end;
};


class Rva005C90F1Elem
{
public:
	void rva005C90F1(int a, int b);
	unsigned char m_data[0x48];
};

class Rva005C839BOwner
{
public:
	void rva005C839B(int a, int b);
private:
	unsigned char m_pad00[8];
	Rva005C90F1Elem *m_begin;
	Rva005C90F1Elem *m_end;
};


class Rva005691DBHelper
{
public:
	void rva005691DB(void *owner, int a);
};

class Rva00569393Owner
{
public:
	void rva00569393(int a);
private:
	unsigned char m_pad00[0x58];
	Rva005691DBHelper **m_begin;
	Rva005691DBHelper **m_end;
};

void Rva00569393Owner::rva00569393(int a)
{
	for (Rva005691DBHelper **p = m_begin; p != m_end; ++p)
		(*p)->rva005691DB(this, a);
}
