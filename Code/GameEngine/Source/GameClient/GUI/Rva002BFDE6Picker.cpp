// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
// Native2BFDE6..2BFF5A372B RET8. The wrapper2C00E0/5CBB0A preserves this
// and passes a coordinate pair and virtual predicate. Target mapAC and
// element10, predicate slot4, display width slot16, projection slot15 are
// target facts. Original receiver and field names remain unknown.
// The node shape agrees with the adjacent rowed 2BFDAE map walker and
// ZH WindowVideoManager's hash-map iteration (BF1 reference cee35b7d8).
// The native picker differs from that donor: projected coordinates,
// predicate slot4 and 3FAAA1 filter establish the nearest-item behavior.
// The pin for first(cursor*) witnesses the same hidden-result ABI as
// the rowed 427195 hashtable begin; cursor.next is owned at411084.
// 3FA835 returns the shared12B coordinate value; the wrapper's void
// return declaration merely discards this method's native EAX result.
#include "Lib/Coord2D.h"
#include "Lib/ICoord2D.h"
#include "Common/BfmeAudioEventPrefix136.h"
class Display;extern Display *TheDisplay;
class PickerDisplayView {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual unsigned width();
};
class Rva000411084
{
public:
	void *next();
	void *current; // +0x00
	void *owner; // +0x04
};
class AsciiString;
class Rva000427195
{
public:
	void *first(Rva000411084 *);
	int bucketIndex(const AsciiString *name);
	void rva00212858(unsigned int n);
};
class LocomotorTemplate;
template<class T> class OVERRIDE {public:OVERRIDE():head(0) {} const T *head;const T *operator->()const;};
struct Rva00539926Base {unsigned references;Rva00539926Base():references(0) {} virtual ~Rva00539926Base();};

class Rva003FA835 : public Rva00539926Base
{
public:
 Rva003FA835(int kind,void *target,unsigned word);
 virtual ~Rva003FA835() {}
 BfmeEventPositionView rva003FA835();
 void rva003FA878();
 void rva003FA781(int enabled);void rva003FA7D3(int enabled);void rva003FA705(void*,float);
private:
 OVERRIDE<LocomotorTemplate> m_template;
 unsigned m_unknown0C;void *m_target;bool m_enabled;char m_pad15[3];
 float m_elapsed,m_unknown1C,m_20;
};
class Rva003FAAA1 {public:bool rva003FAAA1(void *);};
class PickerDetails {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual bool slot13();
};
struct PickerEntry {char pad0[0x10];PickerDetails *details;};
struct PickerNode {void *next;void *key;PickerEntry *entry;};
class PickerPredicate {public:virtual void slot0();virtual bool slot1(PickerEntry*);};
class Rva005CBB0A {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual bool slot15(const BfmeEventPositionView&,ICoord2D*);
 void *rva002BFDE6(void *point,void *predicate);
private:char pad4[0xa8];char mapAC[0x14];
};
void *Rva005CBB0A::rva002BFDE6(void *point,void *predicate) {
 float scale=1.0f;
 if(TheDisplay) scale=((PickerDisplayView*)TheDisplay)->width() * (1.0f/1024.0f);
 float threshold=scale*70.0f;
 PickerEntry *best=0;
 Rva000411084 cursor;
 ((Rva000427195*)mapAC)->first(&cursor);
 while(cursor.current) {
  PickerEntry *entry=((PickerNode*)cursor.current)->entry;
  PickerDetails *details=entry->details;
  if((!details || details->slot13()) && ((PickerPredicate*)predicate)->slot1(entry) && ((Rva003FAAA1*)entry)->rva003FAAA1(point)) {
   ICoord2D projected;
   if(slot15(((Rva003FA835*)entry)->rva003FA835(),&projected)) {
    ICoord2D *mouse=(ICoord2D*)point;
    Coord2D delta;delta.x=(float)(mouse->x-projected.x);delta.y=(float)(mouse->y-projected.y);
    if(delta.length()<threshold) {
     if(!best)best=entry;
     else {
      ICoord2D bestProjected;
      if(slot15(((Rva003FA835*)best)->rva003FA835(),&bestProjected)) {
       Coord2D bestDelta;bestDelta.x=(float)(mouse->x-bestProjected.x);bestDelta.y=(float)(mouse->y-bestProjected.y);
       if(delta.length()<bestDelta.length())best=entry;
      }
     }
    }
   }
  }
  cursor.next();
 }
 return best;
}
