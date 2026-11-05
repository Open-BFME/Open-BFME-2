// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
//
// W3DDisplay screenshot saver pair (retail 0x00047BC0 + 0x00045127).
//  - ?rva00047BC0@W3DDisplay@@AAEXPADIIPBD@Z @0x00047BC0 324B, thiscall ret 0x10
//    (BFME 1 / Zero Hour W3DDisplay::saveScreenShot(image, width, height) with
//    an optional file name): without a name it walks "sshotNNNN.bmp" under the
//    picture path until FileSystem::doesFileExist says the name is free, flips
//    the 24-bit image vertically in place, then writes the bitmap.
//  - ?rva00045127@...@ @0x00045127 236B: CreateBMPFile. Retail passes the
//    width in ECX and the height in EAX with the path and image on the stack,
//    a private convention that appears only because the helper is a static in
//    the same unit as its caller; it writes through FileSystem::openFile
//    (access 0x4A) and File slots 4 (write) and 2 (close) instead of Win32
//    CreateFile/WriteFile.
// Evidence (target): strings 'sshot%.4d' (0xBC2A30) and '.bmp' (0xBC2A28);
// _mbscpy/_mbscat thunks 0x00629176/0x0062988C; GlobalData::getPicturePath
// 0x0023611A (rowed); FileSystem::doesFileExist 0x00600D7D and openFile
// 0x00600C34 (rowed); frame counter cell VA 0x00DB3BFC (function static of
// the original, initialised to 1). Donor (structure only): Zero Hour
// W3DDisplay.cpp CreateBMPFile / saveScreenShot as carried in BFME 1.
// Retail calls the _mbscpy/_mbscat thunks named above directly, while
// sprintf uses the CRT import. Keep that distinction in the real declarations.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdio.h>
#include <windows.h>
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/File.h"

#include "../../../../GameEngine/Include/Common/FileSystem.h"
extern FileSystem *TheFileSystem;

#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;


#pragma pack(push, 2)
struct BfmeBitmapFileHeader
{
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
};
#pragma pack(pop)

struct BfmeBitmapInfoHeader
{
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};

// ZH spelling: the info block is filled through a BITMAPINFO pointer and read
// back through a separate cast BITMAPINFOHEADER pointer; cl then reloads the
// header fields after each file-header store, as retail does.
struct BfmeRgbQuad { unsigned char b, g, r, x; };
struct BfmeBitmapInfo { BfmeBitmapInfoHeader bmiHeader; BfmeRgbQuad bmiColors[1]; };
static __declspec(noinline) void CreateBMPFile(const char *file, char *image, int width, int height)
{
	BfmeBitmapFileHeader hdr;
	BfmeBitmapInfoHeader *pbih;
	BfmeBitmapInfo *pbmi = (BfmeBitmapInfo *)LocalAlloc(0x40, sizeof(BfmeBitmapInfoHeader));
	pbmi->bmiHeader.biSize = sizeof(BfmeBitmapInfoHeader);
	pbmi->bmiHeader.biWidth = width;
	pbmi->bmiHeader.biHeight = height;
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biBitCount = 24;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 * pbmi->bmiHeader.biHeight * 24;
	pbmi->bmiHeader.biClrImportant = 0;
	pbih = (BfmeBitmapInfoHeader *)pbmi;
	char *lpBits = image;
	File *out = TheFileSystem->openFile(file, 0x4A, 0);
	if (out == NULL)
		return;
	hdr.bfType = 0x4D42;
	hdr.bfSize = (unsigned int)(sizeof(BfmeBitmapFileHeader) + pbih->biSize + pbih->biClrUsed * 4 + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (unsigned int)sizeof(BfmeBitmapFileHeader) + pbih->biSize + pbih->biClrUsed * 4;
	if (out->write(&hdr, sizeof(BfmeBitmapFileHeader)) < sizeof(BfmeBitmapFileHeader))
		return;
	if (out->write(pbih, sizeof(BfmeBitmapInfoHeader) + pbih->biClrUsed * 4) < sizeof(BfmeBitmapInfoHeader) + pbih->biClrUsed * 4)
		return;
	int cb = pbih->biSizeImage;
	char *hp = lpBits;
	if (out->write(hp, cb) < cb)
		return;
	out->close();
	LocalFree(pbmi);
}

class W3DDisplay
{
private:
	void rva00047BC0(char *image, unsigned int width, unsigned int height, const char *filename);
};

void W3DDisplay::rva00047BC0(char *image, unsigned int width, unsigned int height, const char *filename)
{
	// Zero Hour's function-local frame counter, initialised to 1 (VA 0x00DB3BFC).
	static int frame_number = 1;
	char leafname[256];
	char pathname[1024];

	bool done = false;
	do {
		if (filename != NULL) {
			_mbscpy((unsigned char *)leafname, (const unsigned char *)filename);
			done = true;
		} else {
			sprintf(leafname, "sshot%.4d", frame_number++);
		}
		_mbscat((unsigned char *)leafname, (const unsigned char *)".bmp");
		_mbscpy((unsigned char *)pathname, (const unsigned char *)TheWritableGlobalData->getPicturePath().str());
		_mbscat((unsigned char *)pathname, (const unsigned char *)leafname);
		if (!TheFileSystem->doesFileExist(pathname))
			done = true;
	} while (!done);

	char *ptr, *ptr1;
	char v, v1;

	for (unsigned int y = 0; y < (height >> 1); y++) {
		ptr = image + ((width * y) * 3);
		ptr1 = image + ((width * (height - 1)) * 3);
		ptr1 -= ((width * y) * 3);

		for (unsigned int x = 0; x < (width * 3); x++) {
			v = *ptr;
			v1 = *ptr1;
			*ptr = v1;
			*ptr1 = v;
			ptr++;
			ptr1++;
		}
	}

	CreateBMPFile(pathname, image, width, height);
}
