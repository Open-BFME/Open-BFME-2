// Native002E2AAE..002E2BAF (257B), scalar deleting caller002E2CF4,
// primary Snapshot vtable C04B50: destructor of the 3C8-byte player object.
// LivingWorldPlayer identity follows the WorldBuilder player constructor
// witnesses retained with bank002E2903; this entry retains its existing opaque
// pin spelling. No original member names are claimed.
// Target calls and unwind states establish listener list04, input18, narrow
// strings48/1B4, AI4C (now recovered), record vector1A8, POD storage1B8/1CC,
// Snapshot members258/274, trees29C/2A8 and embedded snapshot2C8 (now recovered).
// Destructor clears owned armies then broadcasts listener slot3 with this,
// through the existing folded vcall thunk005CB265. Reverse member teardown
// restores all three Snapshot base vtables; /EHs retains POD free transitions.
// No same-layout donor exists: ZH Player and its ScoreKeeper are different
// classes, and BFME1 lifted player bodies do not prove these target lifetimes.
// cl: /O1 /MD /EHs /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "ascii_string.h"
#include <stdlib.h>
class Rva002E1E51Listener {public:virtual void slot0(void*);virtual void slot1(void*);virtual void slot2(void*);virtual void notify(void*);};
class Rva002E1E51List {public:void forEach(void(Rva002E1E51Listener::*)(void*),void*);void*p[4];~Rva002E1E51List(){if(p[0])free(p[0]);}};
class Rva002E21D1 {public:void rva002E21D1();};
class Rva002E0F1E {public:virtual ~Rva002E0F1E();char bytes[36];};
class LivingWorldAI {public:~LivingWorldAI();char bytes[308];};
struct PlayerPodArray {void*p[3];~PlayerPodArray(){if(p[0])free(p[0]);}};
class Rva002E15E6 {public:~Rva002E15E6();void*p[3];};
class Rva004EED02 {public:virtual ~Rva004EED02();char bytes[248];};
class PlayerSnapshotMember:public Snapshot {public:~PlayerSnapshotMember(){}virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);char bytes[24];};
namespace _STL {template<class T>class allocator;template<class T,class A>class vector{public:~vector();void*p[3];};}
struct Rva002E2690Element;
class Rva002E2AAE:public Snapshot,public Rva002E1E51List {public:
 virtual ~Rva002E2AAE();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 int id14;Rva002E0F1E input18;void*context40;int kind44;AsciiString name48;LivingWorldAI ai4C;
 char pad180[0x1A8-0x180];_STL::vector<Rva002E2690Element,_STL::allocator<Rva002E2690Element> > records1A8;AsciiString name1B4;
 PlayerPodArray armies1B8;int unknown1C4;float unknown1C8;PlayerPodArray list1CC;char storage1D8[128];
 PlayerSnapshotMember snapshot258,snapshot274;int unknown290,unknown294,unknown298;Rva002E15E6 tree29C,tree2A8;
 char pad2B4[20];Rva004EED02 score2C8;bool flag3C4,flag3C5;
};
typedef char PlayerSize[sizeof(Rva002E2AAE)==0x3C8?1:-1];
Rva002E2AAE::~Rva002E2AAE(){((Rva002E21D1*)this)->rva002E21D1();forEach(&Rva002E1E51Listener::notify,this);}
