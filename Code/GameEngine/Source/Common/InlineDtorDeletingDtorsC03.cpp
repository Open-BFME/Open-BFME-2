// cl: /O1 /DNDEBUG /MD
//
// Scalar deleting destructors of classes whose destructor is empty and
// inline, batch C03: the 29-byte wrapper stores the class's own vtable,
// then frees through operator delete (0x0002FD60) when bit 0 of the flags is
// set and returns this (ret 4). The synthetic tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. No layout beyond the vtable is modelled.
//
//   wrapper     vtable
//   0x000011CF  0x00BBB52C  FXParticleSystem::ModuleTemplate
//   0x00005405  0x00BBB910  Rva00005405 (Xfer's vtable)
//
// Identity: 0x00BBB52C is the vtable FXParticleSystem.cpp's ModuleTemplate
// constructors (0x000011B4, 0x000011C4) and destructor (0x000011BD) install,
// and 0x000011CF sits right after them, before that class's vector deleting
// destructor (0x000011EC); nothing in retail references it. 0x00BBB910 is
// Xfer's vtable (constructor 0x000053DE, destructor 0x000053E7) and
// 0x00005405 follows Xfer.cpp's rows, but ??_GXfer@@UAEPAXI@Z already names
// the out-of-line-destructor copy at 0x0060C8B1, so this second copy keeps an
// address-derived class name.

// <new> declares operator delete[]: the array path of the vector deleting destructor frees
// through it as retail does.
#include <new>

struct C03VtableEmissionTag;

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
	ModuleTemplate(C03VtableEmissionTag *);
	virtual ~ModuleTemplate() {}
};

// ?<FXParticleSystem::ModuleTemplate::ModuleTemplate> absent-from-retail
ModuleTemplate::ModuleTemplate(C03VtableEmissionTag *)
{
}

}

class Rva00005405
{
public:
	Rva00005405(C03VtableEmissionTag *);
	virtual ~Rva00005405() {}
	virtual bool slot04() { return false; }
	virtual bool slot08() { return false; }
	virtual bool slot0C() { return false; }
	virtual bool slot10() { return false; }
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20(int, int) {}
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
};

// ?<Rva00005405::Rva00005405> absent-from-retail
Rva00005405::Rva00005405(C03VtableEmissionTag *)
{
}

// The anchor (no retail counterpart) only makes this TU emit the vector deleting
// destructor of Rva00005405, which retail holds in the table's destructor slot.
// ?<bfmeVectorDeleteAnchor_Rva00005405> absent-from-retail
void bfmeVectorDeleteAnchor_Rva00005405(Rva00005405 *p)
{
	p->Rva00005405::__vecDelDtor(3);
}
