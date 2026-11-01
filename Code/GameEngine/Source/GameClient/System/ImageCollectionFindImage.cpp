// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ImageCollection::findImageByName, BFME2 retail 0x002D92F6 (53B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/System/Image.cpp
// (BFME1 0x005D1D10): the key comes from the rowed AsciiString lowercase-key
// wrapper at 0x2D91AF through TheNameKeyGenerator (global 0xDF36A4, DIR32
// from retail), then a map<unsigned,Image*>::find with a NULL-on-miss return.
// The map sits at +0xC behind the retail-proven 12-byte SubsystemInterface
// base (vptr + byte@4 + dword@8 zeroed by 0x001B4E63).

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

class Image
{
public:
	virtual ~Image();
	const AsciiString &getName() const { return m_name; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the
	// original copy loses to the first-in-order copy. No flags touched.
	const AsciiString &bfme_image_name_fi() const { return m_name; }

private:
	AsciiString m_name;
};

typedef _STL::map<unsigned int, Image *> ImageNameMap;
// TU-local BFME2 SubsystemInterface (12-byte base, retail-proven).
#define __SUBSYSTEMINTERFACE_H_
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class ImageCollection : public SubsystemInterface
{
public:
	const Image *findImageByName(const AsciiString &name);
	void addImage(Image *image);

protected:
	ImageNameMap m_imageMap;
};

// Declaration-only view of ImageNameMap whose subscript stays out-of-line:
// retail folds every unsigned-key pointer-map operator[] into the single
// shared worker at 0x2077D6 (which drives the rowed PAX _M_lower_bound at
// 0x4FF3B6), so the call below is pinned there instead of inlining.
class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

// ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z, retail 0x002D92F6 (53B).
const Image *ImageCollection::findImageByName(const AsciiString &name)
{
	ImageNameMap::const_iterator it = m_imageMap.find(TheNameKeyGenerator->Rva002D91AF(name));
	return it == m_imageMap.end() ? NULL : it->second;
}

// ?addImage@ImageCollection@@QAEXPAVImage@@@Z, retail 0x002D9457 (48B).
void ImageCollection::addImage(Image *image)
{
	((ImageSubscriptMap *)&m_imageMap)->operator[](TheNameKeyGenerator->Rva002D91AF(image->bfme_image_name_fi())) = image;
}
