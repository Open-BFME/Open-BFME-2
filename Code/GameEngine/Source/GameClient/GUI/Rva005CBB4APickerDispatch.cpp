// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native 5CBB4A..5CBC95 is the complete 331-byte RET12 dispatcher.
// Three slot8 category queries construct the rowed 5CB91E classifier;
// the canonical 5CBB0A picker result supplies a key at +10. The six
// classifier cases select callback slots10..15 and witnessed child+38
// views, followed by the LivingWorldLogic+B0 fallback and slot16/slot9.
// WB LivingWorldThingPicker operator() guides the relationship only;
// original receiver/method and record identities remain address-derived.
// Named lookup-result locals reproduce target callback evaluation order.
// The pointer-result ABI repair is verified in the canonical owner units.
class Rva005CBB0A {public:void *rva005CBB0A(void *,const int*);};
#include "../../../Include/GameLogic/Rva0020EE29.h"
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
struct PickerWorldView {char pad[0xb0];Rva0020EE29 *lookup;};
struct PickerRecordView {char pad[0x38];void *child;};
extern "C" void *Rva003FE245Lookup(int);
unsigned Rva0052B225(unsigned);
unsigned Rva0059E0F7(unsigned);
class Rva005CBB4A;
class Rva005CB91E {public:
 Rva005CBB4A *owner;bool first,second,third;
 int rva005CB91E(int);
};
struct PickerChosenView {char pad[0x10];int key;};
#include "../../../Include/Common/Rva005CBB4A.h"
void Rva005CBB4A::rva005CBB4A(void *map,int point,int mode) {
 bool first=slot8(0);bool second=slot8(1);bool third=slot8(2);
 if(first||second||third) {
  Rva005CB91E classifier;classifier.owner=this;classifier.first=first;classifier.second=second;classifier.third=third;
  PickerChosenView *chosen=(PickerChosenView*)((Rva005CBB0A*)map)->rva005CBB0A((void*)point,(const int*)&classifier);
  if(chosen) {
   int key=chosen->key;
   if(key) {
    switch(classifier.rva005CB91E(key)) {
    case 0:{PickerRecordView *record=(PickerRecordView*)Rva003FE245Lookup(key);slot15(record->child);break;}
    case 1:{void *record=Rva003FE245Lookup(key);slot12(record);break;}
    case 2:{PickerRecordView *record=(PickerRecordView*)Rva0052B225(key);slot14(record->child);break;}
    case 3:{void *record=(void*)Rva0052B225(key);slot11(record);break;}
    case 4:{PickerRecordView *record=(PickerRecordView*)Rva0059E0F7(key);slot13(record->child);break;}
    case 5:{void *record=(void*)Rva0059E0F7(key);slot10(record);break;}
    }
    return;
   }
  }
 }
 if(slot8(3)) {
  void *result=((PickerWorldView*)TheLivingWorldLogic)->lookup->rva0020FAB4(point,mode);
  if(result &&slot7(result)){slot16(result);return;}
 }
 slot9();
}
