// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc
//
// ?rva005D5001@Rva005D5001@@QAEXABUTreeHintRef00217D4C@@@Z, retail
// 0x005D5001..0x005D508E (141B), thiscall ret 4.
//
// Rebinds the object: runs its rowed reset 0x005D4F0E, copies the given
// handle into +0x08, builds a bound-method callback to its own 0x005D4F27
// through the rowed delegate constructor 0x00579E47, and registers that
// callback under the handle's name (slot 3 of the handle target, as a
// temporary string) through 0x0057C394.
//
// Codegen notes: the descriptor is built by a helper, whose parameter copy
// gives retail's method-first store through EAX, and the name is a
// temporary, which lets it reuse the dead argument slot as retail does. The
// const-reference argument is a compatible four-byte borrowed-handle view,
// not a proven original spelling; names are address-derived.
#include "ascii_string.h"
struct TargetRef00217D4C {virtual void f0();virtual void f1();virtual void f2();virtual const char *f3();};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {TargetRef00217D4C *m_ptr;TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C&);};
class __single_inheritance Rva005D4F0E;
typedef void (Rva005D4F0E::*BoundMethod)(int,int);
#include "../../Include/Common/DelegateDesc.h"
template <class T> inline DelegateDesc MakeDesc(void *object, void (T::*method)(int,int)) { DelegateDesc desc; desc.field00 = object; desc.field04 = *reinterpret_cast<void **>(&method); return desc; }
class Rva00579E47:public TreeHintRef00217D4C {
public:Rva00579E47(const DelegateDesc&);~Rva00579E47(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
};
class Rva005D4F0E {public:void rva005D4F0E();void rva005D4F27(int,int);};
#include "../../Include/Common/Rva0057C394.h"
class Rva005D5001 {
public:void rva005D5001(const TreeHintRef00217D4C&);
private:char prefix[8];TreeHintRef00217D4C m_08;
};
void Rva005D5001::rva005D5001(const TreeHintRef00217D4C &arg) {
 ((Rva005D4F0E*)this)->rva005D4F0E();
 m_08=arg;
 Rva00579E47 dlg(MakeDesc(this,&Rva005D4F0E::rva005D4F27));
 ((Rva0057C394*)this)->rva0057C394(AsciiString(m_08.m_ptr->f3()),dlg);
}
