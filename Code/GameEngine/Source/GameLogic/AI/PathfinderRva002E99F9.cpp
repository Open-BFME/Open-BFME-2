// cl: /MD
// Dump lane range 13: ?FindBrokenBridge @0x002E99F9 211B. Two-position cell
// resolution (TerrainLogic layers, then Pathfinder cells) feeding the
// union-find subobject at +0x460 through the pinned 0x0053241F/0x00531FD4
// thunks. Param a2 is overwritten with a ushort result (dead after the
// ret 0xc pop); the function returns 0. Identities unproven.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;
class PathfindCell
{
public:
	char m_pad0[8];
	unsigned short m_8;
};
class Rva005310E3
{
public:
	int rva005310E3();
private:
	char m_lead[4];
	unsigned char m_4;
	unsigned char m_5;
	char m_pad[2];
	int m_8;
};
class Rva00531A44
{
public:
	Rva00531A44 &rva00531A44(unsigned short count);
	void rva00531A93();
	unsigned short rva00531AEE(unsigned short idx);
	unsigned short rva00531B20(unsigned short idx);
	void rva00531ABB(unsigned short idx);
private:
	unsigned short m_count;
	unsigned short m_zero;
	unsigned short *m_p4;
	unsigned char *m_p8;
	unsigned short *m_pC;
	unsigned short *m_p10;
};
int __cdecl rva0053123A(void *item);
class Rva00531720
{
public:
	unsigned char rva00531720(unsigned int count, unsigned int value);
};
// WB12D2AB0 and native531757 establish the predicate owner.
class PathfindZoneManager {
public: bool CouldBeInEquivSet(unsigned equivalent, unsigned zone);
};
class Rva002E99F9Sub460
{
public:
	__declspec(noinline) unsigned short rva0053241F(void *s, unsigned short w);
	unsigned short rva00531FD4(void *s, unsigned short w);
	unsigned short rva00531FE6(bool force, void *item, unsigned short value);
	bool rva005318DB(void *item, void *first, void *second);
	bool rva005317D7(unsigned int index, unsigned int first, unsigned int second);
};
struct Rva002E99F9Arg1
{
	char m_pad0[0x10];
	int m_10;
	char m_pad14;
	unsigned char m_15;
};
struct Rva002E99F9Query
{
	int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
class Pathfinder
{
public:
	PathfindCell *rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos);
	int FindBrokenBridge(Rva002E99F9Arg1 *a1, const Coord3D * volatile a2, const Coord3D *a3);
private:
	char m_pad0[0x460];
	Rva002E99F9Sub460 m_sub460;
};
// ?FindBrokenBridge@Pathfinder@@QAEHPAURva002E99F9Arg1@@RBUCoord3D@@PBU3@@Z
// @0x002E99F9 211B. a2 is top-level volatile: retail observably writes the
// dead param slot (mov [ebp+0xc]) after the fifth sub-call, and the
// qualifier keeps that store. Flags /O1 /MD /G7: /G7 lowers the ushort
// cell-field loads as plain 16-bit mov (no movzx) like the rowed
// Rva00531A44 find in the same family.
int Pathfinder::FindBrokenBridge(Rva002E99F9Arg1 *a1, const Coord3D * volatile a2, const Coord3D *a3)
{
	PathfindLayerEnum layerA3 = TheTerrainLogic->getLayerForDestination(0, a3);
	PathfindLayerEnum layerA2 = TheTerrainLogic->getLayerForDestination(0, a2);
	PathfindCell *cellA2 = rva002E8BF8(layerA2, a2);
	PathfindCell *cellA3 = rva002E8BF8(layerA3, a3);
	Rva002E99F9Query q;
	q.m_8 |= -1;
	q.m_0 = a1->m_10;
	q.m_C = a1->m_15;
	q.m_4 = 0;
	q.m_5 = 0;
	unsigned short wB;
	unsigned short wA;
	wB = cellA2->m_8;
	unsigned int r1 = m_sub460.rva0053241F(&q, wB);
	wA = cellA3->m_8;
	unsigned int r2 = m_sub460.rva0053241F(&q, wA);
	unsigned int r3 = m_sub460.rva00531FD4(&q, r1);
	unsigned int r4 = m_sub460.rva00531FD4(&q, r2);
	unsigned int r5 = m_sub460.rva0053241F(&q, r3);
	a2 = (const Coord3D *)r5;
	m_sub460.rva0053241F(&q, r4);
	return 0;
}

// ?rva00531FE6@Rva002E99F9Sub460@@QAEG_NPAXG@Z @0x00531FE6 91B
// Target evidence: item bit 3 returns 1; rowed 0x005310E3 supplies a signed count; the
// address-derived 0x0053123A lookup maps negative -1 to 1 and other negative values to 0;
// nonnegative indexes select an Rva00531A44 slot ending in rowed 0x00531B20.
// Structural inference: the class relation to Rva002E99F9Sub460 is supported by thunk
// 0x0053241F which forwards (true, item, value) to this body; item identity remains unknown.
unsigned short Rva002E99F9Sub460::rva00531FE6(bool force, void *item, unsigned short value)
{
	if (*((unsigned char *)item) & 0x08)
		return 1;

	int count = ((Rva005310E3 *)item)->rva005310E3();
	if (force)
		++count;
	int index = rva0053123A(item);
	if (index < 0)
		return index == -1;

	unsigned int slot = count * 7 + index + 0x15E1;
	Rva00531A44 *entry = (Rva00531A44 *)((char *)this + slot * 0x14);
	return entry->rva00531B20(value);
}

// ?rva0053241F@Rva002E99F9Sub460@@QAEGPAXG@Z @0x0053241F 18B
// Forwarder pushing (true, s, w) to rowed 0x00531FE6 ret 8. Evidence: pin
// ?rva0053241F@Rva002E99F9Sub460@@QAEGPAXG@Z; callers in FindBrokenBridge
// 0x002E9A6C 0x002E9A7F 0x002E9AAC 0x002E9ABE plus 0x002E7C4E; sibling
// 0x00531FD4 forwards false. noinline keeps FindBrokenBridge calling the
// thunk as retail does instead of inlining the push-1.
__declspec(noinline) unsigned short Rva002E99F9Sub460::rva0053241F(void *s, unsigned short w)
{
	return rva00531FE6(true, s, w);
}

// ?rva005318DB@Rva002E99F9Sub460@@QAE_NPAX00@Z @0x005318DB 157B. The item
// bit 3 returns true; otherwise rowed 0x005310E3 supplies a count and the
// address-derived 0x0053123A helper supplies an index. Two input records each
// contribute their word at +8 to the two rowed 0x00531720 checks, then the
// address-derived 0x00531757 checks and 0x005317D7 final check. The receiver
// association with Rva002E99F9Sub460 is structural; item and record types
// remain unknown.
bool Rva002E99F9Sub460::rva005318DB(void *item, void *first, void *second)
{
	if (*((unsigned char *)item) & 0x08)
		return true;

	unsigned int count = ((Rva005310E3 *)item)->rva005310E3();
	int index = rva0053123A(item);
	if (index < 0)
		return index == -1;

	unsigned int firstValue = *(unsigned short *)((char *)first + 8);
	unsigned int secondValue = *(unsigned short *)((char *)second + 8);
	Rva00531720 *slot = (Rva00531720 *)this;
	if (slot->rva00531720(count, firstValue) &&
		slot->rva00531720(count, secondValue) &&
		((PathfindZoneManager *)this)->CouldBeInEquivSet(index, firstValue) &&
		((PathfindZoneManager *)this)->CouldBeInEquivSet(index, secondValue))
		return rva005317D7(index, firstValue, secondValue);
	return 0;
}
