// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
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
// BFME2 SubsystemInterface (12-byte base, 14-slot vtable 0x00BD77A0) from the
// subsystem shim, so this unit emits the retail 14-slot ImageCollection vtable.
typedef bool Bool;
#include "subsystem_interface.h"

class ImageCollection : public SubsystemInterface
{
public:
	const Image *findImageByName(const AsciiString &name);
	void addImage(Image *image);
	virtual ~ImageCollection();
	// Retail vtable 0x00C03878 slots 1/9/10 (init/reset/update) are the folded
	// empty body at 0x000B3FD0, as in Zero Hour's ImageCollection.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

protected:
	ImageNameMap m_imageMap;
};


ImageCollection::~ImageCollection()
{
	for (ImageNameMap::iterator it = m_imageMap.begin(); it != m_imageMap.end(); ++it)
		::delete it->second;
}
