// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's create-a-hero screen map render callback, bound by the string
// "AptCreateAHero::DrawMapComponent" (WorldBuilder's matching body sits at
// 0x01454570 there). It needs an EH frame, which the screen's other
// callbacks in AptCreateAHeroCallbacks.cpp must not get, so it lives here.

// The picture name's scratch vector frees through the C++-linkage free at
// 0x00030830; that declaration is what makes the caller emit the unwind state
// store retail carries before the call.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"
#include "../../../../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
	int x, y;
};

// The shell's +0x5D flag is cleared while the map component draws.
class Shell
{
public:
	unsigned char m_pad00[0x5D];
	bool m_5d; // +0x5D
};
extern Shell *TheShell;

// TheGlobalData: the +0x62 flag gates the shadow manager's calls; 0x0023611A
// returns the pictures folder.
class GlobalData
{
public:
	AsciiString getPicturePath() const;

	unsigned char m_pad00[0x62];
	bool m_62; // +0x62
};
extern GlobalData *TheWritableGlobalData;

// The manager at 0x00DE1FF8 (W3DShadowManagerReAcquire.cpp's view).
class Rva0007DA23ResourceManager
{
public:
	void rva0007C18E();
	void rva0007B6F3();
};
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;


// TheDisplay: vslot 39 draws the map view into a rectangle, vslot 83 saves
// a screenshot to the named file; +0x141 is a flag.
class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38();
	virtual void drawMapView(const Coord2D *origin, const Coord2D *extent); // vslot 39
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82();
	virtual void takeScreenShot(const char *filename); // vslot 83

	unsigned char m_pad04[0x141 - 4];
	bool m_141; // +0x141
};
extern Display *TheDisplay;

// The object at 0x00DFDC14: rowed setCoords, then its vslot 12.
class Rva001DBAA4
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();

	void setCoords(const ICoord2D *c1, const ICoord2D *c2);
};
extern Rva001DBAA4 *theBfmeDfdc14;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0;
	virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual void slot16() = 0;
	virtual const UnicodeString *slot44(const char *label, bool *exists) = 0; // vslot 0x44
};
extern GameTextInterface *TheGameText;

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class GameWindow;
GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body, void (*okCallback)());

struct SYSTEMTIME
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};
extern "C" __declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *st);
extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

// 0x002DBFAD formats the date, 0x002DC081 the time (Rva002DC081Format.cpp).
UnicodeString Rva002DC081(SYSTEMTIME date, int flag);
UnicodeString Rva002DBFAD(SYSTEMTIME date);
bool GadgetTextEntryValidateCharacter(unsigned short character, signed char flags);

// The wide string-concatenation nodes (WinMainPairUnicode.cpp's (pointer,
// length) reference). The empty constructors keep every node non-POD, so
// each operator+ returns through a hidden slot as retail shows.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *initWide(const unsigned short *src);

	const char *m_ptr;
	int m_len;
};

// wide text + string
struct Rva00513B27Concat
{
	Rva00513B27Concat() {}

	Rva000B3F84Pair m_left;
	const UnicodeString *m_right;
};

// (wide text + string) + wide text; built by 0x00513B5B.
struct Rva00513B5BConcat
{
	Rva00513B5BConcat() {}

	Rva00513B27Concat m_left;
	Rva000B3F84Pair m_right;
};

// ((wide text + string) + wide text) + string; built by 0x0059B036 and
// turned into a UnicodeString by 0x00513E6F.
struct Rva0059B036Concat
{
	Rva0059B036Concat() {}
	operator UnicodeString();

	Rva00513B5BConcat m_left;
	const UnicodeString *m_right;
};

Rva00513B5BConcat operator+(const Rva00513B27Concat &left, const unsigned short *right);
Rva0059B036Concat operator+(const Rva00513B5BConcat &left, const UnicodeString &right);

// Retail 0x00513B27, 52 bytes.
Rva00513B27Concat operator+(const unsigned short *left, const UnicodeString &right)
{
	Rva000B3F84Pair wide;
	wide.initWide(left);
	Rva00513B27Concat result;
	result.m_left = wide;
	result.m_right = &right;
	return result;
}

// Retail 0x00513ED1, 415 bytes: the picture file name, the hero's name
// stamped with the local date and time, every character a file name cannot
// take (the text-entry filter's flag 8) replaced by '-'.
UnicodeString Rva00513ED1(const UnicodeString &name)
{
	UnicodeString result(name);
	SYSTEMTIME st;
	GetLocalTime(&st);
	UnicodeString stamp = L" " + Rva002DBFAD(st) + L" " + Rva002DC081(st, 1);
	result.concat(stamp);
	int len = result.getLength();
	_STL::vector<short> buf(len + 1);
	unsigned short *p = (unsigned short *)&buf[0];
	memcpy(&buf[0], result.str(), (len + 1) * sizeof(unsigned short));
	for (; *p; ++p)
	{
		if (!GadgetTextEntryValidateCharacter(*p, 8))
			*p = L'-';
	}
	result.set((unsigned short *)&buf[0]);
	return result;
}

class AptCreateAHero
{
public:
	void DrawMapComponent(const Coord2D *origin, const Coord2D *extent, void *unused3, void *unused4);

private:
	unsigned char m_pad000[0x274];
	void *m_274; // +0x274, the Apt movie told "OnGameTookPicture"
	unsigned char m_pad278[0x284 - 0x278];
	UnicodeString m_heroName; // +0x284
	unsigned char m_pad288[0x42F - 0x288];
	bool m_takePicture; // +0x42F
};

// Retail 0x00514070, 576 bytes: "AptCreateAHero::DrawMapComponent" draws the
// hero preview map into the component's rectangle with the shell's +0x5D
// flag down; once OnTakePicture asked, saves the frame as a picture named
// for the hero and reports where it went.
void AptCreateAHero::DrawMapComponent(const Coord2D *origin, const Coord2D *extent, void *unused3, void *unused4)
{
	TheShell->m_5d = false;
	if (Rva00DE1FF8Manager && TheWritableGlobalData->m_62)
		Rva00DE1FF8Manager->rva0007C18E();
	TheDisplay->drawMapView(origin, extent);
	if (Rva00DE1FF8Manager && TheWritableGlobalData->m_62)
		Rva00DE1FF8Manager->rva0007B6F3();
	if (TheDisplay->m_141)
	{
		ICoord2D lo;
		ICoord2D hi;
		lo.x = (int)origin->x;
		lo.y = (int)origin->y;
		hi.x = (int)extent->x;
		hi.y = (int)extent->y;
		theBfmeDfdc14->setCoords(&lo, &hi);
		theBfmeDfdc14->v12();
	}
	TheShell->m_5d = true;

	if (m_takePicture)
	{
		m_takePicture = false;
		UnicodeString file = Rva00513ED1(m_heroName);
		AsciiString fileName(file);
		TheDisplay->takeScreenShot(fileName.str());
		void *movie = m_274;
		Rva0043DB23(TheRva00222A8BTarget, movie, "OnGameTookPicture");
		UnicodeString path(TheWritableGlobalData->getPicturePath());
		path.concat(file);
		UnicodeString title;
		title.format(TheGameText->slot44("GUI:OnPictureTakenTitle", 0), m_heroName.str());
		UnicodeString message;
		message.format(TheGameText->slot44("GUI:OnPictureTaken", 0), path.str());
		MessageBoxOk(title, message, 0);
	}
}
