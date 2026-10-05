// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva005C9B76@@UAE@XZ @ 0x005C9B9C 71B
// Evidence: vtable 0x00874B9C; rowed forEach 0x005C9A46 and forwarder 0x001FF3A9; rowed free 0x00030830; caller deleting dtor 0x005C9CC2.
class Rva005C9A46Listener
{
public:
	virtual void notify(void *);
};

extern "C" void __cdecl free(void *);

class Rva005C9A46List
{
public:
	void forEach(void (Rva005C9A46Listener::*notify)(void *), void *arg);
	~Rva005C9A46List() throw()
	{
		if (m_begin)
			free(m_begin);
	}
	Rva005C9A46Listener **m_begin;
	Rva005C9A46Listener **m_end;
	Rva005C9A46Listener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class Rva005C9B76 : public Rva005C9A46List
{
public:
	virtual ~Rva005C9B76();
private:
	void *m_arg14;
	unsigned char m_b18;
	char m_pad19[3];
	int m_i1C;
};

Rva005C9B76::~Rva005C9B76()
{
	forEach((void (Rva005C9A46Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
}
