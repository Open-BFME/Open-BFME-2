// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// ?rva005E5424@Rva005E39AE@@QAEXXZ @0x005E5424 122B
// Banked attempt reverse/attempts/0x005e5424.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// Candidate RVA 0x005E5424..0x005E549E, 122 bytes, discovered by reseeding.
// All bytes match in an isolated compile when relocation operands are masked.
// NOT LANDED: initialization helper 0x005E52FD and global VA 0x00E06710
// still lack linkable definitions. No pin is added just to satisfy the caller.
// Existing Rva005E39AE methods prove the same +0x18 object, +0x28 count,
// +0x2C initialization flag and +0x2D update flag; this body reads tree header
// +0x1C, leftmost link +8 and node value +0x14, with _Rb_global::_M_increment.
// The node key and application class names remain unknown. Only pointer width
// and offsets are observed; opaqueKey carries no inferred key semantics.
// Retail adjusts a non-null receiver through vbtable[1], then calls the
// existing MSVC vcall thunk +0x10. Ordinary virtual-base casts made VC7.1
// insert an extra null branch, so virtualBase() spells that observed ABI.
// The final call translates the label holder via recovered rva005E3E1D and
// calls the established Mouse tooltip setter. The global's destructor is
// rowed at 0x005E3DE8, but its constructor at 0x005E3D95 (83B) and initializer
// at 0x007B5000 (22B) are not recovered. Raw immediate search locates both;
// constructor string is "ArmyDetailsPanel", vtable VA 0x00C77CC4. Neither
// the seed inventory nor this masked match proves a complete global owner.
// stlport
#include <map>
#include "unicode_string.h"
class Rva005E5424Base { public: virtual void s0(); virtual void s4(); virtual void s8(); virtual void sC(); virtual void s10(); };
struct Rva005E5424Value { const int *vbtable;
 Rva005E5424Base &virtualBase() { return *reinterpret_cast<Rva005E5424Base*>(reinterpret_cast<char*>(this)+vbtable[1]); }
};
struct Rva005E5424Node : _STL::_Rb_tree_node_base { unsigned opaqueKey; Rva005E5424Value *value; };
class Rva005F2767 { public: bool rva005F2767() const; };
class Rva005E3DE8 { public: UnicodeString rva005E3E1D(); };
struct RGBColor;
class Mouse { public: void rva001EEA6D(UnicodeString,int,const RGBColor*,float); };
extern Mouse *TheMouse;
extern unsigned g_Va00E06710;
class Rva005E39AE { public:
 void rva005E39AE(); void rva005E52FD(); void rva005E5424();
 char pad00[0x18]; Rva005F2767 *m_18; Rva005E5424Node *m_1c;
 char pad20[0xc]; bool m_2c,m_2d;
};
void Rva005E39AE::rva005E5424() {
 if(!m_2c) rva005E52FD();
 Rva005E5424Node *end=m_1c;
 for(Rva005E5424Node *node=(Rva005E5424Node*)end->_M_left;node!=end;node=(Rva005E5424Node*)_STL::_Rb_global<bool>::_M_increment(node)) {
  void (Rva005E5424Base::*action)()=&Rva005E5424Base::s10;
  (node->value->virtualBase().*action)();
 }
 if(m_2d) rva005E39AE();
 if(m_18->rva005F2767()) TheMouse->rva001EEA6D(((Rva005E3DE8*)&g_Va00E06710)->rva005E3E1D(),-1,0,1.0f);
}

// ?rva005E549E@Rva005E549E@@QAEXXZ @0x005E549E 8B: the member forwarder that
// follows -- the object at +0x10 runs the 0x005E5424 above. Retail's vtable
// reaches it directly (0x00877D08) and through an adjustor thunk (0x005E54A6,
// this-8; 0x00877D04).
class Rva005E549E
{
public:
	void rva005E549E();
private:
	unsigned char m_pad00[0x10];
	Rva005E39AE *m_10;
};

void Rva005E549E::rva005E549E()
{
	m_10->rva005E5424();
}
