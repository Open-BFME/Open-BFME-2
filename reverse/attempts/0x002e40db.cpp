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
	~Rva00330C50Interface() {}
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
};

class Rva0030B9DD
{
public:
	Rva0030B9DD(int);
	~Rva0030B9DD();
private:
	char unknown00[0x2C];
};

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
};

Rva00330C50::Rva00330C50() : container(0)
{
	changed = true;
}

class AreaPolygonBase { public: void reserve(int); };
// Native330AA6 is an8-byte terminal jump to rowed AreaPolygonBase::reserve
// at30B96B with the measured container adjustment8. The following16 bytes
// form a separate float virtual dispatch, not part of this reserve wrapper.
__declspec(noinline) void Rva00330C50::rva00330AA6(int count)
{
 reinterpret_cast<AreaPolygonBase*>(&container)->reserve(count);
}

#include "ascii_string.h"
class PolygonTrigger;
class PolygonSecondary {
public:
 PolygonSecondary():next(0){}

 virtual PolygonTrigger* secondarySlot()=0;
 PolygonTrigger* next;
};
class PolygonTrigger : public Rva00330C50, public PolygonSecondary {
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
};
PolygonTrigger::PolygonTrigger(int identifier,int count):id(identifier)
{ rva002E36B7(count); }
__declspec(noinline) void PolygonTrigger::rva002E36B7(int count)
{
 rva00330AA6(count);
 flag48=false;flag50=false;field54=0;field58=0;
}



struct DataChunkInfo;
class DataChunkInput {
public: int readInt(); AsciiString readAsciiString();
};
struct PolygonPointView {float x,y;};
class ElevatedAreaPolygon {
public:
 void parse(DataChunkInput&,int);
 PolygonPointView *first,*last;
};
class Rva002E3E2AObject { public: virtual ~Rva002E3E2AObject(); };
class Rva002E3E2AOut {
public:
 explicit Rva002E3E2AOut(Rva002E3E2AObject*p):pointer(p){}
 Rva002E3E2AOut(Rva002E3E2AOut&other):pointer(other.pointer){other.pointer=0;}
 ~Rva002E3E2AOut(){delete pointer;}
 Rva002E3E2AObject* release(){Rva002E3E2AObject*p=pointer;pointer=0;return p;}
 Rva002E3E2AObject *pointer;
};
class Rva000AD6F4 {
public:
 explicit Rva000AD6F4(Rva002E3E2AObject*p):pointer(p){}
 ~Rva000AD6F4(){clear();}
 void clear();
 Rva002E3E2AOut rva002E3E2A();
 Rva002E3E2AObject *pointer;
};
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
};

__declspec(noinline) void Rva002E37CB::rva002E37CB(void *value)
{
	*(void **)m_current = value;
	m_current = value ? (char *)value + 0x3C : 0;
}

class PolygonTriggerDataChunkParserBase {
public: bool parse(DataChunkInput&,const DataChunkInfo*);
};
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
  if(polygon.last-polygon.first>=2)
  {
   reinterpret_cast<Rva002E37CB*>(this)->rva002E37CB(owner.rva002E3E2A().release());
  }
 }
 return true;
}




