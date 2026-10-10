// cl: /O1 /G7 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Owned-pointer list teardown, native copies of one shape: walk a
// vector<void *> of polymorphic owned objects, run each one's slot-0 deleteInstance(0) (null
// elements pass null) into the rowed operator delete 0x0002FD60, then erase the whole range
// through the rowed vector<void *>::erase 0x0031BD55. Vector member offsets are target facts
// (+0x124 / +0x14 / +0x170 read off the lea); the owning classes are unproven, so the receivers
// keep address names. deleteInstance spelling follows Rva001095B2Dtor.cpp (slot 0 with 0).
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

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

// Native 0x0020F685: the identical teardown applied twice in one receiver —
// the owned list at +0x14, then the one at +0x20 (so the second vector starts
// exactly where the first's 12 bytes end). Both member addresses are cached in
// ESI, `this` has to survive the first erase so retail parks it in EBX and
// delays EDI's save until the loop that uses it, and the second `v` is re-derived
// only after the second loop — re-deriving it before the loop keeps `this`
// dead too early and MSVC swaps the two callee-saved registers.
class Rva0020F685
{
public:
	void rva0020F685();
private:
	char m_pad[0x14];
	_STL::vector<void *> m_14;
	_STL::vector<void *> m_20;
};

void Rva0020F685::rva0020F685()
{
	_STL::vector<void *> *v = &m_14;
	for (unsigned int i = 0; i < m_14.size(); ++i) {
		OwnedObject *object = (OwnedObject *)m_14[i];
		::operator delete(object ? object->deleteInstance(0) : 0);
	}
	v->erase(v->begin(), v->end());
	for (unsigned int i = 0; i < m_20.size(); ++i) {
		OwnedObject *object = (OwnedObject *)m_20[i];
		::operator delete(object ? object->deleteInstance(0) : 0);
	}
	v = &m_20;
	v->erase(v->begin(), v->end());
}
