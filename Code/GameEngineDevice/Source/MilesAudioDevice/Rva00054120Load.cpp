// cl: /Ireference/shims/bfme2_ascii /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?Rva00054120Load@@YGEPAVINI@@@Z @0x00054120 187B.
// Audio INI loader ORing six loadFile results via INI plus type.
// Evidence: unlock lane plus caller 0x00054222 plus literals Data\INI\Music.ini Data\INI\SoundEffects.ini Data\INI\Speech.ini Data\INI\Voice.ini Data\INI\AmbientStream.ini Data\INI\MiscAudio.ini plus precedent Rva0031B4D6Load OR pattern plus uchar pin for loadFile.
class Xfer;
enum INILoadType { INI_LOAD_OVERWRITE = 1 };
#include "ascii_string.h"
class INI
{
public:
	unsigned char loadFile(AsciiString s, INILoadType t, Xfer *x);
	char m_pad[8];
	INILoadType m_loadType;
};
unsigned char __stdcall Rva00054120Load(INI *ini)
{
	INILoadType t = ini->m_loadType;
	unsigned char b = ini->loadFile(AsciiString("Data\\INI\\Music.ini"), t, 0);
	b |= ini->loadFile(AsciiString("Data\\INI\\SoundEffects.ini"), t, 0);
	b |= ini->loadFile(AsciiString("Data\\INI\\Speech.ini"), t, 0);
	b |= ini->loadFile(AsciiString("Data\\INI\\Voice.ini"), t, 0);
	b |= ini->loadFile(AsciiString("Data\\INI\\AmbientStream.ini"), t, 0);
	b |= ini->loadFile(AsciiString("Data\\INI\\MiscAudio.ini"), t, 0);
	return b;
}
