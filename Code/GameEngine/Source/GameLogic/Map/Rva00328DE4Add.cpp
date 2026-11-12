// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /I.
// Rva00328DE4Add, retail 0x00328DE4..0x00328E96 (178 bytes, EH, cdecl): the
// parsed-polygon append the OldPolygonTrigger.cpp water-area and trigger
// chunk parsers call (WB parseWaterAreasChunkImpl 0x00BE2810 -> 0x003295B4).
// Target evidence: new 0x64 + the rowed PolygonTrigger(int,int) 0x002E3FAB on
// the holder's id and point count (+0x48/+0x4C vector, 8-byte points), the
// boundary set through the vcall thunk 0x005CB279, name/layer copies through
// the rowed StringBase<char>::set 0x000366F0 (AsciiString operator=), the
// link store of the MI next pointer (+0x3C, null-checked) and an owner whose
// release 0x002E3E2A and dtor 0x000AD6F4 are rowed.
#include "Code/Libraries/Include/Lib/Coord2D.h"
#include "ascii_string.h"
struct Out
{
	Out();
	~Out();
	char m_pad00[0x0c];
	bool m_isRiver;
	char m_pad0d[0x48 - 0x0d];
	Coord2D *m_pointsBegin;
	Coord2D *m_pointsEnd;
	char m_pad50[0x74 - 0x50];
	unsigned int pointCount() const { return m_pointsEnd - m_pointsBegin; }
};

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

#include "ascii_string.h"
class PolygonTrigger;
class PolygonNext { public: PolygonNext():next(0){} PolygonTrigger *next; };
class PolygonSecondary {
public:
 PolygonSecondary(){}
 virtual PolygonTrigger* secondarySlot()=0;
};
class PolygonTrigger : public PolygonNext, public Rva00330C50, public PolygonSecondary {
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
#include "../../../Include/GameLogic/Rva002E3E2AObject.h"
class Rva002E3E2AOut {
public:
 explicit Rva002E3E2AOut(Rva002E3E2AObject *p):pointer(p){}
 Rva002E3E2AOut(Rva002E3E2AOut &other):pointer(other.pointer){other.pointer=0;}
 ~Rva002E3E2AOut(){delete pointer;}
 void detach(){pointer=0;}
 Rva002E3E2AObject *pointer;
};
#include "../../../Include/Common/Rva000AD6F4.h"

// Visible copies of the two rowed callees that receive the owner's address
// (PolygonTrigger.cpp 0x002E3E2A, Disp8DivAvgDwordGetters.cpp 0x000AD6F4):
// with their bodies in view cl packs the owner into the dead record argument
// slot and the returned temporary into the dead link argument slot.
class Rva000AD6F4Base { public: virtual void *virt0(int flags); };
__declspec(noinline) inline Rva002E3E2AOut Rva000AD6F4::rva002E3E2A()
{
	Rva002E3E2AOut temporary(reinterpret_cast<Rva002E3E2AObject *>(m_ptr));
	m_ptr = 0;
	return temporary;
}
__declspec(noinline) inline Rva000AD6F4::~Rva000AD6F4()
{
	Rva000AD6F4Base *p = reinterpret_cast<Rva000AD6F4Base *>(m_ptr);
	m_ptr = 0;
	void *q;
	if (p)
		q = p->virt0(0);
	else
		q = 0;
	::operator delete(q);
}
class BoundaryView { public: virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void setBoundary(const void*); };
// WB 0x00BE1500 is the unnamed non-water trigger importer called by the
// polygon parser. Retail independently proves allocation size 0x64, next +3C,
// strings +40/+4C, and transfer into the caller's current list link.
void __cdecl Rva00328DE4Add(void *record, void **linkPtr)
{
	Out *data = static_cast<Out *>(record);
	Rva000AD6F4 trigger(new PolygonTrigger(*static_cast<int *>(record),
		data->m_pointsEnd - data->m_pointsBegin));
	PolygonTrigger *const object=static_cast<PolygonTrigger *>(trigger.m_ptr);
	void (BoundaryView::*setBoundary)(const void *) = &BoundaryView::setBoundary;
	(reinterpret_cast<BoundaryView*>(object)->*setBoundary)(&data->m_pointsBegin);
	object->name = *reinterpret_cast<AsciiString *>(static_cast<char *>(record) + 4);
	object->layer = *reinterpret_cast<AsciiString *>(static_cast<char *>(record) + 8);
	*static_cast<PolygonTrigger **>(*linkPtr) = object;
	*linkPtr = object ? &object->next : 0;
	trigger.rva002E3E2A().detach();
}
