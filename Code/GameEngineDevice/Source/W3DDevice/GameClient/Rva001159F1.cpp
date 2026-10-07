// cl: /DNDEBUG /MD /EHsc /O1
// Native1159F1-115A5A takes one pointer. Retail saves the old member at
// +0x88 into +0x8C then stores the argument. The subsequent calls and the
// rectangle {0, 0, +0x50 + +0x58, +0x54 + +0x58} are direct target evidence.
// Receiver identity is unknown; fields are an address-derived ABI view.

class Rva000AD9AB
{
public:
	void rva000AD9FE();
};

class Rva00113110Holder
{
public:
	void rva00112898(int, int, void *);
};

class Rva00111F0E
{
public:
	void rva00111F0E();
};

class Rva00115044
{
public:
	void rva00115044(int *, int, int, unsigned char);
};

class Rva001159F1
{
	char m_pad00[0x50];
	int m_x;
	int m_y;
	int m_span;
	Rva000AD9AB *m_bitPlane;
	unsigned char m_flags;
	unsigned char m_mode;
	char m_pad62[0x26];
	void *m_current;
	void *m_previous;

public:
	void rva001159F1(void *value);
};

void Rva001159F1::rva001159F1(void *value)
{
	m_previous = m_current;
	m_current = value;
	m_bitPlane->rva000AD9FE();
	reinterpret_cast<Rva00113110Holder *>(this)->rva00112898(
		0, 0, reinterpret_cast<void *>(m_span));
	reinterpret_cast<Rva00111F0E *>(this)->rva00111F0E();

	int rectangle[4];
	rectangle[0] = 0;
	rectangle[1] = 0;
	rectangle[2] = m_x + m_span;
	rectangle[3] = m_y + m_span;
	reinterpret_cast<Rva00115044 *>(this)->rva00115044(
		rectangle, 0, 0, m_mode);
}
