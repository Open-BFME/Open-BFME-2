// cl: /O1 /arch:SSE /G7 /EHsc
//
// ??0Rva0053805DBase@@QAE@XZ, retail 0x005380A8 (139 bytes, EH, RET 4: the
// hidden most-derived flag): the constructor of the listener-broadcasting
// base whose broadcasts 0x0053805D/0x0053806C are already rowed (destructor
// 0x00538133 and its deleting destructor: Rva0053805DBaseDtor.cpp). Its
// derived water-area constructors 0x00308E63, 0x0030C4DE and 0x0030CC3B call
// it. Target evidence: primary table 0x00C691EC, vbtable 0x00C69208 at +0x18
// and the all-__purecall interface 0x00C6EE28 as the shared virtual base at
// +0x30; the root's count (+4) is cleared, the +8 listener list (rowed constructor 0x00330757)
// and the +0x1C observer list (rowed _List_base 0x004EC36C) are built, +0x20
// and +0x24 start at zero, +0x28 at 0.06 and the +0x2C flag false. Names are
// address-derived; the fields' meanings are not established. The 0.06 is
// read from a const global shared with the water-area chunk reader 0x00328E96
// (its stores are scheduled before the load, so it is not a literal); its
// original name is unknown.
// Retail VA 0x00C691E8 stores bits 0x3D75C290, one ULP above 0.06f.
extern const float g_00C691E8 = 0.06000000238418579f;

#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../Include/Common/Rva0030B72CPoint.h"

// Native seven-slot polygon interface, as in Rva00330C50Ctor.cpp.
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

#include "../../Include/Common/Rva00330757Member.h"

struct Rva004FA1FObserver;
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
	~_List_base();
private:
	void *m_node;
};
}

// The reference-counted root (table 0x007C6F20, count at +4) the strategic
// UI classes share; its destructor 0x004E84A4 is pinned. Its constructor
// leaves the table to the derived class (no store in retail), hence novtable.
class __declspec(novtable) Rva0007DF07
{
public:
	__declspec(dllimport) __forceinline Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07();
private:
	unsigned int count;		// +0x04
};

class Rva0053805DBase : public Rva0007DF07, public Rva00330757Member,
	public virtual Rva00330C50Interface
{
public:
	Rva0053805DBase();
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
private:
	_STL::_List_base<Rva004FA1FObserver *, _STL::allocator<Rva004FA1FObserver *> > m_observers;	// +0x1C
	int m_20;
	int m_24;
	float m_28;
	bool m_2C;
};

Rva0053805DBase::Rva0053805DBase()
	: m_observers(_STL::allocator<Rva004FA1FObserver *>()), m_20(0), m_24(0), m_28(g_00C691E8), m_2C(false)
{
}
