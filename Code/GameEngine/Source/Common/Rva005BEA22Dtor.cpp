// cl: /O1 /MD /EHs
// ??1Rva005BEA22@@QAE@XZ retail 0x005BEA22 78B
// Non-virtual dtor: under EH state 0 the object at +0 is deleted through its
// slot-0 deleting dtor with flag 0 and the global ??3@YAXPAX@Z (a
// global-scope delete) and cleared; then the buffer member at +4 runs its
// inline dtor, which frees its block with the CRT free. Names address-derived.

extern "C" void __cdecl free(void *block);

class Rva005BEA22Owned
{
public:
	virtual ~Rva005BEA22Owned();
};

class Rva005BEA22Buffer
{
public:
	~Rva005BEA22Buffer()
	{
		if (m_data)
			free(m_data);
	}

	void *m_data; // +0x00
};

class Rva005BEA22
{
public:
	~Rva005BEA22();

private:
	Rva005BEA22Owned *m_owned; // +0x00
	Rva005BEA22Buffer m_buffer; // +0x04
};

Rva005BEA22::~Rva005BEA22()
{
	::delete m_owned;
	m_owned = 0;
}
