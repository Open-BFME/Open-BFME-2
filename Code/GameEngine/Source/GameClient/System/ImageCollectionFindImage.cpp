// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ImageCollection::findImageByName, BFME2 retail 0x002D92F6 (53B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/System/Image.cpp
// (BFME1 0x005D1D10): the key comes from the rowed AsciiString lowercase-key
// wrapper at 0x2D91AF through TheNameKeyGenerator (global 0xDF36A4, DIR32
// from retail), then a map<unsigned,Image*>::find with a NULL-on-miss return.
// Image and ImageCollection (map at +0xC behind the 12-byte
// SubsystemInterface base) come from the canonical GameClient/Image.h.

#include <map>
// Preserve the native inline unsigned comparison without an external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<unsigned int>::operator()(const unsigned int &left, const unsigned int &right) const
{ return left < right; }
}


enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/GameClient/Image.h"

typedef _STL::map<unsigned int, Image *> ImageNameMap;

// Declaration-only view of ImageNameMap whose subscript stays out-of-line:
// retail folds every unsigned-key pointer-map operator[] into the single
// shared worker at 0x2077D6 (which drives the rowed PAX _M_lower_bound at
// 0x4FF3B6), so the call below is pinned there instead of inlining.
#include "../../../Include/GameClient/ImageSubscriptMap.h"

// ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z, retail 0x002D92F6 (53B).
const Image *ImageCollection::findImageByName(const AsciiString &name)
{
	ImageNameMap::const_iterator it = m_imageMap.find(TheNameKeyGenerator->Rva002D91AF(name));
	return it == m_imageMap.end() ? NULL : it->second;
}

// ?addImage@ImageCollection@@QAEXPAVImage@@@Z, retail 0x002D9457 (48B).
void ImageCollection::addImage(Image *image)
{
	((ImageSubscriptMap *)&m_imageMap)->operator[](TheNameKeyGenerator->Rva002D91AF(image->getName())) = image;
}
