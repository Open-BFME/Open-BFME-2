// cl: /MD /EHs-c-
// ?Rva0030596CIntersects@@YA_NPAXUCoord3D@@M@Z @0x0030596C 137B via GhostObjectManager GhostProvider bfmeIntersects
// Retail walks GhostObject list from TheGhostObjectManager slot 0x20 and tests GeometryInfo::bfmeIntersects.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class GeometryInfo
{
public:
	bool bfmeIntersects(const Coord3D &, float, const GeometryInfo &, const Coord3D &, float) const;
};
class GhostObject
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual GhostObject *getNext();
	int m_04;
	int *m_08;
};
class GhostProvider
{
public:
	virtual const GeometryInfo *geometry();
	virtual const Coord3D *position();
	virtual float angle();
};
class GhostObjectManager
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual GhostObject *getFirst();
};
extern GhostObjectManager *TheGhostObjectManager;
bool __cdecl Rva0030596CIntersects(void *self, Coord3D coord, float radius)
{
	GhostObject *ghost = TheGhostObjectManager->getFirst();
	if (ghost != 0)
	{
		GeometryInfo *myGeom = (GeometryInfo *)((char *)self + 0xa0);
		for (; ghost != 0; ghost = ghost->getNext())
		{
			const GeometryInfo *gi = ((GhostProvider *)((char *)ghost + 8 + ghost->m_08[1]))->geometry();
			const Coord3D *pos = ((GhostProvider *)((char *)ghost + 8 + ghost->m_08[1]))->position();
			float ang = ((GhostProvider *)((char *)ghost + 8 + ghost->m_08[1]))->angle();
			if (gi->bfmeIntersects(*pos, ang, *myGeom, coord, radius))
				return true;
		}
	}
	return false;
}
