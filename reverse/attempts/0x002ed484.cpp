// ?rva002ED484@Rva002ED484@@QAEPAV1@HPAVObject@@HPBUCoord3D@@1MH@Z
// partial score=0.95 date=2026-10-07
// cl: /MD /Oy-
//
// ?rva002ED484@Rva002ED484@@QAEPAV1@HPAVObject@@HPBUCoord3D@@1MH@Z @0x002ED484 177B init via Split.
// Evidence: same init-via-Split shape as neighbour Rva002ED7B6 0x002ED7B6 65B; calls rowed Object
// getControllingPlayer 0x0028AFA9 rowed Split 0x002EBCA7 pinned TerrainLogic getLayer 0x002802FE
// global TheTerrainLogic; callers 0x002FD14D 0x002FD302.
void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd);

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_ONE = 1
};

class Player
{
public:
	unsigned char m_pad[0x5c];
	int m_5c;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Rva002ED484
{
public:
	Rva002ED484 *rva002ED484(int a1, Object *a2, int a3, const Coord3D *a4, const Coord3D *a5, float a6, int a7);
private:
	int m_00;
	Object *m_04;
	int m_08;
	unsigned char m_0c;
	unsigned char m_0d;
	char m_pad0e[2];
	int m_10;
	const Coord3D *m_14;
	int m_18;
	float m_1c;
	char m_pad20[8];
	int m_28;
	int m_2c;
	Coord3D m_30;
};

Rva002ED484 *Rva002ED484::rva002ED484(int a1, Object *a2, int a3, const Coord3D *a4, const Coord3D *a5, float a6, int a7)
{
	m_28 = 0;
	m_00 = a1;
	m_08 = a3;
	m_14 = a5;
	m_2c = a7;
	m_04 = a2;
	m_1c = a6;
	m_30 = *a4;
	unsigned char b;
	Player *p1 = m_04->getControllingPlayer();
	if (p1 != 0) {
		Player *p2 = m_04->getControllingPlayer();
		if (p2->m_5c == 1) {
			b = false;
		} else {
			b = true;
		}
	} else {
		b = true;
	}
	m_0c = b;
	Rva002EBCA7Split(m_04, &m_10, &m_0d);
	m_18 = TheTerrainLogic->getLayerForDestination(a2, &m_30);
	if (m_14 != 0) {
		m_18 = TheTerrainLogic->getLayerForDestination(0, m_14);
	}
	return this;
}
