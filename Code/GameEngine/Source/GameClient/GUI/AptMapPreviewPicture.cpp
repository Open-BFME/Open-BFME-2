// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE2 /DNDEBUG /MD /EHsc
// ?rva0057D10F@AptMapPreview@@QAEXPAVMapMetaData@@@Z @0x0057D10F 139B
// Evidence: caller 0x0057E058 passes MapMetaData* (same slot as bfmeSetMapTitle
// 0x0057C8D1 and bfmeSetMapDescription 0x0057C892); callee bfmeCreateMapPictureImage
// 0x0057CDC3 takes MapMetaData+0x50 AsciiString; fallback uses "MissingMap" via
// rowed StringBase ctor 0x00037BA0 plus rowed findImageByName 0x002D92F6 through
// g_00DFF078 and rowed releaseBuffer 0x00036410; flag +0x60 selects ownership.
#include "ascii_string.h"

void __cdecl operator delete(void *);

class Image
{
public:
	virtual void *rva0057D10F_virt0(unsigned int flag);
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern class ImageCollection *TheMappedImageCollection;

Image *bfmeCreateMapPictureImage(const AsciiString &mapName);

class MapMetaData
{
public:
	char m_pad[0x50];
	AsciiString m_mapFile;
};

class AptMapPreview
{
public:
	void rva0057D10F(MapMetaData *map);
private:
	char m_pad[0x5C];
	Image *m_image;
	bool m_ownsImage;
};

void AptMapPreview::rva0057D10F(MapMetaData *map)
{
	if (m_ownsImage)
	{
		if (m_image)
		{
			void *p = m_image->rva0057D10F_virt0(0);
			::operator delete(p);
			m_image = 0;
		}
	}
	Image *img = 0;
	if (map)
	{
		img = bfmeCreateMapPictureImage(map->m_mapFile);
		m_ownsImage = true;
	}
	if (img == 0)
	{
		{
			AsciiString tmp("MissingMap");
			img = (Image *)TheMappedImageCollection->findImageByName(tmp);
		}
		m_ownsImage = false;
	}
	m_image = img;
}
