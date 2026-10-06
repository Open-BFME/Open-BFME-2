// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0Image@@QAE@XZ, retail 0x002D8FE4, 122 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/ImageCtorThunk.cpp,
// Image::Image): null the texture holder, clear both filename strings, zero
// the sizes and status, and reset the UVs to the full-texture range. The
// retail body follows the reference source statement for statement,
// including the string clears through the 0x36410 pin; the BFME2 deltas are
// the vtable at 0xC037B8 and the member offsets below.

typedef int Int;

#define NULL 0

#include "ascii_string.h"

struct ICoord2D
{
	int x;
	int y;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class Image
{
public:
	Image();
	virtual ~Image();

private:
	AsciiString m_name; // +0x04
	AsciiString m_filename; // +0x08
	ICoord2D m_textureSize; // +0x0C
	Region2D m_UVCoords; // +0x14
	ICoord2D m_imageSize; // +0x24
	void *m_rawTextureData; // +0x2C
	unsigned int m_status; // +0x30
};

// ??0Image@@QAE@XZ
Image::Image()
{
	m_rawTextureData = NULL;
	m_name.clear();
	m_filename.clear();
	m_textureSize.x = 0;
	m_textureSize.y = 0;
	m_UVCoords.lo.x = 0.0f;
	m_UVCoords.lo.y = 0.0f;
	m_UVCoords.hi.x = 1.0f;
	m_UVCoords.hi.y = 1.0f;
	m_imageSize.x = 0;
	m_imageSize.y = 0;
	m_status = 0;
}
