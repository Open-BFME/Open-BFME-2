// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 330C50..330CC2: primary vptr +0, vbptr +4, container +8,
// flag +34, vtordisp +38, seven-slot virtual interface +3C.
// The vbtable contains {-4, 0x38}; interface thunks 2E3E80..2E3EB0
// each subtract the vtordisp before dispatching the corresponding member.
#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../Include/Common/AreaPolygonBase.h"
// The virtual-base interface has seven slots. Defining their actual
// overrides makes MSVC derive the native negative offsets from this class
// layout; separate opaque receiver classes previously hid that relationship.
// Slot1 returns the same eight-byte point type as slot6 through a hidden
// result buffer. Its real copy constructor reproduces both observed stores.
struct Rva0030B72CPoint {
 Rva0030B72CPoint() {}
 __forceinline Rva0030B72CPoint(const Rva0030B72CPoint &p):x(p.x),y(p.y) {}
 float x,y;
};
class PolygonTrigger {
public: Region2D rva0007E03A(); Rva0030B72CPoint getCenterPoint2D() const;
};
class Rva0030B719Shape {public:float rva0030B706()const;float getRadius()const;};

class Rva00330C50Interface
{
public:
	~Rva00330C50Interface() {}
	virtual int slot0() const = 0;
	virtual Rva0030B72CPoint slot1(int index) const = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

class Rva0030B9DD
{
public:
	Rva0030B9DD(int);
	~Rva0030B9DD() { if (begin) _STL::free(begin); }
private:
	public:
 Rva0030B72CPoint *begin,*end,*capacity;
 char unknown0C[0x28-0x0C];
 int index;
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	Rva00330C50();
	void rva00330AA6(int);
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
private:
	Rva0030B9DD container;
	bool changed;
};

Rva00330C50::Rva00330C50() : container(0)
{
	changed = true;
}

// Native 2E3E51..2E3E80 uses the constructor's primary/virtual tables and
// frees container.begin at +8. Real virtual inheritance supplies its vptr
// and vtordisp stores. The compiler's scalar deleting destructor at
// 2E422C..2E424F then restores the interface at +3C and conditionally deletes
// this object. The original semantic class name remains unproven.
Rva00330C50::~Rva00330C50() {}

// Native330AA6 is an8-byte terminal jump to rowed AreaPolygonBase::reserve
// at30B96B with the measured container adjustment8. The following16 bytes
// form a separate float virtual dispatch, not part of this reserve wrapper.
void Rva00330C50::rva00330AA6(int count)
{
 reinterpret_cast<AreaPolygonBase*>(&container)->reserve(count);
}

int Rva00330C50::slot0()const {return container.end-container.begin;}
Rva0030B72CPoint Rva00330C50::slot1(int index)const {return container.begin[index];}
int Rva00330C50::slot2()const {return container.index;}
Region2D Rva00330C50::slot3() {return reinterpret_cast<PolygonTrigger*>(this)->rva0007E03A();}
float Rva00330C50::slot4()const {return reinterpret_cast<const Rva0030B719Shape*>(&container)->rva0030B706();}
float Rva00330C50::slot5()const {return reinterpret_cast<const Rva0030B719Shape*>(&container)->getRadius();}
Rva0030B72CPoint Rva00330C50::slot6()const {return reinterpret_cast<const PolygonTrigger*>(this)->getCenterPoint2D();}
