// cl: /MD /EHs
// ??1Rva005961D6@@UAE@XZ retail 0x00596225 68B
// Own vptr C70A4C; the owned buffer at +0x98 is freed when set (EH state 0),
// then the rowed base dtor ??1Rva0025BFE3@@UAE@XZ 0x0025BFE3. Caller: the
// slot-0 ??_G 0x005962CB. Names address-derived.

extern "C" void __cdecl free(void *block);

class Rva0025BFE3
{
public:
	virtual ~Rva0025BFE3();

private:
	unsigned char m_pad04[0x98 - 4];
};

class Rva005961D6Buffer
{
public:
	~Rva005961D6Buffer()
	{
		if (m_ptr)
			free(m_ptr);
	}

	void *m_ptr;
};

class Rva005961D6 : public Rva0025BFE3
{
public:
	virtual ~Rva005961D6();

private:
	Rva005961D6Buffer m_buffer; // +0x98
};

Rva005961D6::~Rva005961D6()
{
}
