// cl: /O1 /G7 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Owned-pointer list teardown, three native copies of one shape (74B each): walk a
// vector<void *> of polymorphic owned objects, run each one's slot-0 deleteInstance(0) (null
// elements pass null) into the rowed operator delete 0x0002FD60, then erase the whole range
// through the rowed vector<void *>::erase 0x0031BD55. Vector member offsets are target facts
// (+0x124 / +0x14 / +0x170 read off the lea); the owning classes are unproven, so the receivers
// keep address names. deleteInstance spelling follows Rva001095B2Dtor.cpp (slot 0 with 0).
#include <vector>

class OwnedObject
{
public:
	virtual void *deleteInstance(int pool);
};

class Rva002B7B71
{
public:
	void rva002B7B71();
private:
	char m_pad[0x124];
	_STL::vector<void *> m_124;
};

void Rva002B7B71::rva002B7B71()
{
	_STL::vector<void *> *v = &m_124;
	for (unsigned int i = 0; i < m_124.size(); ++i) {
		OwnedObject *object = (OwnedObject *)m_124[i];
		::operator delete(object ? object->deleteInstance(0) : 0);
	}
	v->erase(v->begin(), v->end());
}

class Rva003B9132
{
public:
	void rva003B9132();
private:
	char m_pad[0x14];
	_STL::vector<void *> m_14;
};

void Rva003B9132::rva003B9132()
{
	_STL::vector<void *> *v = &m_14;
	for (unsigned int i = 0; i < m_14.size(); ++i) {
		OwnedObject *object = (OwnedObject *)m_14[i];
		::operator delete(object ? object->deleteInstance(0) : 0);
	}
	v->erase(v->begin(), v->end());
}

class Rva003F2106
{
public:
	void rva003F2106();
private:
	char m_pad[0x170];
	_STL::vector<void *> m_170;
};

void Rva003F2106::rva003F2106()
{
	_STL::vector<void *> *v = &m_170;
	for (unsigned int i = 0; i < m_170.size(); ++i) {
		OwnedObject *object = (OwnedObject *)m_170[i];
		::operator delete(object ? object->deleteInstance(0) : 0);
	}
	v->erase(v->begin(), v->end());
}
