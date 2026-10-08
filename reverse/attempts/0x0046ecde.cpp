// ?rva0046ECDE@HordeContain@@UAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z
// partial score=0.95 date=2026-10-08
// Banked near miss for
// ?rva0046ECDE@HordeContain@@UAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z
// @0x0046ECDE (273 B), HordeContain +0x11C iface slot 111, in
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp.
// Declarations it needs (add to that unit):
#if 0
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
// AIUpdateInterface: destroys the path and builds a new one (needs a
// symbols.csv pin for 0x0026594F; no row there yet):
void rva0026594F(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer, const Coord3D *dest, const Coord3D *pos);
struct Rva0046E6EAObject; struct Rva0046E6EACoord;
class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject *obj, const Rva0046E6EACoord *pos, Rva0046E6EACoord *out, bool flag); };
// iface slot 111 (was gap111):
virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer) = 0;
#endif
// Exact except one thing: retail calls slot 7 into a temp at [ebp-0x40] and
// movsd-copies it into pos at [ebp-0x34] (frame 0x40). This body RVOs slot 7
// straight into pos (frame 0x34), otherwise byte-identical. Every form that
// produces the temp (pos = slot7(), const Coord3D &r = slot7(); pos = r,
// tmp then pos = tmp / *&tmp, block-scoped tmp, function-scope pos or angle)
// also caches self in eax across the copy and swaps self/angle slots
// (-8/-0xc). A member-wise inline set(&tmp) keeps the slots but copies via
// movss. Inline by-value wrappers around slot 7 RVO through.
void HordeContain::rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer)
{
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_ai;
			float angle = 0.0f;
			Coord3D pos = slot7(obj, &angle);
			Coord3D dest = *self->getPosition();
			if (layer != LAYER_GROUND)
			{
				dest.add(a2);
				dest.scale(0.5f);
			}
			((Rva0046E6EA *)(UpdateModule *)this)->rva0046E6EA((Rva0046E6EAObject *)obj, (const Rva0046E6EACoord *)&pos, (Rva0046E6EACoord *)self, false);
			ai->rva0026594F(a1, a2, a3, layer, &dest, &pos);
		}
	}
}
