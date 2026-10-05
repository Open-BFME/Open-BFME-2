// ?rva002ED72B@Rva002ED72B@@QAEPAV1@HPAVObject@@HPBUCoord3D@@M@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /MD /arch:SSE
// ?rva002ED72B@Rva002ED72B@@QAEPAU01@HPAUObject@@HPAUCoord3D@@M@Z @0x002ED72B 139B: init via Split plus layer.
// Evidence: caller 0x002FA27A; callees rowed getControllingPlayer 0x0028AFA9 twice plus Split 0x002EBCA7 plus getLayer pin 0x002802FE plus TheTerrainLogic; members +0x00 +0x04 Object +0x08 +0x0C flag +0x0D odd +0x10 half +0x14 layer +0x18 float +0x24 cleared +0x28 Coord3D; Player +0x5C; neighbours Rva002EBCD6Split Rva002ED7B6Finish same /O1 /MD.
class Object;
class Player
{
public:
	unsigned char m_pad[0x5C];
	int m_5C;
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
enum PathfindLayerEnum
{
	LAYER_0 = 0
};
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *dest);
};
extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
};

void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd);

class Rva002ED72B
{
public:
	Rva002ED72B *rva002ED72B(int a, Object *b, int c, const Coord3D *d, float e);
private:
	int m_00;
	Object *volatile m_04;
	int m_08;
	unsigned char m_0C;
	unsigned char m_0D;
	char m_pad0E[2];
	int m_10;
	int m_14;
	float m_18;
	char m_pad1C[0x24 - 0x1C];
	int m_24;
	Coord3D m_28;
};

// ?rva002ED72B@Rva002ED72B@@QAEPAV1@HPAVObject@@HPBUCoord3D@@M@Z present-unmatched
Rva002ED72B *Rva002ED72B::rva002ED72B(int a, Object *b, int c, const Coord3D *d, float e)
{
	m_24 = 0;
	m_00 = a;
	m_04 = b;
	m_08 = c;
	m_18 = e;
	m_28.x = d->x;
	m_28.y = d->y;
	m_28.z = d->z;
	m_0C = (unsigned char)((m_04->getControllingPlayer() == 0 || m_04->getControllingPlayer()->m_5C != 1) ? 1 : 0);
	Rva002EBCA7Split(m_04, &m_10, &m_0D);
	m_14 = TheTerrainLogic->getLayerForDestination(b, d);
	return this;
}
