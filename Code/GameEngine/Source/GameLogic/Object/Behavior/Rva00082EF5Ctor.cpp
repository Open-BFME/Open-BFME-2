// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva00082EF5@@QAE@PAX@Z @0x00082EF5 117B: MI ctor with second base at +8 plus vector float bool plus list append and init call. Evidence: vtable stores plus vector base row plus append row plus pin 0x82D6A plus callers 0x82F81 0x8355E.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
void Rva00030830FreeAllocation(void*);
namespace _STL {
 template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *p,size_type) const { if(p) Rva00030830FreeAllocation(p); }
}


struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

class Rva00082D6A
{
public:
	void rva00082D6A();
};

class Rva00082EF5Second
{
public:
	Rva00082EF5Second();
	virtual ~Rva00082EF5Second() {}
};
// ??0Rva00082EF5Second@@QAE@XZ @0x0007E056 9B: the default constructor, storing the
// class's own vtable (VA 0x00BC6EEC) and returning this.
Rva00082EF5Second::Rva00082EF5Second()
{
}

class Rva00082EF5Base1
{
public:
	Rva00082EF5Base1() : m_04(0) {}
	virtual ~Rva00082EF5Base1() {}
	int m_04;
};

class Rva00082EF5 : public Rva00082EF5Base1, public Rva00082EF5Second
{
public:
	Rva00082EF5(void *mgr);
	virtual ~Rva00082EF5();
private:
	void *m_mgr0C;
	float m_flt10;
	_STL::vector<BfmeE16> m_vec14;
	bool m_flag20;
};

Rva00082EF5::Rva00082EF5(void *mgr)
	: Rva00082EF5Base1()
	, Rva00082EF5Second()
	, m_mgr0C(mgr)
	, m_flt10(0.0f)
	, m_vec14()
	, m_flag20(false)
{
	((Rva005A0B4CList *)((char *)mgr + 8))->append((Rva002BA8F1Listener *)((char *)this + 8));
	((Rva00082D6A *)this)->rva00082D6A();
}

class CreateAHeroData;
class Rva002B7250 {public:void rva002B7250(CreateAHeroData*);};
// Native81C7F..81CDF96B is the primary-base destructor required by both
// native water constructors. It unregisters its +8 listener then tears down
// vector14 and both base vptrs; the owner name remains address-derived.
// ??1Rva00082EF5@@UAE@XZ
Rva00082EF5::~Rva00082EF5()
{
 reinterpret_cast<Rva002B7250*>(reinterpret_cast<char*>(m_mgr0C)+8)->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<Rva00082EF5Second*>(this)));
}

// ??1Rva008291D@@UAE@XZ, native 0x0008291D..0x00082A53 (310 bytes), the
// destructor the rowed ??_GRva008291D (0x00082C6C) calls. Target facts: the
// class extends a 0x3C-byte primary built on Rva00082EF5 (vtables 0x00BC7364
// at +0 and 0x00BC734C at +8; its destructor 0x00081C7F runs last) with a
// second base at +0x3C (0x00BC7330, reset to 0x00BC6F04). It leaves the +0x40
// owner's +0x68 observer list, clears +0x18 on every pointer of the +0x58 set
// (node walk through _Rb_global::_M_increment), runs the rowed cleanup
// 0x00081F03, then unwinds twelve EH states: five POD vectors (+0x64..+0x94),
// the set (0x0007E971), two RefCountPtr<TextureClass> (+0x50, 0x0017098D)
// and three texture references (+0x44..+0x4C, Release_Ref 0x0021ED10).
// Member roles are structural inference.
#include <set>
class Rva00081F03 { public: void rva00081F03(); };
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass;
template <class T> class RefCountPtr
{
public:
	~RefCountPtr();
	T *m_ptr;
};
struct Rva008291DTextureRef
{
	~Rva008291DTextureRef() { if (m_ptr) m_ptr->Release_Ref(); }
	TextureBaseClass *m_ptr;
};
struct Rva008291DItem
{
	unsigned char m_pad00[0x18];
	int m_18;
};
struct Rva0007E971 : public _STL::set<Rva008291DItem *>
{
	~Rva0007E971();
};
class Rva008291DPrimary : public Rva00082EF5
{
	unsigned char m_pad24[0x3C - 0x24];
};
class Rva008291DSecond
{
public:
	virtual ~Rva008291DSecond() {}
};
class Rva008291D : public Rva008291DPrimary, public Rva008291DSecond
{
public:
	virtual ~Rva008291D();
private:
	void *m_owner40;
	Rva008291DTextureRef m_44;
	Rva008291DTextureRef m_48;
	Rva008291DTextureRef m_4C;
	RefCountPtr<TextureClass> m_50[2];
	Rva0007E971 m_58;
	_STL::vector<BfmeE16> m_64;
	_STL::vector<BfmeE16> m_70;
	_STL::vector<BfmeE16> m_7C;
	_STL::vector<BfmeE16> m_88;
	_STL::vector<BfmeE16> m_94;
};

Rva008291D::~Rva008291D()
{
	reinterpret_cast<Rva002B7250 *>(reinterpret_cast<char *>(m_owner40) + 0x68)->rva002B7250(reinterpret_cast<CreateAHeroData *>(static_cast<Rva008291DSecond *>(this)));
	for (Rva0007E971::iterator it = m_58.begin(); it != m_58.end(); ++it)
	{
		if (*it)
			(*it)->m_18 = 0;
	}
	reinterpret_cast<Rva00081F03 *>(this)->rva00081F03();
}
