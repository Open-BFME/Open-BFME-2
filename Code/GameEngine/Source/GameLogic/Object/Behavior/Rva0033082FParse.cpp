// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0033082F@Rva0033082FTarget@@QAEEHH@Z @0x0033082F 191B. Chain via 0x00542379.
// Clears vector at +0x10 via rowed 0x003306B0 then parses DataChunkInput tags
// 0x66726565->0x44/0x6c6f6f6b->0x64 objects via rowed new and ctors,
// virtual init at +0x10, then rowed 0x003307F2. Evidence: rowed callees,
// prev/next flags, caller forwarder 0x003308EE. Returns 1 in al so E not X.
#include <vector>

class DataChunkInput
{
public:
	int readInt() throw();
};

class ModuleData
{
public:
	char m_pad[20];
	int m_ref;
};

class CreateAHeroData
{
public:
	void dummy() throw();
};

class Rva0033068BListener
{
public:
	virtual void notify(void *, int);
};

class Rva0033068BList
{
public:
	void forEach(void (Rva0033068BListener::*notify)(void *, int), void *arg, int value) throw();
private:
	Rva0033068BListener **m_begin;
	Rva0033068BListener **m_end;
	Rva0033068BListener **m_capacity;
	unsigned int m_index;
};

class Rva003306B0
{
public:
	void rva003306B0(CreateAHeroData *key) throw();
};

class Rva003307F2
{
public:
	void rva003307F2(const ModuleData *mod) throw();
};

void *__cdecl operator new(unsigned int size);

class RvaParseBase
{
public:
	virtual void b0() throw();
	virtual void b1() throw();
	virtual void b2() throw();
	virtual void b3() throw();
	virtual void b4(int a0, int a1) throw();
};

class Rva00541EB8 : public RvaParseBase
{
public:
	Rva00541EB8();
private:
	char m_extra[0x64 - sizeof(RvaParseBase)];
};

class Rva00540845 : public RvaParseBase
{
public:
	Rva00540845();
private:
	char m_extra[0x44 - sizeof(RvaParseBase)];
};

class Rva0033082FTarget
{
public:
	unsigned char rva0033082F(int a0, int a1);
private:
	Rva0033068BList m_list;
	_STL::vector<const ModuleData *> m_vec;
};

unsigned char Rva0033082FTarget::rva0033082F(int a0, int a1)
{
	while (!m_vec.empty())
		((Rva003306B0 *)this)->rva003306B0((CreateAHeroData *)m_vec.front());
	DataChunkInput *in = (DataChunkInput *)a0;
	int remaining = in->readInt();
	if (remaining <= 0)
		return 1;
	do {
		--remaining;
		int tag = in->readInt();
		RvaParseBase *obj = 0;
		switch (tag) {
		case 0x66726565:
			obj = new Rva00540845;
			break;
		case 0x6c6f6f6b:
			obj = new Rva00541EB8;
			break;
		default:
			break;
		}
		if (obj == 0)
			break;
		obj->b4(a0, a1);
		((Rva003307F2 *)this)->rva003307F2((const ModuleData *)obj);
	} while (remaining > 0);
	return 1;
}
