// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /EHsc /MD /DNDEBUG
// ?rva005D13E2@Rva005D13E2@@QAEXXZ @ 0x005D13E2, 201 bytes.
// Target evidence: PE RVA 0x005D13E2 begins with push ecx and returns at
// 0x005D14AA; 0x005D14AB begins the next body. The method counts the pointer
// range at +0x10..+0x14, forwards that count to 0x005EE250, and for each
// entry updates its name, ARGB color, mapped image, region count and unit
// count through the player-row APT wrappers. It finishes by setting row 0.
// Callee addresses and offsets come from BFME2 target instructions. The
// player-row wrapper and record views are structural inferences from the
// +4 delegate thunks and their rowed callees; the original host class name
// and higher-level method name are unknown, so this remains address-derived.

#include "ascii_string.h"
#include "unicode_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

struct RGBColor
{
	int getAsInt() const;
};

class Rva005EE250
{
public:
	void rva005EE250(int count);
};

class Rva005ED976
{
public:
	void rva005ED849(int index, int color);
	void rva005ED851(int index, int value);
	void rva005ED859(int index, int value);
	void rva005ED861(int row);
	void rva005ED986(int index, const UnicodeString &name);
	void rva005ED5BB(int index, const Image *image);
};

class Rva002E1001
{
public:
	int rva002E1001();
};

struct Rva002E0D02Arg;
int __cdecl Rva002E0D02Get(Rva002E0D02Arg *arg);

class Rva005D13E2
{
public:
	void rva005D13E2();

private:
	char m_pad00[0x0C];
	Rva005ED976 *m_rowView;
	char **m_entriesBegin;
	char **m_entriesEnd;
};

struct Rva005D13E2LoopTemps
{
	void *imageInfo;
	Rva005ED976 *currentView;
};

void Rva005D13E2::rva005D13E2()
{
	int count = (int)(m_entriesEnd - m_entriesBegin);
	reinterpret_cast<Rva005EE250 *>(m_rowView)->rva005EE250(count);

	for (int index = 0; index < count; ++index) {
		char *entry = m_entriesBegin[index];
		Rva005D13E2LoopTemps temps;
		temps.imageInfo = *(void **)(entry + 0x40);
		m_rowView->rva005ED986(index, *(UnicodeString *)(entry + 0x1C));

		int color = ((RGBColor *)(entry + 0x184))->getAsInt() | 0xFF000000;
		m_rowView->rva005ED849(index, color);

		temps.currentView = m_rowView;
		const AsciiString &imageName = *(AsciiString *)((char *)temps.imageInfo + 0x20);
		const Image *image = TheMappedImageCollection->findImageByName(imageName);
		temps.currentView->rva005ED5BB(index, image);

		temps.currentView = m_rowView;
		int regions = ((Rva002E1001 *)entry)->rva002E1001();
		temps.currentView->rva005ED851(index, regions);

		temps.currentView = m_rowView;
		int units = Rva002E0D02Get((Rva002E0D02Arg *)entry);
		temps.currentView->rva005ED859(index, units);
	}

	m_rowView->rva005ED861(0);
}
