// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// W3DBridgeBuffer::loadBridges, Zero Hour's body. BFME 2 reads the map object
// list through its holder at BfmeTheMapObjectListHolder, fetches each
// location through the out-of-line accessor at 0x0030D631 (the ledger's
// Rva0030D631) and keeps the object's own z under the terrain height.
#include "ascii_string.h"

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	float X;
	float Y;
	float Z;
};

class BfmeRetBWF
{
public:
	float x;
	float y;
	float z;
};

class Rva0030D631
{
public:
	BfmeRetBWF *rva0030D631();
};

class Dict;

enum
{
	FLAG_BRIDGE_POINT1 = 0x010,
	FLAG_BRIDGE_POINT2 = 0x020
};

class MapObject
{
public:
	MapObject *getNext() { return m_nextMapObject; }
	const BfmeRetBWF *getLocation() { return ((Rva0030D631 *)this)->rva0030D631(); }
	bool getFlag(int flag) { return (m_flags & flag) ? true : false; }
	const AsciiString &getName() const { return m_objectName; }
	Dict *getProperties() { return (Dict *)m_properties; }
private:
	char m_pad00[4];
	MapObject *m_nextMapObject; // +0x04
	char m_pad08[0x14 - 0x08];
	AsciiString m_objectName; // +0x14
	char m_pad18[0x20 - 0x18];
	int m_flags; // +0x20
	char m_properties[4]; // +0x24
};

class BfmeMapObjectListHolder
{
public:
	MapObject *m_bfmeHead;
};
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

class BaseHeightMapRenderObjClass
{
public:
	virtual void gap(char (*)[1]);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// TheTerrainRenderObject's height query, slot +0x244.
class BfmeTerrainHeightQuery
{
public:
#define G(n) virtual void gap##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(0A) G(0B) G(0C) G(0D) G(0E) G(0F)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(1A) G(1B) G(1C) G(1D) G(1E) G(1F)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29) G(2A) G(2B) G(2C) G(2D) G(2E) G(2F)
	G(30) G(31) G(32) G(33) G(34) G(35) G(36) G(37) G(38) G(39) G(3A) G(3B) G(3C) G(3D) G(3E) G(3F)
	G(40) G(41) G(42) G(43) G(44) G(45) G(46) G(47) G(48) G(49) G(4A) G(4B) G(4C) G(4D) G(4E) G(4F)
	G(50) G(51) G(52) G(53) G(54) G(55) G(56) G(57) G(58) G(59) G(5A) G(5B) G(5C) G(5D) G(5E) G(5F)
	G(60) G(61) G(62) G(63) G(64) G(65) G(66) G(67) G(68) G(69) G(6A) G(6B) G(6C) G(6D) G(6E) G(6F)
	G(70) G(71) G(72) G(73) G(74) G(75) G(76) G(77) G(78) G(79) G(7A) G(7B) G(7C) G(7D) G(7E) G(7F)
	G(80) G(81) G(82) G(83) G(84) G(85) G(86) G(87) G(88) G(89) G(8A) G(8B) G(8C) G(8D) G(8E) G(8F)
	G(90)
#undef G
	virtual float getHeightMapHeight(float x, float y, void *normal); // +0x244
};

class W3DTerrainLogic
{
public:
#define G(n) virtual void gap##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(0A) G(0B) G(0C) G(0D) G(0E) G(0F)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(1A) G(1B) G(1C) G(1D) G(1E) G(1F)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29) G(2A) G(2B) G(2C) G(2D) G(2E) G(2F)
	G(30)
#undef G
	virtual void updateBridgeDamageStates(void); // +0xC4
};

#define BRIDGE_FLOAT_AMT (0.25f)

class W3DBridgeBuffer
{
public:
	void clearAllBridges();
	void addBridge(Vector3 fromLeft, Vector3 fromRight, AsciiString name, W3DTerrainLogic *pTerrainLogic, Dict *props);
	void loadBridges(W3DTerrainLogic *pTerrainLogic, bool saveGame);
};

// ?loadBridges@W3DBridgeBuffer@@QAEXPAVW3DTerrainLogic@@_N@Z @0x000DFB3C
void W3DBridgeBuffer::loadBridges(W3DTerrainLogic *pTerrainLogic, bool saveGame)
{
	clearAllBridges();
	MapObject *pMapObj;
	MapObject *pMapObj2;
	BfmeTerrainHeightQuery *terrain;
	for (pMapObj = BfmeTheMapObjectListHolder->m_bfmeHead; pMapObj; pMapObj = pMapObj->getNext()) {
		if (pMapObj->getFlag(FLAG_BRIDGE_POINT1)) {
			pMapObj2 = pMapObj->getNext();
			if (pMapObj2 == NULL)
				break;
			if (!pMapObj2->getFlag(FLAG_BRIDGE_POINT2))
				continue;
			float fz = pMapObj->getLocation()->z;
			float fy = pMapObj->getLocation()->y;
			float fx = pMapObj->getLocation()->x;
			Vector3 from(fx, fy, fz);
			terrain = (BfmeTerrainHeightQuery *)TheTerrainRenderObject;
			from.Z = terrain->getHeightMapHeight(from.X, from.Y, NULL) + from.Z + BRIDGE_FLOAT_AMT;
			float tz = pMapObj2->getLocation()->z;
			float ty = pMapObj2->getLocation()->y;
			float tx = pMapObj2->getLocation()->x;
			Vector3 to(tx, ty, tz);
			terrain = (BfmeTerrainHeightQuery *)TheTerrainRenderObject;
			to.Z = terrain->getHeightMapHeight(to.X, to.Y, NULL) + to.Z + BRIDGE_FLOAT_AMT;
			addBridge(from, to, pMapObj->getName(), pTerrainLogic, pMapObj->getProperties());
			pMapObj = pMapObj2;
		}
	}
	if (pTerrainLogic)
		pTerrainLogic->updateBridgeDamageStates();
}
