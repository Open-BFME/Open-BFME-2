// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva0033073C@Rva003306B0@@QAEXXZ @ 0x0033073C 27B
// Evidence: chain from just-landed 0x003306B0; same vector at +0x10/+0x14; clears via remove-first loop.
#include <vector>
#include <algorithm>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	void rva0033073C();
private:
	Rva0033068BList m_list;
	_STL::vector<void *> m_vec;
};

void Rva003306B0::rva0033073C()
{
	while ((void **)m_vec.begin() != (void **)m_vec.end()) {
		_ReadWriteBarrier();
		rva003306B0((CreateAHeroData *)*m_vec.begin());
	}
}
