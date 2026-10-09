#pragma once
// Target MaterialInfo texture-vector getter at 16EE40: array24, four-byte
// owning cells and 16-bit refcount at texture+4. WB A085F0 supplies the
// Get_Texture relationship; the original owning handle spelling is unknown.
#include "../../../../GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"
class FloorMaterialHandle {
public:
 TextureClass *pointer;
 FloorMaterialHandle() : pointer(0) {}
 __forceinline FloorMaterialHandle(const FloorMaterialHandle &other) : pointer(other.pointer) { if(pointer)++pointer->m_refCount; }
 ~FloorMaterialHandle() { if(pointer)pointer->Release_Ref(); }
};
class Rva00016EE40 {
 char prefix[0x24]; FloorMaterialHandle *textures;
public: FloorMaterialHandle getTexture(int);
};
