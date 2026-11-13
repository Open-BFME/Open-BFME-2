// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?reset@BaseHeightMapRenderObjClass@@UAEXXZ, retail 0x0006D5A7..0x0006D6D9
// (306 bytes, no direct callers: a vtable slot). Zero Hour's
// BaseHeightMapRenderObjClass::reset (BaseHeightMap.cpp) in its BFME2 form:
// every vegetation/road/bridge/bib/prop buffer cleared through its rowed reset
// (null-checked), the scorch ring emptied inline (+0x3790/+0x3794/+0x3798 and a
// new count at +0x37AC), the two visibility vectors (+0x37EC/+0x3800)
// cleared, both shroud-like layers (+0x3878/+0x387C) reset and given their
// border level from GlobalData (+0xBEA / +0xC04), and the second terrain
// texture reloaded from the empty name while the first (+0x381C/+0x3820) is
// released. Receiver evidence: all the buffer pointers are the ones the
// neighbouring draw/update steps (0x0006B895, 0x0006669F) use.
// WWLib always.h defines the array placement forms itself.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"

namespace _STL { template<> void vector<bool, allocator<bool> >::clear(); }

#include "../../../Include/W3DDevice/GameClient/W3DTreeBufferClass.h"
class Rva000D3A17
{
public:
	Rva000D3A17();
	~Rva000D3A17();
	void rva000D3A17();
	char data[272]; // +0x00
};
class W3DShrubBuffer { public: void rva000E7016(); };
#include "../../../../GameEngine/Include/GameLogic/Rva000EE198Owner.h"
class BaseHeightMapRenderObjClass;
class WorldHeightMap;
class W3DRoadBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void loadRoads();
protected:
	void freeRoadBuffers();
	void allocateRoadBuffers();
public:
	W3DRoadBuffer();
	~W3DRoadBuffer();
	void clearAllRoads();
	void setMap(WorldHeightMap*);
	char data[80]; // +0x00
};
#include "../../../Include/W3DDevice/GameClient/W3DBridgeBufferClass.h"
#include "../../../Include/W3DDevice/GameClient/W3DFloorBuffer.h"
enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};
class Vector3;
class W3DBibBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void addBibDrawable(Vector3 corners[4], DrawableID id, bool highlight);
	void removeHighlighting();
	void clearAllBibs();
	void removeBib(ObjectID id);
	void removeBibDrawable(DrawableID id);
	void addBib(Vector3 corners[4], ObjectID id, bool highlight);
protected:
	void freeBibBuffers();
	void allocateBibBuffers();
public:
	W3DBibBuffer();
	~W3DBibBuffer();
	char data[68048]; // +0x00
};
#include "../../../Include/W3DDevice/GameClient/Rva000731AE.h"
class Rva000729CC { public: void rva000729CC(bool level); };
#include "../../../Include/W3DDevice/GameClient/Rva00073C7A.h"
struct BfmeResetResource;
#include "../../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"

class GlobalData
{
public:
	char m_pad000[0xBEA];
	bool m_shroudAlphaA;	// +0xBEA
	char m_padBEB[0xC04 - 0xBEB];
	bool m_shroudAlphaB;	// +0xC04
};
extern GlobalData *TheWritableGlobalData;

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
#define REFCOUNT_H
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// TU-local views of the header's untyped words: the two visibility bit
// vectors, the first terrain texture and its name, and the buffers whose
// reset entry points this body calls.
static __forceinline _STL::vector<bool> &visibilityBits(_STL::vector<bool> &storage)
{
	return storage;
}
static __forceinline BfmeResetTextureRef &terrainTexture(RefCountPtr<TextureClass> &word)
{
	return *reinterpret_cast<BfmeResetTextureRef *>(&word);
}
static __forceinline Rva000EE198Owner *propBuffer(W3DPropBuffer *buffer)
{
	return reinterpret_cast<Rva000EE198Owner *>(buffer);
}
static __forceinline W3DFloorBuffer *floorBuffer(void *buffer)
{
	return reinterpret_cast<W3DFloorBuffer *>(buffer);
}
static __forceinline Rva000D3A17 *buffer3874(void *buffer)
{
	return reinterpret_cast<Rva000D3A17 *>(buffer);
}
static __forceinline Rva000731AE *shroudLayer(W3DShroud *layer)
{
	return reinterpret_cast<Rva000731AE *>(layer);
}
static __forceinline Rva00073C7A *taintLayer(W3DTaint *layer)
{
	return reinterpret_cast<Rva00073C7A *>(layer);
}

void BaseHeightMapRenderObjClass::reset()
{
	field3880 = true;
	if (m_treeBuffer)
		m_treeBuffer->rva000EA24D();
	if (field3874)
		buffer3874(field3874)->rva000D3A17();
	if (m_shrubBuffer)
		m_shrubBuffer->rva000E7016();
	if (m_propBuffer)
		propBuffer(m_propBuffer)->rva000EE198();
	m_numScorches = 0;
	m_scorchesInBuffer = 0;
	field3798 = 0;
	field37AC = 0;
	if (m_roadBuffer)
		m_roadBuffer->clearAllRoads();
	if (m_bridgeBuffer)
		m_bridgeBuffer->clearAllBridges();
	if (field3860)
		floorBuffer(field3860)->rva000E598B();
	if (m_bibBuffer)
		m_bibBuffer->clearAllBibs();
	visibilityBits(unknown37EC).clear();
	visibilityBits(unknown3800).clear();
	if (m_shroud) {
		shroudLayer(m_shroud)->rva000731AE();
		((Rva000729CC *)m_shroud)->rva000729CC(TheWritableGlobalData->m_shroudAlphaA);
	}
	if (field387C) {
		taintLayer(field387C)->rva00073C7A();
		((Rva000729CC *)field387C)->rva000729CC(TheWritableGlobalData->m_shroudAlphaB);
	}
	rva0006ABE7(AsciiString(""), false);
	terrainTexture(field381C).clear();
	field3820.clear();
}
