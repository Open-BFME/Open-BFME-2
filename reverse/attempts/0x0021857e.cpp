// ?rva0021857E@FontLibrary@@QAEPAVGameFont@@PBVAsciiString@@M_NH@Z
// partial score=0.9869 date=2026-10-06
// ?rva0021857E@FontLibrary@@QAEPAVGameFont@@PBVAsciiString@@M_NH@Z
// partial score=0.95 date=2026-10-02
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Oy-
// stlport
//
// ?rva002186A6@FontLibrary@@QAEPAXPBVAsciiString@@M@Z, retail 0x002186A6, 69 bytes.
// FontLibrary record lookup called by pinned getFont at 0x002189E1.
// BFME1 donor (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/FontLibraryBFMERetail_getFont.cpp:
// bfmeFindRecord): AsciiString table find, int sizeKey from float, int-map find,
// default-record fallback, second-pointer return. BFME2 deltas (all retail-measured):
// table map lives at this+0x14, size-table records at table+0x0C with default at +0x08,
// float-to-int via cvttss2si (/arch:SSE). True member types are
// map<AsciiString,BfmeFontSizeTable*> and map<int,UnsignedInt>; they are spelled
// map<AsciiString,AsciiString> and map<int,int> so the emitted _M_find calls name
// the rowed workers at 0x001F8437 and 0x00388F63 (identical tree mechanics;
// LocomotorStoreFindTemplate precedent), the stored pointer recast from second.

#include <map>

typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

struct BfmeFontSizeTable
{
	unsigned char m_pad[8];
	void *m_defaultRecord;
	_STL::map<int, int> m_records;
};

extern "C" __declspec(dllimport) double __cdecl floor(double);

class GameFont
{
public:
	virtual ~GameFont();

	GameFont *next;          // +0x04
	AsciiString nameString;  // +0x08
	float pointSize;         // +0x0C
	int m_pad10;             // +0x10
	void *fontData;          // +0x14
	bool bold;               // +0x18
	int style;               // +0x1C
};

// The existing matched 0x002173E3 helper prepends a node through +0x04 and
// updates the FontLibrary list head/count at +0x0C/+0x10.
struct Rva002173E3Node
{
	int m_pad;
	Rva002173E3Node *m_next;
};

class Rva002173E3
{
public:
	void rva002173E3(Rva002173E3Node *node);
};

struct BfmeFontRecord
{
	unsigned char m_pad[8];
	bool m_flag08; // +0x08
};

class FontLibrary
{
public:
	void *rva002186A6(const AsciiString *name, float size);
	GameFont *getFont(const AsciiString *name, float size, bool bold);
	GameFont *rva0021857E(const AsciiString *name, float size, bool bold, int style);
	void rva00218468(AsciiString *name, float *size, bool *bold);

	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual bool loadFontData(GameFont *font); // +0x38
private:
	char m_pad04[0x0C - 4];
	GameFont *m_fontList; // +0x0C
	int m_fontCount; // +0x10, updated by the matched list-prepend helper
	_STL::map<AsciiString, AsciiString> m_tables;
};

void *FontLibrary::rva002186A6(const AsciiString *name, float size)
{
	_STL::map<AsciiString, AsciiString>::iterator table = m_tables.find(*name);
	if (table == m_tables.end())
		return 0;
	int sizeKey = (int)size;
	BfmeFontSizeTable *sizes = *(BfmeFontSizeTable **)&table->second;
	_STL::map<int, int>::iterator record = sizes->m_records.find(sizeKey);
	if (record == sizes->m_records.end())
		return sizes->m_defaultRecord;
	return (void *)record->second;
}

// ?getFont@FontLibrary@@QAEPAVGameFont@@PBVAsciiString@@M_N@Z, retail
// 0x002189E1 (66B). BFME 2's getFont looks the name/size record up (above)
// to choose a style, 4 when the record's +8 flag is set or no record exists,
// else 1, and hands everything to the styled lookup 0x0021857E (pinned).
GameFont *FontLibrary::getFont(const AsciiString *name, float size, bool bold)
{
	bool flag = true;
	BfmeFontRecord *record = (BfmeFontRecord *)rva002186A6(name, size);
	if (record)
		flag = record->m_flag08;
	return rva0021857E(name, size, bold, flag ? 4 : 1);
}

// ?rva0021857E@FontLibrary@@QAEPAVGameFont@@PBVAsciiString@@M_NH@Z, retail
// 0x0021857E (296B). Zero Hour's FontLibrary::getFont (find in the font list,
// else create, load the device data and link it) with BFME 2's style: the
// point size is snapped to a 1/style grid first, the name/size/bold triple is
// normalised by 0x00218468 (pinned), and fonts also match on style (+0x1C).
GameFont *FontLibrary::rva0021857E(const AsciiString *namePtr, float size, bool bold, int style)
{
	const float fstyle = (float)style;
	size = fstyle * size + 0.5f;
	size = (float)(floor(size) / fstyle);
	AsciiString name(*namePtr);
	rva00218468(&name, &size, &bold);

	GameFont *font;
	for (font = m_fontList; font; font = font->next)
	{
		if (font->pointSize == size && (bool)font->bold == bold && font->style == style &&
			font->nameString == name)
			return font;
	}

	font = new GameFont;
	if (0 == font)
		return 0;

	font->nameString = name;
	const bool newBold = bold;
	const float newSize = size;
	font->fontData = 0;
	font->pointSize = newSize;
	font->bold = newBold;
	font->style = style;

	if (loadFontData(font) == false)
	{
		::delete font;
		return 0;
	}

	((Rva002173E3 *)this)->rva002173E3((Rva002173E3Node *)font);
	return font;
}
