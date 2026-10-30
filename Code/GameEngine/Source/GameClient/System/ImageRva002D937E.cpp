// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngineDevice/Source/W3DDevice/GameClient /ICode/GameEngine/Source/GameClient/System /ICode
// stlport
//
// ?rva002D937E@Image@@QAEXXZ retail 0x002D937E (217B): lazy texture setup and
// registry; filename +8, holder +0x2C, status +0x30. Exact via W7-D3
// sweepeq4x equal-arm (frame slot ranking).
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngineDevice/Source/W3DDevice/GameClient /ICode/GameEngine/Source/GameClient/System /ICode
// stlport
// Reference BF1 f98983a7d and ZH Image.cpp establish Image filename/status.
// Target 0x002D937E..0x002D9457 supplies the lazy texture setup and registry;
// no original method name is asserted. Image.cpp's ctor/dtor independently prove
// filename +8, holder +2C, status +30. Existing helper names denote ABI views.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include "ascii_string.h"
#include "BFME2ParticleTextureHandles.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::_Rb_tree_base(const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> void _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_erase(_Rb_tree_node<Rva001408C0Target *> *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
class ShroudFilter;
class ShroudTexture { public: ShroudFilter *getFilter(); };
class TextureAsset { public: static BFME2ParticleTextureHandle Get(const char*,int,int); void rva00132FE9(bool); };
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
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
class INI;
class BfmeMapPictureTexture;
class Image
{
public:
	Image();
	virtual ~Image();
	unsigned int setStatus(unsigned int bit);
	unsigned int clearStatus(unsigned int bit);
	void bfmeSetTexture(const BfmeMapPictureTexture &texture);
	void rva002D937E();
	const AsciiString &getName() const { return m_name; }
	const AsciiString &bfme_image_name_fi() const { return m_name; }
	void setImageSize(ICoord2D *size);
	void setUV(Region2D *uv) { if (uv) m_UVCoords = *uv; }
	const ICoord2D *getTextureSize(void) const { return &m_textureSize; }

	int getImageWidth(void) const { return m_imageSize.x; }
	int getImageHeight(void) const { return m_imageSize.y; }

	static void parseImageCoords(INI *ini, void *instance, void *store, const void *userData);
	static void parseImageStatus(INI *ini, void *instance, void *store, const void *userData);

private:
	AsciiString m_name; // +0x04
	AsciiString m_filename; // +0x08
	ICoord2D m_textureSize; // +0x0C
	Region2D m_UVCoords; // +0x14
	ICoord2D m_imageSize; // +0x24
	BfmeMapPictureTexture *m_texture; // +0x2C
	unsigned int m_status; // +0x30
};
void Image::rva002D937E()
{
 const AsciiString *source=&m_filename;
 if(reinterpret_cast<const StringBase<char>*>(source)->isEmpty()	/* rowed 0x00001E2F */) return;
 if(m_texture || (m_status&2)) return;
 BFME2ParticleTextureHandle texture=TextureAsset::Get(source->str(),1,0);
 ShroudTexture *getter=reinterpret_cast<ShroudTexture*>(&texture);
 reinterpret_cast<ImageTextureOptions*>((source ? (getter->getFilter()) : (getter->getFilter())))->option10=1;
 reinterpret_cast<ImageTextureOptions*>(getter->getFilter())->optionC=1;
 reinterpret_cast<TextureAsset*>(&texture)->rva00132FE9(true);
 if(Rva0134FAA0) {
  AssetList00208F90 assets;
  assets<<m_filename;
  bfmeMergeReceiverKeys((int)&assets);
 }
}
