// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ??1Rva005D4C61@@UAE@XZ retail 0x005D4C61 90B dtor stores vtable 0x00875AAC plus list forEach and holder clear with list free

class Rva005D4C01Listener
{
public:
	virtual void notify(void *);
};

void __cdecl free(void *);

class Rva005D4C01List
{
public:
	void forEach(void (Rva005D4C01Listener::*notify)(void *), void *arg);
// ??1Rva005D4C01List@@QAE@XZ present-unmatched
	~Rva005D4C01List()
	{
		void *p = m_begin;
		if (p)
			free(p);
	}
	Rva005D4C01Listener **m_begin;
	Rva005D4C01Listener **m_end;
	Rva005D4C01Listener **m_capacity;
	unsigned int m_index;
};

class DummyCb1
{
public:
	void cb(void *);
};

class Rva005D4913
{
public:
	~Rva005D4913();
};

class Rva005D4BE7
{
	Rva005D4913 *m_ptr;
public:
	void rva005D4BE7();
// ??1Rva005D4BE7@@QAE@XZ present-unmatched
	~Rva005D4BE7()
	{
		rva005D4BE7();
	}
};

class Rva005D4C61
{
public:
	virtual ~Rva005D4C61();
private:
	Rva005D4C01List m_04;
	Rva005D4BE7 m_14;
};

Rva005D4C61::~Rva005D4C61()
{
	typedef void (Rva005D4C01Listener::*Notify_t)(void *);
	m_04.forEach((Notify_t)&DummyCb1::cb, this);
}
