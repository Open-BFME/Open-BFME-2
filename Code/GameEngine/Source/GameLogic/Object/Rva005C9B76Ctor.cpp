// cl: /DNDEBUG /MD /EHsc
// ??0Rva005C9B76@@QAE@PAX@Z @0x005C9B76 38B
// Honest-address ctor installing vtable 0x00874B9C: member Rva00330757Member
// at +0x4 via rowed 0x00330757, arg pointer at +0x14, int at +0x1C cleared
// via and-idiom, byte at +0x18 zeroed. Callers at 0x0056DBD4 and 0x005752E1
// pass subobject this plus void arg.

class Rva00330757Member
{
public:
	Rva00330757Member();

private:
	char m_data[0x10];
};

class Rva005C9B76 : public Rva00330757Member
{
public:
	Rva005C9B76(void *arg);
	virtual ~Rva005C9B76();

private:
	void *m_arg14;
	unsigned char m_b18;
	char m_pad19[0x3];
	int m_i1C;
};

Rva005C9B76::Rva005C9B76(void *arg)
{
	m_i1C = 0;
	m_arg14 = arg;
	m_b18 = 0;
}
