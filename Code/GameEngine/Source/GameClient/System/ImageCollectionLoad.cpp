// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?load@ImageCollection@@QAEXH@Z @ 0x002D908D 249B
// Evidence: BFME1 donor ImageCollectionLoad.cpp trimmed (no userData block); same 5 strings TextureSize_%d HandCreated AptImages ParticleTextures TransitionImages in order; same loadDirectory TRUE OVERWRITE NULL 0; ret 4 single int arg; callers 0x0023A2F1; neighbours ImageBfmeSetTexture and stlport map.
#include "ascii_string.h"

extern "C" {
__declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
}

class Xfer;
enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	INI();
	~INI();
	bool loadDirectory(AsciiString dirpath, bool recursive, INILoadType loadType, Xfer *xfer, int extra);

private:
	char m_unported[0x87C];
};

class ImageCollection
{
public:
	void load(int textureSize);
};

void ImageCollection::load(int textureSize)
{
	char buffer[260];
	INI ini;
	sprintf(buffer, "Data\\INI\\MappedImages\\TextureSize_%d", textureSize);
	ini.loadDirectory(AsciiString(buffer), true, INI_LOAD_OVERWRITE, (Xfer *)0, 0);
	ini.loadDirectory("Data\\INI\\MappedImages\\HandCreated", true, INI_LOAD_OVERWRITE, (Xfer *)0, 0);
	ini.loadDirectory("Data\\INI\\MappedImages\\AptImages", true, INI_LOAD_OVERWRITE, (Xfer *)0, 0);
	ini.loadDirectory("Data\\INI\\MappedImages\\ParticleTextures", true, INI_LOAD_OVERWRITE, (Xfer *)0, 0);
	ini.loadDirectory("Data\\INI\\MappedImages\\TransitionImages", true, INI_LOAD_OVERWRITE, (Xfer *)0, 0);
}
