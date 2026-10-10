// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
//
// ??0Rva00524BB4@@QAE@UTreeHintRef00217D4C@@@Z, retail 0x00524C1B..0x00524C88
// (109 bytes, EH, ret 4): the 0x3C-byte movie playback subsystem AptPalantir's
// init news with its frame callback (vtable 0x00C67DFC, as the rowed sibling
// constructor 0x00524B7A and destructor 0x00524BB4). SubsystemInterface base,
// then the playback fields; the callback holder taken by value is kept at
// +0x34. Declaring the fields directly in this class (no intermediate base)
// and copying the holder after the zero stores reproduces retail's order:
// the argument load right after the base call, the holder store last.
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
struct PlaybackFlags { unsigned char low:3; unsigned char reserved:5; };
class Rva00524BB4:public SubsystemInterface {
public:
 Rva00524BB4(TreeHintRef00217D4C ref);
 virtual ~Rva00524BB4();
 virtual void init();virtual void reset();virtual void update();virtual void vslot12();
private:
 void *m_ptr0C;
 int m_10,m_14,m_18,m_1C,m_20;
 PlaybackFlags flags24;char pad25[3];
 int m_28,m_2C,m_30;
 TreeHintRef00217D4C m_ref;
 int m_38;
};
Rva00524BB4::Rva00524BB4(TreeHintRef00217D4C ref) {
 flags24.low=0;m_28=-1;
 m_ptr0C=0;m_20=0;m_2C=0;m_30=0;
 m_ref.m_ptr=ref.m_ptr;
 if(m_ref.m_ptr) ++m_ref.m_ptr->references;
 m_38=0;m_10=0;m_14=0;m_18=0;m_1C=0;
}
