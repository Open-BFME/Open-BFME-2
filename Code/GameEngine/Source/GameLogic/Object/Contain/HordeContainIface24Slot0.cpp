// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva0046950D@Rva0046950D24@@QAEXPAVObject@@HH@Z at 0x0046950D (205B).
// Native 0x0046950D..0x004695DA, RET 12. HordeContain's +0x24 interface (shared
// vtable 0x00C45AA4, installed by the HordeContain and HorseHordeContain ctors)
// has this body in slot 0; ECX is the +0x24 subobject, so the owning Object at
// primary +0x08 is [ecx-0x1C], the target-ID member at primary +0x2F0 is
// [ecx+0x2CC] and the +0x11C interface passed to slot 143 is ecx+0xF8. Only the
// first argument is read; the other argument types and the method's original
// name are unresolved. It returns early unless the target is a template with bit 1
// at +0x121, not status bit 0 and not the remembered target, then compares the
// 2D facing of the owner and the target: when the absolute dot product is at
// least 0.5 it calls +0x11C interface slot 143 with the target's ID.
// Codegen: the target's direction is read three times through volatile references
// (retail re-reads the Coord3D the getter filled); the Coord3D is the canonical
// header, copied member by member.
#include <math.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

template<class T> inline volatile T &__vref(T &x) { return *(volatile T *)&x; }

#include "../../../Common/Thing/thing.h"

class Object;

template <int N> class Rva00469626Slots : public Rva00469626Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00469626Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva0046950DHordeIface : public Rva00469626Slots<143>
{
public:
	virtual void rva00468BDC(int value) = 0;
};

struct Rva0046950DTemplate
{
	unsigned char m_pad000[0x121];
	unsigned char m_121;
};

struct Rva00468C37Template
{
	unsigned char m_pad000[0x150];
	unsigned char m_150;
};

struct Rva00468C37Holder
{
	unsigned char m_pad000[4];
	const Rva00468C37Template *m_4;
};

class AIUpdateInterface
{
public:
	unsigned char m_pad000[0x1F0];
	Rva00468C37Holder *m_1F0;
};

class Object : public Thing
{
public:
	unsigned char m_pad060[0x74 - 0x60];
	unsigned int m_id; // +0x74
	unsigned char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned int m_status; // +0x438
};

class Rva0046950D24
{
public:
	void rva0046950D(Object *obj, int, int);

private:
	// ECX is the +0x24 interface subobject: the primary Object pointer sits at primary +0x08.
	Object *owner() const { return *(Object **)((char *)this - 0x1C); }
};

void Rva0046950D24::rva0046950D(Object *obj, int, int)
{
	unsigned int targetId = *(unsigned int *)((char *)this + 0x2CC);
	if (!obj || !(((const Rva0046950DTemplate *)obj->m_template)->m_121 & 2) || (obj->m_status & 1)
		|| obj->m_id == targetId)
		return;
	AIUpdateInterface *ai = owner()->m_ai;
	if (!ai || !ai->m_1F0 || !ai->m_1F0->m_4->m_150)
		return;
	Coord3D ownerDirection;
	{ const Coord3D *p = owner()->getUnitDirectionVector2D(); ownerDirection.x = p->x; ownerDirection.y = p->y; ownerDirection.z = p->z; }
	Coord3D direction;
	{ const Coord3D *p = obj->getUnitDirectionVector2D(); direction.x = p->x; direction.y = p->y; direction.z = p->z; }
	if (fabs(__vref(direction.x) * ownerDirection.x + __vref(direction.y) * ownerDirection.y
		+ __vref(direction.z) * ownerDirection.z) < 0.5f)
		return;
	((Rva0046950DHordeIface *)((char *)this + 0xF8))->rva00468BDC(obj->m_id);
}
