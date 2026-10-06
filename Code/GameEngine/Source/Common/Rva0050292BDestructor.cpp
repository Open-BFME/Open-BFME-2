// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

void __cdecl free(void *block);

class Rva00500D30
{
public:
	~Rva00500D30();

private:
	char m_data[8];
};

class Rva005026B6
{
public:
	~Rva005026B6();

private:
	char m_data[8];
};

class Rva0050292BFree
{
public:
	__forceinline ~Rva0050292BFree()
	{
		if (m_pointer)
			free(m_pointer);
	}

private:
	void *m_pointer;
};

class Rva0050292B
{
public:
	~Rva0050292B();

private:
	char m_pad00[0x10];
	Rva0050292BFree m_free10;
	char m_pad14[0x10];
	Rva0050292BFree m_free24;
	char m_pad28[0x10];
	Rva005026B6 m_tree38;
	char m_pad40[4];
	Rva00500D30 m_tree44;
};

// 0x0050292B 93B: extent and EH state transitions come from Ghidra and the
// target call graph; class/member owners remain address-derived.
Rva0050292B::~Rva0050292B()
{
}
