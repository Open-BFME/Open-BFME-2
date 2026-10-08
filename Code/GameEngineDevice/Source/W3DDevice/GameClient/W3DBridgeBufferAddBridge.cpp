// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// W3DBridgeBuffer::addBridge, Zero Hour's body. BFME 2's terrain logic takes
// the bridge template name by reference (retail pushes &name to its slot at
// +0xB8). BridgeInfo is the ledger's Rva0027C36A (0xA8 bytes, bridgeIndex at
// +0x4C); bridges are 0x114 bytes from +0x10 with the count at +0xD7B0.
#include "ascii_string.h"

class Vector3
{
public:
	Vector3(const Vector3 &v) { x = v.x; y = v.y; z = v.z; }
	float x;
	float y;
	float z;
};

class Region3D
{
public:
	Region3D();
	float m_x;
	float m_y;
	float m_z;
};

class Rva0027C36ASix
{
public:
	Rva0027C36ASix();
	char m_d[6];
};

// Zero Hour's BridgeInfo.
class Rva0027C36A
{
public:
	Rva0027C36A();
	char m_pad00[0x4C];
	int bridgeIndex; // +0x4C
	char m_pad50[0x6C - 0x50];
	Region3D m_6c[4];
	Rva0027C36ASix m_9c[2];
};

class Dict;

class W3DTerrainLogic
{
public:
	virtual void gap00(); virtual void gap04(); virtual void gap08(); virtual void gap0C();
	virtual void gap10(); virtual void gap14(); virtual void gap18(); virtual void gap1C();
	virtual void gap20(); virtual void gap24(); virtual void gap28(); virtual void gap2C();
	virtual void gap30(); virtual void gap34(); virtual void gap38(); virtual void gap3C();
	virtual void gap40(); virtual void gap44(); virtual void gap48(); virtual void gap4C();
	virtual void gap50(); virtual void gap54(); virtual void gap58(); virtual void gap5C();
	virtual void gap60(); virtual void gap64(); virtual void gap68(); virtual void gap6C();
	virtual void gap70(); virtual void gap74(); virtual void gap78(); virtual void gap7C();
	virtual void gap80(); virtual void gap84(); virtual void gap88(); virtual void gap8C();
	virtual void gap90(); virtual void gap94(); virtual void gap98(); virtual void gap9C();
	virtual void gapA0(); virtual void gapA4(); virtual void gapA8(); virtual void gapAC();
	virtual void gapB0(); virtual void gapB4();
	virtual void addBridgeToLogic(Rva0027C36A *pInfo, Dict *props, const AsciiString &bridgeTemplateName); // +0xB8
};

enum BodyDamageType
{
	BODY_PRISTINE
};

class W3DBridge
{
public:
	void init(Vector3 fromLoc, Vector3 toLoc, AsciiString name);
	bool load(BodyDamageType curDamageState);
	void getBridgeInfo(Rva0027C36A *pInfo);
private:
	char m_pad[0x114];
};

enum { MAX_BRIDGES = 200 };

class W3DBridgeBuffer
{
public:
	void addBridge(Vector3 fromLeft, Vector3 fromRight, AsciiString name, W3DTerrainLogic *pTerrainLogic, Dict *props);
private:
	void *m_vertexBridge; // +0x00
	void *m_indexBridge; // +0x04
	int m_curNumBridgeVertices; // +0x08
	int m_curNumBridgeIndices; // +0x0C
	W3DBridge m_bridges[MAX_BRIDGES]; // +0x10
	int m_numBridges; // +0xD7B0
	bool m_initialized; // +0xD7B4
};

// ?addBridge@W3DBridgeBuffer@@QAEXVVector3@@0VAsciiString@@PAVW3DTerrainLogic@@PAVDict@@@Z @0x000DF612
void W3DBridgeBuffer::addBridge(Vector3 fromLeft, Vector3 fromRight, AsciiString name, W3DTerrainLogic *pTerrainLogic, Dict *props)
{
	if (m_numBridges >= MAX_BRIDGES) {
		return;
	}
	if (!m_initialized) {
		return;
	}
	m_bridges[m_numBridges].init(fromLeft, fromRight, name);
	if (m_bridges[m_numBridges].load(BODY_PRISTINE)) {
		W3DBridge *pBridge = &m_bridges[m_numBridges];
		if (pTerrainLogic) {
			Rva0027C36A info;
			pBridge->getBridgeInfo(&info);
			info.bridgeIndex = m_numBridges;
			pTerrainLogic->addBridgeToLogic(&info, props, name);
		}
		m_numBridges++;
	}
}
