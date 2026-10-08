// ?rva004690D0@HordeContain@@UAEXH@Z
// partial score=0.85 date=2026-10-08
// Banked near miss for ?rva004690D0@HordeContain@@UAEXH@Z @0x004690D0 (51 B),
// HordeContain +0x11C iface slot 141, in
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp.
// Declarations it needs (already in that unit):
#if 0
struct Rva002A8AB1Record { void rva002C6AA8(int value, Object *obj); };	// SkirmishAI::onHordeCreated
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *owner); };
extern Rva002A8F24 *g_00DFEEF8;
// HordeContain: virtual void rva004690D0(int value);
#endif
// Only diff: cl CSEs &m_object as `lea esi,[ecx-0x114]` and loads [esi];
// retail keeps `mov esi,ecx` and loads [esi-0x114] twice. Tried a local
// Player*, getObject() accessor, a const Object* local, a casted access and a
// braced if: all CSE the address.
void HordeContain::rva004690D0(int value)
{
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_object->getControllingPlayer());
	if (rec)
		rec->rva002C6AA8(value, m_object);
}
