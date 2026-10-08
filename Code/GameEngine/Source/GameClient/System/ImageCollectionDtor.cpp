// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ImageCollection::~ImageCollection, BFME2 retail 0x002D9283 (115B), slot 0
// of vtable 0x00C03878 through ??_G at 0x002D9362. Zero Hour's destructor
// (GameClient/System/Image.cpp) walks the image map and frees every image;
// BFME 2 frees them with a global delete (virtual destructor with flag 0,
// then operator delete) where Zero Hour returned them to their pool. The
// map's destructor (0x002D922A) and SubsystemInterface's (0x001B4E74) follow.
// Class view as in ImageCollectionFindImage.cpp.

#include <map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType Rva002D91AF(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Image
{
public:
	virtual ~Image();
	const AsciiString &getName() const { return m_name; }

private:
	AsciiString m_name;
};

typedef _STL::map<unsigned int, Image *> ImageNameMap;
// TU-local BFME2 SubsystemInterface (12-byte base, retail-proven).
#define __SUBSYSTEMINTERFACE_H_
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfmeBasePad[8];
};

class ImageCollection : public SubsystemInterface
{
public:
	const Image *findImageByName(const AsciiString &name);
	void addImage(Image *image);
	virtual ~ImageCollection();

protected:
	ImageNameMap m_imageMap;
};


ImageCollection::~ImageCollection()
{
	for (ImageNameMap::iterator it = m_imageMap.begin(); it != m_imageMap.end(); ++it)
		::delete it->second;
}
