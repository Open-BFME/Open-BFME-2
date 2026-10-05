// cl: /O1 /EHsc /DNDEBUG /MD
//
// FontLibrary font-list maintenance, Zero Hour GameFont.cpp (BFME 1 donor
// game/GameEngine/Source/GameClient/GUI/GameFont.cpp, same bodies):
//
//   ?unlinkFont@FontLibrary@@IAEXPAVGameFont@@@Z   retail 0x002173FA, 79 bytes
//   ?deleteAllFonts@FontLibrary@@IAEXXZ            retail 0x00217449, 53 bytes
//   ??1FontLibrary@@UAE@XZ                         retail 0x00218415, 83 bytes
//
// Target evidence: the destructor re-stores FontLibrary's vtable 0x00BE5AD0
// and is the callee of the rowed ??_GFontLibrary 0x002189A9; it calls
// 0x00217449 (the delete-all loop over m_fontList at +0x0C), then the two
// map members' destructors (+0x20 then +0x14, both rowed) and the pinned
// SubsystemInterface base destructor 0x001B4E74. 0x00217449 calls
// 0x002173FA with each list head, releases it through FontLibrary vtable
// slot 15 (+0x3C; the donor's releaseFontData) and frees it through the
// BFME 2 deleteInstance shape (virtual slot 0 with 0, then operator
// delete), as WeaponStore's temp-weapon bodies do. 0x002173FA is the Zero
// Hour unlink: GameFont::next at +4, m_count at +0x10.
// Layout (+0x0C list, +0x10 count, maps at +0x14/+0x20) matches the rowed
// FontLibrary ctor 0x00218942.

class GameFont
{
public:
	virtual void *deleteInstance(int flags);

	GameFont *next; // +0x04
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	unsigned char m_bfmeBasePad[8];
};

// The two map members, under the names their rowed destructors carry.
class Rva00217A02
{
public:
	~Rva00217A02();
private:
	unsigned char m_pad[0x0C];
};

class Rva00217A37
{
public:
	~Rva00217A37();
private:
	unsigned char m_pad[0x0C];
};

class FontLibrary : public SubsystemInterface
{
public:
	virtual ~FontLibrary();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void releaseFontData(GameFont *font) = 0; // +0x3C

protected:
	void unlinkFont(GameFont *font);
	void deleteAllFonts();

	GameFont *m_fontList; // +0x0C
	int m_count; // +0x10
	Rva00217A02 m_table1; // +0x14
	Rva00217A37 m_table2; // +0x20
};

void FontLibrary::unlinkFont(GameFont *font)
{
	GameFont *other = 0;

	// sanity
	if (font == 0)
		return;

	// sanity check and make sure this font is actually in this library
	for (other = m_fontList; other; other = other->next)
		if (other == font)
			break;
	if (other == 0)
		return;

	// scan for the font pointing to the one we're going to unlink
	for (other = m_fontList; other; other = other->next)
		if (other->next == font)
			break;

	// if nothing was found this was at the head of the list, otherwise
	// remove from chain
	if (other == 0)
		m_fontList = font->next;
	else
		other->next = font->next;

	// clean up this font we just unlinked just to be cool!
	font->next = 0;

	// we now have one less font on the list
	m_count--;
}

void FontLibrary::deleteAllFonts()
{
	GameFont *font;

	// release all the fonts
	while (m_fontList)
	{
		// get temp pointer to this font
		font = m_fontList;

		// remove font from the list, this will change m_fontList
		unlinkFont(font);

		// release font data
		releaseFontData(font);

		// delete the font list element
		::operator delete(font != 0 ? font->deleteInstance(0) : 0);
	}
}

FontLibrary::~FontLibrary()
{
	deleteAllFonts();
}
