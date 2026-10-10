// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8573@Rva002B8573@@UAE_NPAVRva003190A5@@@Z @0x002B8573 62B via ref table pattern
// Evidence: REF table slot 0x007FDFEC plus neighbours plus prev LivingWorldLogic plus query row 0x003190A5 plus push_back pin.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
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
	virtual bool rva002B8573(Rva003190A5 *a);
 ~Rva002B8573() {}
 Rva002B8573(_STL::vector<Object*> *v, Rva002B8573Filter *f):m_vec04(v),m_flt08(f) {}
private:
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

// ?rva002B85B1@Rva002B85B1@@UAE_NPAVRva003190A5@@@Z @0x002B85B1 59B via ref table sibling.
// Evidence: REF table slot 0x007FDFF0 plus neighbour rva002B8573 plus query plus push_back.
class Rva002B85B1
{
public:
	virtual bool rva002B85B1(Rva003190A5 *a);
 ~Rva002B85B1() {}
 Rva002B85B1(_STL::vector<Object*> *v, int id):m_vec04(v),m_08(id) {}
private:
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

// Native2B31F2..2B323C74B and2B323C..2B328876B construct the
// 12-byte callback payloads whose single native vtable entries are2B8573
// and2B85B1. WB D7ECE0 also constructs a derived callback with pointer4
// and filter8. These target facts correct the earlier nonvirtual views:
// the vptr replaces the old four-byte padding; full callback bytes remain
// unchanged. Output pointer element names remain the existing caller ABI
// views; application identities and complete class layouts remain open.
class Rva003F498ACallback;
class LivingWorldBattle {public: void rva003F498A(Rva003F498ACallback*);};
class Rva003F468D;
class Rva0020E6B7RegionManager {public:Rva003F468D *rva0020E6B7();};
class Rva002B31F2 {
public: void rva002B31F2(_STL::vector<unsigned int>*);
char pad[0xb0];Rva0020E6B7RegionManager *manager;
};
class Rva0040D701ArmySummary;
class Rva002BA8F1Logic {
public:void rva002B323C(_STL::vector<Rva0040D701ArmySummary*>*,int);
char pad[0xb0];Rva0020E6B7RegionManager *manager;
};
void Rva002B31F2::rva002B31F2(_STL::vector<unsigned int>*out) {
 LivingWorldBattle *battle=(LivingWorldBattle*)manager->rva0020E6B7();
 if(battle){Rva002B8573 callback((_STL::vector<Object*>*)out,0);battle->rva003F498A((Rva003F498ACallback*)&callback);}
}
void Rva002BA8F1Logic::rva002B323C(_STL::vector<Rva0040D701ArmySummary*>*out,int id) {
 LivingWorldBattle *battle=(LivingWorldBattle*)manager->rva0020E6B7();
 if(battle){Rva002B85B1 callback((_STL::vector<Object*>*)out,id);battle->rva003F498A((Rva003F498ACallback*)&callback);}
}
// Native 2B25EF..2B262D, 62B; WB D7EE00 is unnamed. The receiver
// is unused; the explicit battle, output and filter arguments have RET12.
// Preserve the address owner while using the existing proved callback.
class Rva002B25EF {
public: void rva002B25EF(LivingWorldBattle *,_STL::vector<Object *> *,Rva002B8573Filter *);
};
void Rva002B25EF::rva002B25EF(LivingWorldBattle *battle,_STL::vector<Object *> *out,Rva002B8573Filter *filter) {
 Rva002B8573 callback(out,filter);
 battle->rva003F498A((Rva003F498ACallback *)&callback);
}
