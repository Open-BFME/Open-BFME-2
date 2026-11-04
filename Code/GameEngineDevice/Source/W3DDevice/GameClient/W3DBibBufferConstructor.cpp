// cl: /DBFME_SORTING_DWORD_DRAW /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfmecamera /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/indexbuffercount /Ireference/shims/vertexbufferlock /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "W3DBibBufferLayout.h"
class BFME2ParticleTextureHandle { public:
 TextureClass *Ptr;
 ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};
#include "../../../Include/W3DDevice/GameClient/TextureAsset.h"
class ShroudFilter { public: char pad[12]; int u,v; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
// ZH W3DBibBuffer.cpp (BF1 donor 575ba2b04) supplies the constructor purpose,
// texture names and clamp operations. BFME2 parent allocation at 0x6CC5C calls
// this body for its +385C bib owner and allocates 109D0 bytes. Native +10/+14
// are counted holders, unlike ZH raw pointers; the native array helper calls
// the already-owned 22B TBib constructor 1000 times with stride 68. The added
// two dwords at +20 are opaque: this constructor does not initialize them.
// All factory/assignment/filter/buffer/release callees are existing owners.
W3DBibBuffer::W3DBibBuffer() {
 m_initialized=false;
 m_vertexBib=0; m_indexBib=0; m_curNumBibVertices=0; m_curNumBibIndices=0;
 m_numBibs=0; m_anythingChanged=true;
 m_indexBibSize=384; m_vertexBibSize=256;
 allocateBibBuffers();
 m_bibTexture=(const RefCountPtr<TextureClass> &)TextureAsset::Get("TBBib.tga",0,0);
 m_highlightBibTexture=(const RefCountPtr<TextureClass> &)TextureAsset::Get("TBRedBib.tga",0,0);
 ((ShroudTexture *)&m_bibTexture)->getFilter()->u=1;
 ((ShroudTexture *)&m_bibTexture)->getFilter()->v=1;
 ((ShroudTexture *)&m_highlightBibTexture)->getFilter()->u=1;
 ((ShroudTexture *)&m_highlightBibTexture)->getFilter()->v=1;
 m_initialized=true;
}
