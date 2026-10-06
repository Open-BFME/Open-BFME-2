// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x003009CD, 285 bytes.
// MapMetaData::getDescription, the lazy cached map.str text loader feeding
// bfme_getDescriptionFirstLine. Ported from Open-BFME-1
// (Code/GameEngine/Source/GameClient/MapMetaData_getBaseDisplayName.cpp,
// whose getDescription shares the base-loader skeleton minus the dollar
// branch and the .map strip). Description label +0x04, description cache
// +0xFC. The getDescription pin was placed with the first-line commit; no new
// pins here. Out-of-line copies fold with the string rows like the sibling TUs.

typedef unsigned short WideChar;

#include "ascii_string.h"
#include "unicode_string.h"

class UnicodeString;



class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void reset() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;
};

extern GameTextInterface *TheGameText;

class MapMetaData
{
public:
	UnicodeString getDescription();

private:
	UnicodeString m_displayNameLabel;
	UnicodeString m_descriptionLabel;
	char m_pad08[0x20 - 0x08];
	int m_playerCount;
	char m_pad24[0x50 - 0x24];
	AsciiString m_fileName;
	char m_pad54[0xFC - 0x54];
	UnicodeString m_cachedDescription;
};

UnicodeString MapMetaData::getDescription()
{
	if (m_cachedDescription.getLength() == 0)
	{
		const char *slash = ((StringBase<char> &)m_fileName).reverseFind('\\');
		if (slash)
		{
			AsciiString stringFileName(m_fileName, 0,
				(int)(slash - ((StringBase<char> &)m_fileName).str()) + 1);
			((StringBase<char> &)stringFileName).concat("map.str");
			TheGameText->initMapStringFile(stringFileName);
		}

		AsciiString label;
		label.translate(m_descriptionLabel);

		bool exists = false;
		m_cachedDescription.set(TheGameText->fetch(label, &exists));
		if (!exists)
			m_cachedDescription.set(m_descriptionLabel);

		TheGameText->reset();
	}

	return m_cachedDescription;
}
