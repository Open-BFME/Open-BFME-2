// ?rva005D5001@Rva005D5001@@QAEXABUTreeHintRef00217D4C@@@Z
// partial score=0.9 date=2026-10-09
// ?rva005D5001@Rva005D5001@@QAEXABUTreeHintRef00217D4C@@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc
// Partial0.9: native141B; fresh140B all six calls resolve with genuine
// delegate constructor and symbolic callback member address. Constructor EH
// guard now starts after call, matching target; remaining frame16 versus12
// and local AsciiString(-10) versus dead argument(+8), plus direct-immediate
// method store versus native EAX store. /EHa leaves these unchanged.
// Original bank supplied semantic/layout guide; const-reference argument is
// a compatible four-byte borrowed-handle view, not proven original spelling.
#include "ascii_string.h"
struct TargetRef00217D4C {virtual void f0();virtual void f1();virtual void f2();virtual const char *f3();};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {TargetRef00217D4C *m_ptr;TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C&);};
struct DelegateDesc {void *m_object;void *m_method;};
class Rva00579E47:public TreeHintRef00217D4C {
public:Rva00579E47(const DelegateDesc&);~Rva00579E47(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
};
class Rva005D4F0E {public:void rva005D4F0E();};
class Rva005D4F27 {public:void rva005D4F27(int,int);};
class Rva0057C394 {public:void rva0057C394(const AsciiString&,const TreeHintRef00217D4C&);};
class Rva005D5001 {
public:void rva005D5001(const TreeHintRef00217D4C&);
private:char prefix[8];TreeHintRef00217D4C m_08;
};
void Rva005D5001::rva005D5001(const TreeHintRef00217D4C &arg) {
 ((Rva005D4F0E*)this)->rva005D4F0E();
 m_08=arg;
 union MemberCode {void *raw;void(Rva005D4F27::*method)(int,int);} code;
 code.method=&Rva005D4F27::rva005D4F27;
 DelegateDesc desc;
 desc.m_object=this;desc.m_method=code.raw;
 Rva00579E47 dlg(desc);
 AsciiString name(m_08.m_ptr->f3());
 ((Rva0057C394*)this)->rva0057C394(name,dlg);
}
