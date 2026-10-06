// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva003306B0@Rva003306B0@@QAEXPAVCreateAHeroData@@@Z @ 0x003306B0 94B
// Evidence: chain from rowed Release 0x0053FA32; calls rowed find 0x0020E873, rowed forEach 0x0033068B twice, rowed erase 0x001FF51F; vector at +0x10, list at +0x00.
#include <vector>
#include <algorithm>

class Rva0053FA0A {
public:
	void rva0053FA32();
};

class CreateAHeroData : public Rva0053FA0A {
};

class Rva0033068BListener {
public:
	virtual void notify(void *, int);
	void dummy1(void *, int);
	void dummy2(void *, int);
};

class Rva0033068BList {
public:
	void forEach(void (Rva0033068BListener::*notify)(void *, int), void *arg, int value);
private:
	Rva0033068BListener **m_begin;
	Rva0033068BListener **m_end;
	Rva0033068BListener **m_capacity;
	unsigned int m_index;
};

class Rva003306B0 {
public:
	void rva003306B0(CreateAHeroData *key);
private:
	Rva0033068BList m_list;
	_STL::vector<void *> m_vec;
};

void Rva003306B0::rva003306B0(CreateAHeroData *key)
{
	CreateAHeroData **first = (CreateAHeroData **)m_vec.begin();
	CreateAHeroData **last = (CreateAHeroData **)m_vec.end();
	CreateAHeroData **it = _STL::find(first, last, key);
	if (it == last)
		return;
	m_list.forEach(&Rva0033068BListener::dummy1, this, (int)key);
	m_vec.erase((void **)it);
	m_list.forEach(&Rva0033068BListener::dummy2, this, (int)key);
	key->rva0053FA32();
}
