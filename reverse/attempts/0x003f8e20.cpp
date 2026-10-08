// ??1Rva003F8E20@@UAE@XZ
// partial score=0.88 date=2026-10-08
// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B07: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x00362EAB  0x00362E1C  0x00C17088#0
//   0x00367E0A  0x00367E26  0x00C17600#0
//   0x0036C693  0x0036B8E6  0x00C17A80#0
//   0x00373800  0x0037343B  0x00C17DD0#0
//   0x00373B54  0x0037381C  0x00C17E14#0
//   0x0037BD0F  0x0037BB53  0x00C187C0#0
//   0x0037BD48  0x0037BBED  0x00C18828#0
//   0x0038745D  0x00386374  0x00C19500#0
//   0x0038ADC6  0x0038ADE2  0x00C1989C#0
//   0x003AE9BF  0x003ABA4C  0x00C1D588#0
//   0x003B01EC  0x003B00D6  0x00C1D8F0#0
//   0x003B055C  0x003B0344  0x00C1D9B0#0
//   0x003B93A0  0x003B923B  0x00C1FB04#0
//   0x003ED249  0x003ED1FC  0x00C36100#0
//   0x003EE3E2  0x003EE1BE  0x00C3613C#0
//   0x003EF44B  0x003EF36E  0x00C363D8#0
//   0x003F36EC  0x003F332E  0x00C36FA4#0
//   0x003F6CDD  0x003F6A91  0x00C3709C#0
//   0x003F8DC0  0x003F8728  0x00C37314#0
//   0x003F8DDC  0x003F87A9  0x00C37318#0
//   0x003F901B  0x003F8E20  0x00C3731C#0
//   0x003F9DBE  0x003F9D08  0x00C375F0#0
//   0x003FD173  0x003FCE38  0x00C37C30#0
//   0x003FE5F3  0x003FE58A  0x00C37E48#0

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

extern "C" void __cdecl free(void *);

struct EmitVtableTag;

class Rva00362E1C
{
public:
	Rva00362E1C(EmitVtableTag *);
public:
	virtual ~Rva00362E1C();
};

// ?<Rva00362E1C::Rva00362E1C> absent-from-retail
Rva00362E1C::Rva00362E1C(EmitVtableTag *)
{
}

class Rva00367E26
{
public:
	Rva00367E26(EmitVtableTag *);
public:
	virtual ~Rva00367E26();
};

// ?<Rva00367E26::Rva00367E26> absent-from-retail
Rva00367E26::Rva00367E26(EmitVtableTag *)
{
}

class Rva0036B8E6
{
public:
	Rva0036B8E6(EmitVtableTag *);
public:
	virtual ~Rva0036B8E6();
};

// ?<Rva0036B8E6::Rva0036B8E6> absent-from-retail
Rva0036B8E6::Rva0036B8E6(EmitVtableTag *)
{
}

class Rva0037343B
{
public:
	Rva0037343B(EmitVtableTag *);
public:
	virtual ~Rva0037343B();
};

// ?<Rva0037343B::Rva0037343B> absent-from-retail
Rva0037343B::Rva0037343B(EmitVtableTag *)
{
}

class Rva0037381CBase0
{
public:
	virtual ~Rva0037381CBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class Rva0037381CBaseC
{
public:
	virtual ~Rva0037381CBaseC();
};
class Rva0037381C : public Rva0037381CBase0, public Rva0037381CBaseC
{
public:
	Rva0037381C(EmitVtableTag *);
public:
	virtual ~Rva0037381C();
};

// ?<Rva0037381C::Rva0037381C> absent-from-retail
Rva0037381C::Rva0037381C(EmitVtableTag *)
{
}

class Rva0037BB53
{
public:
	Rva0037BB53(EmitVtableTag *);
public:
	virtual ~Rva0037BB53();
};

// ?<Rva0037BB53::Rva0037BB53> absent-from-retail
Rva0037BB53::Rva0037BB53(EmitVtableTag *)
{
}

class Rva0037BBED
{
public:
	Rva0037BBED(EmitVtableTag *);
public:
	virtual ~Rva0037BBED();
};

// ?<Rva0037BBED::Rva0037BBED> absent-from-retail
Rva0037BBED::Rva0037BBED(EmitVtableTag *)
{
}

class Rva00386374
{
public:
	Rva00386374(EmitVtableTag *);
public:
	virtual ~Rva00386374();
};

// ?<Rva00386374::Rva00386374> absent-from-retail
Rva00386374::Rva00386374(EmitVtableTag *)
{
}

class Rva0038ADE2
{
public:
	Rva0038ADE2(EmitVtableTag *);
public:
	virtual ~Rva0038ADE2();
};

// ?<Rva0038ADE2::Rva0038ADE2> absent-from-retail
Rva0038ADE2::Rva0038ADE2(EmitVtableTag *)
{
}

class Rva003ABA4CBase0
{
public:
	virtual ~Rva003ABA4CBase0();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) in its vtable is target evidence for it.
class Rva003ABA4CBase18
{
public:
	virtual ~Rva003ABA4CBase18();
};
class Rva003ABA4C : public Rva003ABA4CBase0, public Rva003ABA4CBase18
{
public:
	Rva003ABA4C(EmitVtableTag *);
public:
	virtual ~Rva003ABA4C();
};

// ?<Rva003ABA4C::Rva003ABA4C> absent-from-retail
Rva003ABA4C::Rva003ABA4C(EmitVtableTag *)
{
}

class Rva003B00D6
{
public:
	Rva003B00D6(EmitVtableTag *);
public:
	virtual ~Rva003B00D6();
};

// ?<Rva003B00D6::Rva003B00D6> absent-from-retail
Rva003B00D6::Rva003B00D6(EmitVtableTag *)
{
}

class Rva003B0344
{
public:
	Rva003B0344(EmitVtableTag *);
public:
	virtual ~Rva003B0344();
};

// ?<Rva003B0344::Rva003B0344> absent-from-retail
Rva003B0344::Rva003B0344(EmitVtableTag *)
{
}

class Rva003B923BBase0
{
public:
	virtual ~Rva003B923BBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x003B912A in its vtable is target evidence for it.
class Rva003B923BBaseC
{
public:
	virtual ~Rva003B923BBaseC();
};
class Rva003B923B : public Rva003B923BBase0, public Rva003B923BBaseC
{
public:
	Rva003B923B(EmitVtableTag *);
public:
	virtual ~Rva003B923B();
};

// ?<Rva003B923B::Rva003B923B> absent-from-retail
Rva003B923B::Rva003B923B(EmitVtableTag *)
{
}

class Rva003ED1FC
{
public:
	Rva003ED1FC(EmitVtableTag *);
public:
	virtual ~Rva003ED1FC();
};

// ?<Rva003ED1FC::Rva003ED1FC> absent-from-retail
Rva003ED1FC::Rva003ED1FC(EmitVtableTag *)
{
}

class Rva003EE1BE
{
public:
	Rva003EE1BE(EmitVtableTag *);
public:
	virtual ~Rva003EE1BE();
};

// ?<Rva003EE1BE::Rva003EE1BE> absent-from-retail
Rva003EE1BE::Rva003EE1BE(EmitVtableTag *)
{
}

class Rva003EF36E
{
public:
	Rva003EF36E(EmitVtableTag *);
public:
	virtual ~Rva003EF36E();
};

// ?<Rva003EF36E::Rva003EF36E> absent-from-retail
Rva003EF36E::Rva003EF36E(EmitVtableTag *)
{
}

struct Elem003B2540
{
	char m_pad[8];
	int m_key;
	char m_pad2[12];
};
namespace _STL {
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
    ~vector();
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
	T *erase(T *);
    T *erase(T *, T *);
    T *begin() { return _M_start; }
    T *end() { return _M_finish; }
};
}

class Rva003F332E
{
public:
	Rva003F332E(EmitVtableTag *);
public:
	virtual ~Rva003F332E();
	Elem003B2540 *rva003F3708(int key);

	char m_pad[0x1a8 - 4];
	_STL::vector<Elem003B2540> m_vec;
};

// ?<Rva003F332E::Rva003F332E> absent-from-retail
Rva003F332E::Rva003F332E(EmitVtableTag *)
{
}

// ?rva003F3708@Rva003F332E@@QAEPAUElem003B2540@@H@Z @0x003F3708 49B
Elem003B2540 *Rva003F332E::rva003F3708(int key)
{
	Elem003B2540 *it = m_vec._M_start;
	Elem003B2540 *end = m_vec._M_finish;
	if (it == end)
		return it;
	do {
		if (it->m_key == key)
			return m_vec.erase(it);
		++it;
	} while (it != end);
	return it;
}

// ?clear@ConnectionVec@@QAEXXZ @0x003F3739 11B
class LivingWorldRegionConnection;
struct ConnectionVec
{
	LivingWorldRegionConnection *m_start;
	LivingWorldRegionConnection *m_finish;
	LivingWorldRegionConnection *m_end;
	LivingWorldRegionConnection *rva003F35B0(LivingWorldRegionConnection *a, LivingWorldRegionConnection *b);
	void clear();
};

void ConnectionVec::clear()
{
	rva003F35B0(m_start, m_finish);
}

class Rva003F6A91
{
public:
	Rva003F6A91(EmitVtableTag *);
public:
	virtual ~Rva003F6A91();
};

// ?<Rva003F6A91::Rva003F6A91> absent-from-retail
Rva003F6A91::Rva003F6A91(EmitVtableTag *)
{
}

class Rva003F8728
{
public:
	Rva003F8728(EmitVtableTag *);
public:
	virtual ~Rva003F8728();
};

// ?<Rva003F8728::Rva003F8728> absent-from-retail
Rva003F8728::Rva003F8728(EmitVtableTag *)
{
}

class Rva003F87A9
{
public:
	Rva003F87A9(EmitVtableTag *);
public:
	virtual ~Rva003F87A9();
};

// ?<Rva003F87A9::Rva003F87A9> absent-from-retail
Rva003F87A9::Rva003F87A9(EmitVtableTag *)
{
}

// Target 0x003F8E20: notify the +4 listener list with this, process the
// +0x14 pointer range through the existing by-value-box provider, then free
// both buffers and restore the already rowed 0x00C37298 base vtable.
class Rva003F7BCC
{
public:
    virtual ~Rva003F7BCC() {}
};
class Rva003F86B6Listener { public: virtual void notify(void *); };
class Rva003F86B6List
{
public:
    Rva003F86B6Listener **begin, **end, **capacity;
    unsigned int index;
    void forEach(void (Rva003F86B6Listener::*notify)(void *), void *);
    ~Rva003F86B6List() { if (begin) free(begin); }
};
class FileClass;
struct Rva0059E2DCBox { bool flag; };
bool __cdecl rva0059E2DC(FileClass **, FileClass **, Rva0059E2DCBox);
struct Rva003F8E20FileVector
{
    FileClass **begin, **end, **capacity;
    __forceinline ~Rva003F8E20FileVector()
    {
        rva0059E2DC(begin, end, Rva0059E2DCBox());
        if (begin) free(begin);
    }
};
class Rva003F8E20 : public Rva003F7BCC
{
public:
    Rva003F8E20(EmitVtableTag *);
    virtual ~Rva003F8E20();
    Rva003F86B6List listeners04;
    Rva003F8E20FileVector files14;
};

Rva003F8E20::~Rva003F8E20()
{
    listeners04.forEach(&Rva003F86B6Listener::notify, this);
}

// ?<Rva003F8E20::Rva003F8E20> absent-from-retail
Rva003F8E20::Rva003F8E20(EmitVtableTag *)
{
}

// Retail performs an explicit clear before ordinary member destruction.
// releaseBuffer nulls each string pointer; the subsequent automatic release
// is consequently safe. The final vptr store proves the Snapshot base.
extern "C" void __cdecl free(void *);
struct BfmePod8 { unsigned int words[2]; };
namespace _STL {
template <> inline vector<BfmePod8>::~vector()
{
    if (_M_start) free(_M_start);
}
}
class Rva003F9D08 : public Snapshot
{
public:
    Rva003F9D08(EmitVtableTag *);
    virtual ~Rva003F9D08();
    AsciiString string04, string08, string0C, string10;
    char unmodelled14[0x3C-0x14];
    _STL::vector<BfmePod8> vector3C;
};

Rva003F9D08::~Rva003F9D08()
{
    string04.clear();
    string08.clear();
    string0C.clear();
    string10.clear();
    _STL::vector<BfmePod8> *vector = &vector3C;
    vector->erase(vector->begin(), vector->end());
}

// ?<Rva003F9D08::Rva003F9D08> absent-from-retail
Rva003F9D08::Rva003F9D08(EmitVtableTag *)
{
}

// Target 0x003FCE38 assigns the shared empty string at +4, calls the
// existing unresolved operation 0x003FCD71, unregisters this pointer from
// the 0x00DFE1C8 singleton, and conditionally unlinks its +0x1C handle.
// The owner name is deliberately retained from the rowed deleting wrapper.
class RvaSmartPtr12 { public: __declspec(nothrow) void rva0004CBC0(); };
struct Rva003FCE38Handle
{
    void *system, *previous, *next;
    ~Rva003FCE38Handle() throw()
    {
        if (system) ((RvaSmartPtr12 *)this)->rva0004CBC0();
    }
};
class Rva003FCD71 { public: void rva003FCD71(); };
class CreateAHeroData;
class Rva00211541 { public: void rva00211541(CreateAHeroData *); };
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class Rva003FCE38
{
public:
    Rva003FCE38(EmitVtableTag *);
    virtual ~Rva003FCE38();
    AsciiString string04;
    char unmodelled08[0x1C-8];
    Rva003FCE38Handle handle1C;
};

Rva003FCE38::~Rva003FCE38()
{
    string04 = AsciiString::TheEmptyString;
    ((Rva003FCD71 *)this)->rva003FCD71();
    if (TheLivingWorldManager)
        ((Rva00211541 *)TheLivingWorldManager)->rva00211541((CreateAHeroData *)this);
}

// ?<Rva003FCE38::Rva003FCE38> absent-from-retail
Rva003FCE38::Rva003FCE38(EmitVtableTag *)
{
}

// Retail destructor at 0x003FE58A proves base cleanup at 0x0053947D,
// pointer buffer at +0x2C, record vector at +0x3C, and counted ref at +0x4C.
// The record-vector call 0x00538E3E is a direct JMP to its rowed destructor
// 0x00319B58; it retains that provider's established STLport spelling.
class Rva0053947D
{
public:
    virtual ~Rva0053947D();
    virtual void v01(); virtual void rva005391D3(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual int v13(); virtual void v14(); virtual void *v15(int);
    char unmodelled04[0x10];
};
class Rva0052B23D { public: void rva0052B23D(); };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
extern "C" void __cdecl free(void *);
struct Rva003FE58ABuffer
{
    void *begin, *end, *capacity;
    ~Rva003FE58ABuffer() { if (begin) free(begin); }
};
struct Rva003FE58ARef
{
    TargetRef00217D4C *ref;
    ~Rva003FE58ARef() { if (ref) ReleaseTreeHintRef00217D4C(ref); }
};
struct BfmeVectorRecord00319C84;
class Rva003FE58A : public Rva0053947D
{
public:
    Rva003FE58A(EmitVtableTag *);
    virtual ~Rva003FE58A();
    char unmodelled14[0x18];
    Rva003FE58ABuffer buffer;
    char unmodelled38[4];
    _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > records;
    char unmodelled48[4];
    Rva003FE58ARef ref;
};

Rva003FE58A::~Rva003FE58A()
{
    ((Rva0052B23D *)this)->rva0052B23D();
}

// ?<Rva003FE58A::Rva003FE58A> absent-from-retail
Rva003FE58A::Rva003FE58A(EmitVtableTag *)
{
}
