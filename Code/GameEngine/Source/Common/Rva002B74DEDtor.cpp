// cl: /O1 /MD /EHs
// ??1Rva002B74DE@@QAE@XZ retail 0x002B74DE 93B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 2..0 -- the vectors at +0x1C and +0x10 (inline CRT free of each
// block), the holder at +0xC whose inline dtor runs the rowed
// ?clear@Rva002B430C@@QAEXXZ 0x002B430C, then the holder at +8 whose inline
// dtor runs the rowed ?rva002B2EA0@Rva002B2EA0@@QAEXXZ 0x002B2EA0.
// Names address-derived.

extern "C" void __cdecl free(void *block);

class Rva002B2EA0
{
public:
	~Rva002B2EA0()
	{
		rva002B2EA0();
	}
	void rva002B2EA0();
private:
	void *m_ptr;
};

class Rva002B430C
{
public:
	~Rva002B430C()
	{
		clear();
	}
	void clear();
private:
	void *m_ptr;
};

class Rva002B74DEVector
{
public:
	~Rva002B74DEVector()
	{
		if (m_begin)
			free(m_begin);
	}

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class Rva002B74DE
{
public:
	~Rva002B74DE();

private:
	char m_pad00[8];
	Rva002B2EA0 m_holder08; // +0x08
	Rva002B430C m_holder0C; // +0x0C
	Rva002B74DEVector m_vector10; // +0x10
	Rva002B74DEVector m_vector1C; // +0x1C
};

Rva002B74DE::~Rva002B74DE()
{
}
