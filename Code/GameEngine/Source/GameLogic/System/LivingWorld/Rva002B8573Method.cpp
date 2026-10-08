// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8573@Rva002B8573@@QAE_NPAVRva003190A5@@@Z @0x002B8573 62B via ref table pattern
// Evidence: REF table slot 0x007FDFEC plus neighbours plus prev LivingWorldLogic plus query row 0x003190A5 plus push_back pin.
#include <vector>

class Object;
class Rva003190A5
{
public:
	bool query() const;
	char m_pad00[0x54];
	int m_54;
	char m_pad58[0x78 - 0x58];
	Object *m_78;
};

struct Rva002B8573Filter
{
	char m_pad00[0x14];
	int m_14;
};

class Rva002B8573
{
public:
	bool rva002B8573(Rva003190A5 *a);
private:
	char m_pad00[4];
	_STL::vector<Object *> *m_vec04;
	Rva002B8573Filter *m_flt08;
};

bool Rva002B8573::rva002B8573(Rva003190A5 *a)
{
	Object *obj = a->m_78;
	if (!a->query())
		return true;
	if (m_flt08 != 0)
	{
		if (m_flt08->m_14 != a->m_54)
			return true;
	}
	m_vec04->push_back(obj);
	return true;
}

// ?rva002B85B1@Rva002B85B1@@QAE_NPAVRva003190A5@@@Z @0x002B85B1 59B via ref table sibling.
// Evidence: REF table slot 0x007FDFF0 plus neighbour rva002B8573 plus query plus push_back.
class Rva002B85B1
{
public:
	bool rva002B85B1(Rva003190A5 *a);
private:
	char m_pad00[4];
	_STL::vector<Object *> *m_vec04;
	int m_08;
};

bool Rva002B85B1::rva002B85B1(Rva003190A5 *a)
{
	Object *obj = a->m_78;
	if (obj == 0)
		return true;
	if (!a->query())
		return true;
	if (a->m_54 != m_08)
		return true;
	m_vec04->push_back(obj);
	return true;
}
