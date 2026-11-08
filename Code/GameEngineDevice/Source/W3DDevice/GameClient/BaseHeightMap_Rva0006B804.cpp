// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Target 0x0006B804..0x0006B895, RET0. Same-this call to the
// established terrain texture method at 0x0006ACBD identifies the receiver.
// The second surface guard deliberately reloads the first pointer, as retail does.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

class Rva000E6594 { public: void rva000E6594(); };
// The destructor at 0x00073BFE is rowed as ??1W3DTaint@@QAE@XZ (W3DTaintDtor.cpp).
class WorldHeightMap;
class W3DTaint
{
public:
	bool ReAcquireResources();
	~W3DTaint();
	W3DTaint();
	void init(WorldHeightMap*,float,float);
	char data[80]; // +0x00
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The header keeps +0x3820/+0x382C as string words and the buffers at
// +0x3850/+0x3854 as opaque pointers; read them as the views this body uses.
static __forceinline AsciiString &terrainString(unsigned int &word)
{
	return *reinterpret_cast<AsciiString *>(&word);
}

static __forceinline Rva000E6594 *vegetationBuffer(W3DTreeBuffer *buffer)
{
	return reinterpret_cast<Rva000E6594 *>(buffer);
}

static __forceinline Rva000E6594 *vegetationBuffer(W3DShrubBuffer *buffer)
{
	return reinterpret_cast<Rva000E6594 *>(buffer);
}

void BaseHeightMapRenderObjClass::rva0006B804()
{
    if (m_treeBuffer) vegetationBuffer(m_treeBuffer)->rva000E6594();
    if (m_shrubBuffer) vegetationBuffer(m_treeBuffer)->rva000E6594();
    reinterpret_cast<unsigned char *>(TheWritableGlobalData)[0xC6A] = 0;
    W3DTaint *oldResource = field387C;
    if (oldResource) {
        oldResource->W3DTaint::~W3DTaint();
        operator delete(oldResource);
        field387C = 0;
    }
    rva0006ACBD(terrainString(field3820));
    rva0006ABE7(terrainString(field382C), field3834);
}
