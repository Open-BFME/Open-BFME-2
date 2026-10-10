// Retail 004EED02..004EEE38 (310B): complete destructor of the 252-byte
// snapshot embedded at LivingWorldPlayer+2C8. Existing scalar deleting
// destructor 004EF28F and primary vtable C62AC4 establish this pin's identity.
// No original class name is asserted. The nine polymorphic base lifetimes
// follow the primary/secondary stores and the native unwind map (states 0..8).
// Secondary callbacks retain the RET4/8/12 ABI of their retail base slots;
// nonempty overrides are declarations only. Derived tables at C62ABC/AC/A0/98/
// 88/78/70/60 and base tables C62A20/C77F44/C62A14/C62A20/BFDF68/BFDF8C/
// BED658/BC6F34 independently establish the interface offsets and widths.
// Members: range-destructed vector28, storage arrays34/40/4C/58, four 12-byte
// trees9C/B4/C0/CC. Their destructors and detach004EE78A are existing owners.
// /EHs preserves the four inline array-free EH-state transitions; /EHsc drops
// them. Target xfer004EF039 proves the container uses and overall FC layout.
// This is target-based structural recovery; the ZH ScoreKeeper is a different
// class and supplies no target observer/layout facts.
// cl: /O1 /MD /EHs /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfmealloc
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <stdlib.h>
class ScoreObserver0 {public: ~ScoreObserver0(){} virtual void event0_0(int,int){} virtual void event0_1(int,int){} };
class ScoreObserver1 {public: ~ScoreObserver1(){} virtual void event1_0(int){} virtual void event1_1(int){} virtual void event1_2(int){} virtual void event1_3(int,int){} };
class ScoreObserver2 {public: ~ScoreObserver2(){} virtual void event2_0(int,int,int){} virtual void event2_1(int,int,int){} virtual void event2_2(int,int,int){} };
class ScoreObserver3 {public: ~ScoreObserver3(){} virtual void event3_0(int,int){} virtual void event3_1(int,int){} };
class ScoreObserver4 {public: ~ScoreObserver4(){} virtual void event4_0(int,int,int){} virtual void event4_1(int,int,int){} virtual void event4_2(int,int){} virtual void event4_3(int,int){} };
class ScoreObserver5 {public: ~ScoreObserver5(){} virtual void event5_0(int){} virtual void event5_1(int,int,int){} virtual void event5_2(int,int,int){} virtual void event5_3(int){} };
class ScoreObserver6 {public: ~ScoreObserver6(){} virtual void event6_0(int){} virtual void event6_1(int){} };
class ScoreObserver7 {public: ~ScoreObserver7(){} virtual void event7_0(int){} virtual void event7_1(int,int){} virtual void event7_2(int,int){} virtual void event7_3(int,int){} };
class Rva004EE501 {public:~Rva004EE501();void*p[3];};
class Rva004EE5D2 {public:void rva004EE78A();};
namespace _STL {
template<class A,class B>struct pair;template<class T>struct less;template<class T>class allocator;template<class T>struct _Select1st;
template<class K,class V,class S,class C,class A>class _Rb_tree {public:~_Rb_tree();void*p;int count;int compare;};
}
// Scalar-key/scalar-value tree teardown uses the existing canonical emitted
// unsigned/void-pointer owner. This storage view asserts no semantic key type:
// target xfer identifies ThingTemplate count maps; the old same-byte donor pin
// for that template spelling is refuted by the code-identity sweep.
typedef _STL::pair<const unsigned,void*> ScorePair;
typedef _STL::_Rb_tree<unsigned,ScorePair,_STL::_Select1st<ScorePair>,_STL::less<unsigned>,_STL::allocator<ScorePair> > ScoreTree;
struct ScoreArray {void*p[3];~ScoreArray(){if(p[0])free(p[0]);}};
class Rva004EED02: public Snapshot,public ScoreObserver0,public ScoreObserver1,public ScoreObserver2,public ScoreObserver3,public ScoreObserver4,public ScoreObserver5,public ScoreObserver6,public ScoreObserver7 {public:virtual ~Rva004EED02();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
virtual void event0_1(int,int);
virtual void event1_0(int);virtual void event1_3(int,int);
virtual void event2_2(int,int,int);
virtual void event3_0(int,int);virtual void event3_1(int,int);
virtual void event4_0(int,int,int);
virtual void event5_0(int);
virtual void event6_1(int);
virtual void event7_3(int,int);
void*owner24;Rva004EE501 member28;ScoreArray list34,list40,list4C,list58;
char pad64[0x9C-0x64];ScoreTree map9C;char padA8[12];ScoreTree mapB4,mapC0,mapCC;char padD8[0xFC-0xD8];};
typedef char ScoreSize[sizeof(Rva004EED02)==0xFC?1:-1];
Rva004EED02::~Rva004EED02(){((Rva004EE5D2*)this)->rva004EE78A();}
