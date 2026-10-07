// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <list>

template <> _STL::_List_base<int, _STL::allocator<int> >::~_List_base();

class Rva0053470B
{
public:
	~Rva0053470B();
};
// Scalar deleting destructors that retail keeps but never references: no
// vtable slot, call or jmp reaches them. Each is the 28B shape that calls
// the complete destructor, tests bit 0 of the flags, frees through
// operator delete 0x0002FD60 and returns this with ret 4. Each class is
// declared locally only so its deleting destructor is emitted; the
// destructor call resolves through an address-derived pin in
// reverse/symbols.csv read from the wrapper's own REL32. Owner identities
// and layouts are not recovered.

// ??_GRva004D2344@@QAEPAXI@Z @0x0025DEE5 28B: calls ~Rva004D2344 0x004D2344
class Rva004D2344 { public: ~Rva004D2344(); };
void famgenDelete(Rva004D2344 *p) { delete p; }

// ??_GRva00200667@@QAEPAXI@Z @0x002821B3 28B: calls ~Rva00200667 0x00200667
class Rva00200667 { public: ~Rva00200667(); };
void famgenDelete(Rva00200667 *p) { delete p; }

// ??_GRva00288B89@@QAEPAXI@Z @0x00288B9E 28B: calls ~Rva00288B89 0x00288B89
class Rva00288B89 { public: ~Rva00288B89(); };
void famgenDelete(Rva00288B89 *p) { delete p; }

// ??_GRva00289706@@QAEPAXI@Z @0x00289BC4 28B: calls ~Rva00289706 0x00289706
class Rva00289706 { public: ~Rva00289706(); };
void famgenDelete(Rva00289706 *p) { delete p; }

// ??_GRva004DDF3A@@QAEPAXI@Z @0x0028AB32 28B: calls ~Rva004DDF3A 0x004DDF3A
class Rva004DDF3A { public: ~Rva004DDF3A(); };
void famgenDelete(Rva004DDF3A *p) { delete p; }

// ??_GRva004E9657@@QAEPAXI@Z @0x002A8A49 28B: calls ~Rva004E9657 0x004E9657
class Rva004E9657 { public: ~Rva004E9657(); };
void famgenDelete(Rva004E9657 *p) { delete p; }

// ??_GRva004E013B@@QAEPAXI@Z @0x002A8A65 28B: calls ~Rva004E013B 0x004E013B
class Rva004E013B { public: ~Rva004E013B(); };
void famgenDelete(Rva004E013B *p) { delete p; }

// ??_GRva001EB63C@@QAEPAXI@Z @0x002AD057 28B: calls ~Rva001EB63C 0x001EB63C
class Rva001EB63C { public: ~Rva001EB63C(); };
void famgenDelete(Rva001EB63C *p) { delete p; }

// ??_GRva0053476A@@QAEPAXI@Z @0x002E7FAB 28B: calls ~Rva0053476A 0x0053476A
class Rva0053476A
{
public:
	~Rva0053476A();

private:
	_STL::list<int> m_list;
	Rva0053470B m_member;
};
void famgenDelete(Rva0053476A *p) { delete p; }

// ??1Rva0053476A@@QAE@XZ @0x0053476A 53B
// Target evidence: EH prolog 0x00629188; calls 0x0053470B on this+4, then the rowed
// _List_base<int> destructor at 0x004EC395 on this; then restores the SEH frame.
// Structural inference: model the +0 subobject as list<int> and the +4 subobject by its
// address-derived destructor. Owner identity and remaining object layout are unknown.
Rva0053476A::~Rva0053476A()
{
}

// ??_GRva0056A061@@QAEPAXI@Z @0x003EDBFA 28B: calls ~Rva0056A061 0x0056A061
class Rva0056A061 { public: ~Rva0056A061(); };
void famgenDelete(Rva0056A061 *p) { delete p; }

// ??_GRva0056C3E5@@QAEPAXI@Z @0x00404A0D 28B: calls ~Rva0056C3E5 0x0056C3E5
class Rva0056C3E5 { public: ~Rva0056C3E5(); };
void famgenDelete(Rva0056C3E5 *p) { delete p; }

// ??_GRva00415AE0@@QAEPAXI@Z @0x00415C68 28B: calls ~Rva00415AE0 0x00415AE0
class Rva00415AE0 { public: ~Rva00415AE0(); };
void famgenDelete(Rva00415AE0 *p) { delete p; }

// ??_GRva0042D92E@@QAEPAXI@Z @0x0042DFD9 28B: calls ~Rva0042D92E 0x0042D92E
class Rva0042D92E { public: ~Rva0042D92E(); };
void famgenDelete(Rva0042D92E *p) { delete p; }

// ??_GRva001EB940@@QAEPAXI@Z @0x0046ACDA 28B: calls ~Rva001EB940 0x001EB940
class Rva001EB940 { public: ~Rva001EB940(); };
void famgenDelete(Rva001EB940 *p) { delete p; }

// ??_GRva004DCE8E@@QAEPAXI@Z @0x004B0D0C 28B: calls ~Rva004DCE8E 0x004DCE8E
class Rva004DCE8E { public: ~Rva004DCE8E(); };
void famgenDelete(Rva004DCE8E *p) { delete p; }

// Target facts: 0x0052BBD7 is a complete 28B scalar deleting wrapper. Its
// direct destructor call at +3 reaches 0x004E366E, then it tests flag bit 0,
// conditionally calls operator delete, returns this, and uses ret 4. The
// existing Rva004E364F constructor is at 0x004E364F, and the destructor pin
// for that view maps to 0x004E366E. Inference: this wrapper belongs to that
// class; its layout and broader owner remain unclaimed.
// ??_GRva004E364F@@QAEPAXI@Z @0x0052BBD7 28B
class Rva004E364F { public: ~Rva004E364F(); };
void famgenDelete(Rva004E364F *p) { delete p; }
