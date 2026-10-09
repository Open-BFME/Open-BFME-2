// ??0Rva00524BB4@@QAE@UTreeHintRef00217D4C@@@Z
// partial score=0.97 date=2026-10-09
// ??0Rva00524BB4@@QAE@UTreeHintRef00217D4C@@@Z
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Partial0.97: exact109B size; only MOV ECX,[arg] and flag AND swap.
// Source helpers PlaybackStorage/PlaybackFlags are a compiler-shape model,
// not target class identities. Existing canonical Subsystem and target handle
// calls establish ABI/lifetime; /G6 leaves the scheduling difference unchanged.
// Target109B native524C1B..524C88; matched sibling524B7A and dtor524BB4
// prove sameC67DFC/Subsystem prefix/owned handle34. Old QR callback is refuted.
typedef bool Bool;
#include "subsystem_interface.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C() {}
 TreeHintRef00217D4C(const TreeHintRef00217D4C &other):m_ptr(other.m_ptr) {if(m_ptr) ++m_ptr->references;}
 ~TreeHintRef00217D4C() {if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);}
};
struct PlaybackFlags { unsigned char low:3; unsigned char reserved:5; PlaybackFlags():low(0) {} };
class __declspec(novtable) PlaybackStorage:public SubsystemInterface {
protected:
 __forceinline PlaybackStorage() {m_28=-1;}
 void *m_ptr0C;
 int m_10,m_14,m_18,m_1C,m_20;
 PlaybackFlags flags24;char pad25[3];
 int m_28,m_2C,m_30;
};
class Rva00524BB4:public PlaybackStorage {
public:
 Rva00524BB4(TreeHintRef00217D4C ref);
 virtual ~Rva00524BB4();
 virtual void init();virtual void reset();virtual void update();virtual void vslot12();
private:
 TreeHintRef00217D4C m_ref;
 int m_38;
};
Rva00524BB4::Rva00524BB4(TreeHintRef00217D4C ref) {
 m_ptr0C=0;m_20=0;m_2C=0;m_30=0;
 m_ref.m_ptr=ref.m_ptr;
 if(m_ref.m_ptr) ++m_ref.m_ptr->references;
 m_38=0;m_10=0;m_14=0;m_18=0;m_1C=0;
}
