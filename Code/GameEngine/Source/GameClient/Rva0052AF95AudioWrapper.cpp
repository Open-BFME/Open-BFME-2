// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// Native52AF95/110,52B10F/112,52B17F/112: source guide is the matched
// 3FDDAC family. Each independent range ends at its RET and has one EH state.
// Target establishes receiver14 refs10/14/18 owner38 ID18 and rowed tag5
// ctor2DA651 / destructor2D9A43 then Audio slot64. Original owner unknown.
#include "Common/BfmeAudioEventPrefix136.h"

// Target tag5 ctor2DA651 and dtor2D9A43 establish the0x88-byte event lifetime.
// Receiver+14 owns reference slots10/14/18; +38 points to ID at18.
// Original class and helper names remain uncertain. Same-valued PHIs retain
// retail CMP[ref+offset] before the late ADD, after the ID push.
// Opaque constructor declaration: storage below follows its verified0x88-byte provider layout.
struct Rva002DA651 { Rva002DA651(const OpaqueRefElement4&,int); };
union EventStorage0052 { int align; unsigned char bytes[0x88]; };
class OwnerAudioEvent0052 {
 EventStorage0052 storage;
public:
 __forceinline OwnerAudioEvent0052(const OpaqueRefElement4 &ref,int id) {
  ((Rva002DA651*)&storage)->Rva002DA651::Rva002DA651(ref,id);
 }
 __forceinline ~OwnerAudioEvent0052() {
  ((BfmeAudioEventPrefix136*)&storage)->BfmeAudioEventPrefix136::~BfmeAudioEventPrefix136();
 }
 __forceinline BfmeAudioEventPrefix136 *get() {return (BfmeAudioEventPrefix136*)&storage;}
};

class AudioManager;
extern AudioManager *TheAudio;

class Rva0052AudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *);
};


struct AudioRefs0052 { char unknown[0x10]; OpaqueRefElement4 r10,r14,r18; };
struct AudioID0052 { char unknown[0x18]; int id; };
class Rva005391A9 { public: void rva005391A9(); };
class Holder0052B003 { public: void rva0052B003(int); };
struct Receiver0052 {
 char unknown00[0x14]; AudioRefs0052 *refs;
 char unknown18[0x20]; AudioID0052 *owner;
};
class Rva0052AF95 : private Receiver0052 { public: void rva0052AF95(); };
class Rva0052B10F : private Receiver0052 { public: void rva0052B10F(); };
class Rva0052B17F : private Receiver0052 { public: void rva0052B17F(); };
void Rva0052AF95::rva0052AF95() {
 if(!(refs?refs:refs)->r10.referent)goto done;
 if(!owner)goto done;
 {
  OwnerAudioEvent0052 event((owner?refs->r10:refs->r10),owner->id);
  ((Rva0052AudioView *)TheAudio)->addAudioEvent(event.get());
 }
 done:((Rva005391A9 *)this)->rva005391A9();
}
void Rva0052B10F::rva0052B10F() {
 if(!(refs?refs:refs)->r14.referent)goto done;
 if(!owner)goto done;
 {
  OwnerAudioEvent0052 event((owner?refs->r14:refs->r14),owner->id);
  ((Rva0052AudioView *)TheAudio)->addAudioEvent(event.get());
 }
 done:((Holder0052B003 *)this)->rva0052B003(1);
}
void Rva0052B17F::rva0052B17F() {
 if(!(refs?refs:refs)->r18.referent)goto done;
 if(!owner)goto done;
 {
  OwnerAudioEvent0052 event((owner?refs->r18:refs->r18),owner->id);
  ((Rva0052AudioView *)TheAudio)->addAudioEvent(event.get());
 }
 done:((Holder0052B003 *)this)->rva0052B003(0);
}
