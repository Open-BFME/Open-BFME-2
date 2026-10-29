// ?parse@PolygonTriggerDataChunkParserBase@@QAE_NAAVDataChunkInput@@PBUDataChunkInfo@@@Z
// partial score=0.999 date=2026-10-14
// U1 r6: EXACT in the Lab2 scorer (nd 0, 273 B, unresolved ctor 0x2E3FAB bound by address). Levers: (1) visible noinline bodies of the rowed
// Rva000AD6F4::rva002E3E2A and ::clear (their address escape kept the owner out of the dead param slot [ebp+8]); (2) `if(n<2) continue;` early-continue
// instead of the wrapping if (retail's skip path jumps into the middle of the shared owner-dtor tail). Landing needs the ctor 0x2E3FAB (claimed by w7-mp3).
// ?parse@PolygonTriggerDataChunkParserBase@@QAE_NAAVDataChunkInput@@PBUDataChunkInfo@@@Z
// partial score=0.93 date=2026-10-12
// ?parse@PolygonTriggerDataChunkParserBase@@QAE_NAAVDataChunkInput@@PBUDataChunkInfo@@@Z
// partial score=0.92674 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Banked near miss: native2E40DB..2E41EC273B; WBABB3B0 names parser.
// BF1ba7 PolygonTrigger.cpp guides semantic name/layer/id fields only.
// Native ElevatedAreaPolygon parse and owned transfer prove target structure.
// 253/273 patched bytes match including unresolved constructor call bytes.
// Remaining: constructor2E3FAB unresolved; allocation temp frame24 vs20;
// owner-address LEA is scheduled after the point-count check. Do not admit.
// Native 330C50..330CC2: primary vptr +0, vbptr +4, container +8,
// flag +34, vtordisp +38, seven-slot virtual interface +3C.
// The vbtable contains {-4, 0x38}; interface thunks 2E3E80..2E3EB0
// each subtract the vtordisp before dispatching the corresponding member.
class Rva00330C50Interface

{
 public:
 ~Rva00330C50Interface() 
 {
  
 }
 virtual void slot0() = 0;
 virtual void slot1() = 0;
 virtual void slot2() = 0;
 virtual void slot3() = 0;
 virtual void slot4() = 0;
 virtual void slot5() = 0;
 virtual void slot6() = 0;
 
}
;
class Rva0030B9DD

{
 public:
 Rva0030B9DD(int);
 ~Rva0030B9DD();
 private:
 char unknown00[0x2C];
 
}
;
class Rva00330C50 : public virtual Rva00330C50Interface

{
 public:
 Rva00330C50();
 void rva00330AA6(int);
 virtual ~Rva00330C50();
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 private:
 Rva0030B9DD container;
 bool changed;
 
}
;
// Rva00330C50::Rva00330C50 is rowed in its home unit; this copy was a duplicate definition.
// Rva00330C50::rva00330AA6 (0x00330AA6) is rowed in Rva00330C50Ctor.cpp; this unit
// only calls it.
#include "ascii_string.h"
class PolygonTrigger;
class PolygonSecondary 
{
 public:
 PolygonSecondary():next(0)
 {
  
 }
 virtual PolygonTrigger* secondarySlot()=0;
 PolygonTrigger* next;
 
}
;
class PolygonTrigger : public Rva00330C50, public PolygonSecondary 
{
 public:
 PolygonTrigger(int,int);
 virtual ~PolygonTrigger();
 virtual PolygonTrigger* secondarySlot();
 void rva002E36B7(int);
 AsciiString name;
 int id;
 bool flag48;
 AsciiString layer;
 bool flag50;
 int field54,field58;
 
}
;
// PolygonTrigger::PolygonTrigger is rowed in PolygonTriggerCtor.cpp (0x002E3FAB);
// this unit's copy was not retail's and the link kept it.
__declspec(noinline) inline void PolygonTrigger::rva002E36B7(int count)

{
 rva00330AA6(count);
 flag48=false;
 flag50=false;
 field54=0;
 field58=0;
 
}
struct DataChunkInfo;
class DataChunkInput 
{
 public: int readInt();
 AsciiString readAsciiString();
 
}
;
struct PolygonPointView 
{
 float x,y;
 
}
;
class ElevatedAreaPolygon 
{
 public:
 void parse(DataChunkInput&,int);
 PolygonPointView *first,*last;
 
}
;
class Rva002E3E2AObject 
{
 public: virtual ~Rva002E3E2AObject();
 
}
;
class Rva002E3E2AOut 
{
 public:
 explicit Rva002E3E2AOut(Rva002E3E2AObject*p):pointer(p)
 {
  
 }
 Rva002E3E2AOut(Rva002E3E2AOut&other):pointer(other.pointer)
 {
  other.pointer=0;
  
 }
 ~Rva002E3E2AOut()
 {
  delete pointer;
  
 }
 Rva002E3E2AObject* release()
 {
  Rva002E3E2AObject*releasedObject=pointer;
  pointer=0;
  return releasedObject;
  
 }
 Rva002E3E2AObject *pointer;
 
}
;
class Rva000AD6F4 
{
 public:
 explicit Rva000AD6F4(Rva002E3E2AObject*ownedObject):pointer(ownedObject)
 {
  
 }
 // Retail's destructor is the folded 29-byte clear body at 0x000AD6F4
 // (Disp8DivAvgDwordGetters.cpp spells the same copy).
 ~Rva000AD6F4()
 {
  struct Slot0 { virtual void *virt0(unsigned int); };
  Rva002E3E2AObject *m_objectToDelete=pointer;
  pointer=0;
  void *deletedStorage;
  if(m_objectToDelete)
   deletedStorage=((Slot0 *)m_objectToDelete)->virt0(0);
  else
   deletedStorage=0;
  ::operator delete(deletedStorage);
 }
 void clear();
 Rva002E3E2AOut rva002E3E2A();
 Rva002E3E2AObject *pointer;
 
}
;
inline __declspec(noinline) Rva002E3E2AOut Rva000AD6F4::rva002E3E2A()

{
 Rva002E3E2AOut temporary(pointer);
 pointer=0;
 return temporary;
 
}
struct Rva000AD6F4Base 
{
 virtual void *virt0(unsigned int);
 
}
;
inline __declspec(noinline) void Rva000AD6F4::clear()

{
 Rva000AD6F4Base *p = (Rva000AD6F4Base *)pointer;
 pointer = 0;
 void *q;
 if (p) q = p->virt0(0);
 else q = 0;
 ::operator delete(q);
 
}
// cl: /O1 /arch:SSE /G7 /MD
// 0x002E37CB / 26 bytes. The pointer update and +0x3C field displacement
// are direct retail evidence; the class owner remains an address-based name.
class Rva002E37CB

{
 public:
 void rva002E37CB(void *value);
 private:
 unsigned char m_pad00[0x0C];
 void *m_current;
 
}
;
__declspec(noinline) void Rva002E37CB::rva002E37CB(void *value)

{
 *(void **)m_current = value;
 m_current = value ? (char *)value + 0x3C : 0;
 
}
class PolygonTriggerDataChunkParserBase 
{
 public: bool parse(DataChunkInput&,const DataChunkInfo*);
 
}
;
bool PolygonTriggerDataChunkParserBase::parse(DataChunkInput& file,const DataChunkInfo*)

{
 for(int remaining=file.readInt();remaining>0;--remaining)
 
 {
  AsciiString triggerName=file.readAsciiString();
  AsciiString layerName=file.readAsciiString();
  int identifier=file.readInt();
  Rva000AD6F4 owner(reinterpret_cast<Rva002E3E2AObject*>(new PolygonTrigger(identifier,2)));
  PolygonTrigger *trigger=reinterpret_cast<PolygonTrigger*>(owner.pointer);
  trigger->name=triggerName;
  trigger->layer=layerName;
  ElevatedAreaPolygon &polygon=*reinterpret_cast<ElevatedAreaPolygon*>(reinterpret_cast<char*>(trigger)+8);
  polygon.parse(file,1);
  if(polygon.last-polygon.first<2)
  continue;
  reinterpret_cast<Rva002E37CB*>(this)->rva002E37CB(owner.rva002E3E2A().release());
  
 }
 return true;
 
}
