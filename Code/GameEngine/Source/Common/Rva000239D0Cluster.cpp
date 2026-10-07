// cl: /Od
//
// One-off bodies recovered from the 0x000239D0 neighbourhood. The cluster sits
// directly after the BfmeConv1502 string helper; the allocator call below is
// the same raw byte allocator pinned at 0x000307F0, and the free calls reach
// 0x00030830. Names are address-derived because no caller names them.

void free(void *p);

namespace _STL
{
	template<class T> class allocator
	{
	public:
		static T *allocate(unsigned n, const void *hint);
	};
}

class Rva000239D0
{
public:
	char *b;
	char *e;
	char *c;
	int size();
};

int Rva000239D0::size()
{
	return e - b;
}

class Rva00023A00
{
public:
	void f(void *p);
};

void Rva00023A00::f(void *p)
{
	if (p)
		free(p);
}

class Rva00023AC0
{
public:
	void *f(unsigned n, const void *hint);
};

void *Rva00023AC0::f(unsigned n, const void *hint)
{
	return n != 0 ? _STL::allocator<char>::allocate(n << 2, 0) : 0;
}

class Rva00023B00
{
public:
	void f(void *p, unsigned unused);
};

void Rva00023B00::f(void *p, unsigned unused)
{
	if (p)
		free(p);
}

// 0x00023B30..0x00023B48: RET8 initializer. Retail writes the second
// stack argument to the receiver's first word and returns the receiver.
// The first argument is unused; neither the original type nor its name is known.
class Rva00023B30
{
public:
    Rva00023B30(void *unused, void *value);
private:
    void *m_value;
};

Rva00023B30::Rva00023B30(void *unused, void *value) : m_value(value)
{
}