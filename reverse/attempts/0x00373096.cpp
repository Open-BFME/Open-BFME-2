// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /GX
// stlport
//
// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00373096, 96 bytes. Behavior-side ctor (rowed instance factory
// 0x24B625 news 0x3C with this pinned 2-arg ctor as its sole raw caller
// at 0x24B64C).
//
// Shape: UpdateModule-base call (rowed 0x253390), two-phase +0x20/+0x24
// slots via sourced-before address-take plus body overwrites, a body-
// placed std::vector<BfmeE16> member at +0x28 (rowed _Vector_base
// 0x211E58; the empty-allocator temporary surfaces as the lea [ebp+0xF]
// push), the three derived vtable installs, and an and-zero plus
// false/true tail bytes. The bases are declared without virtuals or dtors.
// Row supersedes the ctor pin.

#include <new>
#include <vector>

class Thing;
class ModuleData;
class Object;

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class MineshaftPortalBehaviour : public UpdateModule
{
public:
	MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	const void *m_24;
	_STL::vector<BfmeE16> m_28;
	int m_34;
	bool m_38;
	bool m_39;
};

// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z @0x00373096
MineshaftPortalBehaviour::MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_20((const void *)0x00C1C780),
	  m_24((const void *)0x00C4EF80),
	  m_28()
{
	int *slot20 = (int *)&m_20;
	int *slot24 = (int *)&m_24;
	m_vtable = (const void *)0x00C17DD0;
	m_secondary0C = (const void *)0x00C42B60;
	m_secondary10 = (const void *)0x00C17DC4;
	*slot20 = (int)0x00C17DC0;
	*slot24 = (int)0x00C17DB0;
	m_34 &= 0;
	m_38 = false;
	m_39 = true;
}
