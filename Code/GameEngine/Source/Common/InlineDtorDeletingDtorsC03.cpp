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
