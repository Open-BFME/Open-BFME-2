// ?rva002D937E@Image@@QAEXXZ
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngineDevice/Source/W3DDevice/GameClient
// stlport
// Reference BF1 f98983a7d and ZH Image.cpp establish Image filename/status.
// Target 0x002D937E..0x002D9457 supplies the lazy texture setup and registry;
// no original method name is asserted. ImageCtor/ImageDtor independently prove
// filename +8, holder +2C, status +30. Existing helper names denote ABI views.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include "ascii_string.h"
#include "BFME2ParticleTextureHandles.h"

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
class ShroudFilter;
class ShroudTexture { public: ShroudFilter *getFilter(); };
class TextureAsset { public: void rva00132FE9(bool); };
class BfmeStringPresenceValue { public: bool isEmpty() const; };
struct ImageTextureOptions { unsigned char pad[12]; int optionC,option10; };
struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key,_STL::less<Rva001408C0Key>,_STL::allocator<Rva001408C0Key> > Rva001408C0Set;
struct AssetList00208F90 {
 Rva001408C0Set m_prototypes;
 unsigned m_treeLayoutPad;
 bool m_changed;
 AssetList00208F90():m_treeLayoutPad(0),m_changed(true) {}
 AssetList00208F90 &operator<<(const AsciiString&);
};
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
void bfmeMergeReceiverKeys(int);
class Image {
public:
 virtual ~Image();
 void rva002D937E();
 AsciiString name,filename;
 unsigned char geometry[0x20];
 void *textureHolder;
 unsigned status;
};
void Image::rva002D937E()
{
 const AsciiString *source=&filename;
 if(reinterpret_cast<const BfmeStringPresenceValue*>(source)->isEmpty()) return;
 if(textureHolder || (status&2)) return;
 BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(source->str(),1,0);
 ShroudTexture *getter=reinterpret_cast<ShroudTexture*>(&texture);
 reinterpret_cast<ImageTextureOptions*>(getter->getFilter())->option10=1;
 reinterpret_cast<ImageTextureOptions*>(getter->getFilter())->optionC=1;
 reinterpret_cast<TextureAsset*>(&texture)->rva00132FE9(true);
 if(Rva0134FAA0) {
  AssetList00208F90 assets;
  assets<<filename;
  bfmeMergeReceiverKeys((int)&assets);
 }
}
