// cl: /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString;

class NameKeyGenerator
{
public:
	NameKeyType Rva002D91AF(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Image;

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

protected:
	ImageNameMap m_imageMap;
};

// ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z, retail 0x002D92F6 (53B).
const Image *ImageCollection::findImageByName(const AsciiString &name)
{
	ImageNameMap::const_iterator it = m_imageMap.find(TheNameKeyGenerator->Rva002D91AF(name));
	return it == m_imageMap.end() ? NULL : it->second;
}
