// cl: /DNDEBUG /MD
// ?rva005E58ED@Rva005E58ED@@QAEXXZ @0x005E58ED 34B.
// If +8->+0x18 object’s 0x00318C32 (pinned, this-only int) is 0 return.
// Else call pinned 0x005E6836 (this + 2 args: +8->+0x18 value and first result).
// Ret void, this only. Address-derived.
class Rva00318C32
{
public:
	int rva00318C32();
};

class Rva005E6836
{
public:
	void rva005E6836(int a, int b);
};

class Rva005E58EDInner
{
public:
	unsigned char m_pad[0x18];
	Rva00318C32 *m_18;
};

class Rva005E58ED
{
public:
	void rva005E58ED();
protected:
	unsigned char m_pad[8];
	Rva005E58EDInner *m_8;
};

void Rva005E58ED::rva005E58ED()
{
	int r = m_8->m_18->rva00318C32();
	if (r == 0)
		return;
	((Rva005E6836 *)this)->rva005E6836(r, *(int *)((unsigned char *)m_8 + 0x18));
}
