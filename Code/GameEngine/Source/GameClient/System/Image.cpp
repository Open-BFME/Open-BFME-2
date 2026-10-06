// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE

// Image::clearStatus, retail 0x002D8E72 (17B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/System/Image.cpp
// (BFME1 0x005D1C30). Member offsets follow the proven ImageCtor TU in this
// directory (m_status at +0x30).

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

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	int scanInt(const char *token);
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
};

// Zero Hour's file-static imageStatusNames table ("ROTATED_90_CLOCKWISE",
// "RAW_TEXTURE", NULL) lives at retail 0x00DBCEDC; only its address is used.
const char *imageStatusNames[] = { "ROTATED_90_CLOCKWISE", "RAW_TEXTURE", 0 };

enum
{
	IMAGE_STATUS_ROTATED_90_CLOCKWISE = 0x00000001
};

class Image
{
public:
	virtual ~Image();
	unsigned int clearStatus(unsigned int bit);
	void setImageSize(ICoord2D *size);
  void setUV(Region2D *uv) { if (uv) m_UVCoords = *uv; }
	const ICoord2D *getTextureSize(void) const { return &m_textureSize; }

	int getImageWidth(void) const { return m_imageSize.x; }
	int getImageHeight(void) const { return m_imageSize.y; }

	static void parseImageCoords(INI *ini, void *instance, void *store, const void *userData);
	static void parseImageStatus(INI *ini, void *instance, void *store, const void *userData);

private:
	AsciiString m_name;
	AsciiString m_filename;
	ICoord2D m_textureSize;
	Region2D m_UVCoords;
	ICoord2D m_imageSize;
	void *m_rawTextureData;
	unsigned int m_status;
};

// ?clearStatus@Image@@QAEII@Z, retail 0x002D8E72 (17B).
unsigned int Image::clearStatus(unsigned int bit)
{
	unsigned int prevStatus = m_status;

	m_status &= ~bit;
	return prevStatus;
}

// ?setImageSize@Image@@QAEXPAUICoord2D@@@Z, retail 0x0004D717 (18B).
inline void Image::setImageSize(ICoord2D *size)
{
	m_imageSize = *size;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (Image::*_bfmeInlineAnchor_Image_0)(ICoord2D *size) = &Image::setImageSize;

//-------------------------------------------------------------------------------------------------
/** Parse an image coordinates in the form of
	*
	* COORDS = Left:AAA Top:BBB Right:CCC Bottom:DDD
	*
	* Zero Hour GameClient/System/Image.cpp. BFME pulls the right/bottom edge in
	* by one texel (as BFME 1 does), and BFME 2 scales by the reciprocal of the
	* texture size rather than dividing each coordinate. */
//-------------------------------------------------------------------------------------------------
void Image::parseImageCoords( INI* ini, void *instance, void *store, const void* /*userData*/ )
{
	int left = ini->scanInt(ini->getNextSubToken("Left"));
	int top = ini->scanInt(ini->getNextSubToken("Top"));
	int right = ini->scanInt(ini->getNextSubToken("Right"));
	int bottom = ini->scanInt(ini->getNextSubToken("Bottom"));

	// get the image we're storing in
	Image *theImage = (Image *)instance;

	//
	// store the UV coords based on what we've read in and the texture size
	// defined for this image
	//
	Region2D uvCoords;

	uvCoords.lo.x = (float)left;
	uvCoords.lo.y = (float)top;
	uvCoords.hi.x = (float)right - 1.0f;
	uvCoords.hi.y = (float)bottom - 1.0f;
	
	// adjust the coords by texture size
	const ICoord2D *textureSize = theImage->getTextureSize();
	if( textureSize->x )
	{
		float scale = 1.0f / (float)textureSize->x;
		uvCoords.lo.x *= scale;
		uvCoords.hi.x *= scale;
	}  // end if
	if( textureSize->y )
	{
		// retail re-reads the size here rather than reusing the cached pointer
		float scale = 1.0f / (float)theImage->getTextureSize()->y;
		uvCoords.lo.y *= scale;
		uvCoords.hi.y *= scale;
	}  // end if

	// store the uv coords
	theImage->setUV( &uvCoords );

	// compute the image size based on the coords we read and store
	ICoord2D imageSize;
	imageSize.x = right - left;
	imageSize.y = bottom - top;
	theImage->setImageSize( &imageSize );

}  // end parseImageCoord

//-------------------------------------------------------------------------------------------------
/** Parse the image status line */
//-------------------------------------------------------------------------------------------------
void Image::parseImageStatus( INI* ini, void *instance, void *store, const void* /*userData*/)
{	
	// use existing INI parsing for the bit strings
	INI::parseBitString32(ini, instance, store, imageStatusNames);

	//
	// if we are rotated 90 degrees clockwise we need to swap our width and height as
	// they were computed from the page location rect, which was for the rotated image
	// (see ImagePacker tool for more details)
	//
	unsigned int *theStatusBits = (unsigned int *)store;
	if( (*theStatusBits & IMAGE_STATUS_ROTATED_90_CLOCKWISE) != 0 )
	{
		Image *theImage = (Image *)instance;
		ICoord2D imageSize;

		imageSize.x = theImage->getImageHeight();  // note it's height not width
		imageSize.y = theImage->getImageWidth();   // note it's width not height
		theImage->setImageSize( &imageSize );

	}  // end if

}  // end parseImageStatus
