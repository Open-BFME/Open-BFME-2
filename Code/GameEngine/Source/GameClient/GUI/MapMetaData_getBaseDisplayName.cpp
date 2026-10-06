// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x00300AEA, 404 bytes.
// MapMetaData::bfme_getBaseDisplayName, the lazy cached map.str base-name
// loader feeding bfme_getDisplayName. Ported from Open-BFME-1
// (Code/GameEngine/Source/GameClient/MapMetaData_getBaseDisplayName.cpp)
// with two BFME2 differences: the fallback translates the leaf then strips a
// trailing ".map" (endsWith plus four removeLastChar calls, 0x000376E0 pinned
// under the narrow-pin's wide twin), and the suffix format lives in the
// numbered wrapper. Layout measured from retail: display-name label +0x00,
// player count +0x20, file name +0x50, cached base name +0xF8.
// StringBase friends let the body call the base methods directly so no novel
// wrapper is emitted; every out-of-line copy this TU emits (default/copy/
// substring ctors, both dtors, str, getLength) is byte-identical to its
// string_base/unicode_string/ascii_string row and folds. TheGameText virtuals
// need no pins (slots reset +0x24, fetch +0x38, initMapStringFile +0x4C);
// TheGameText itself is declared extern like VersionUnicode.cpp does.

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
	UnicodeString bfme_getBaseDisplayName();
	UnicodeString rva00300D0E();

private:
	UnicodeString m_displayNameLabel;
	char m_pad04[0x20 - 0x04];
	int m_playerCount;
	char m_pad24[0x50 - 0x24];
	AsciiString m_fileName;
	char m_pad54[0xF8 - 0x54];
	UnicodeString m_cachedBaseDisplayName;
};

UnicodeString MapMetaData::bfme_getBaseDisplayName()
{
	if (m_cachedBaseDisplayName.getLength() == 0)
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
		if (*m_displayNameLabel.str() == '$')
		{
			label.translate(m_displayNameLabel.str() + 1);
		}
		else
		{
			label.translate(m_displayNameLabel);
		}

		bool exists = false;
		m_cachedBaseDisplayName.set(TheGameText->fetch(label, &exists));
		if (!exists)
		{
			if (slash && *m_displayNameLabel.str() == '$')
			{
				m_cachedBaseDisplayName.translate(slash + 1);
				if (((StringBase<WideChar> &)m_cachedBaseDisplayName).endsWith(L".map"))
				{
					for (int i = 4; i != 0; --i)
						((StringBase<WideChar> &)m_cachedBaseDisplayName).removeLastChar();
				}
			}
			else
			{
				m_cachedBaseDisplayName.set(m_displayNameLabel);
			}
		}

		TheGameText->reset();
	}

	return m_cachedBaseDisplayName;
}

UnicodeString MapMetaData::rva00300D0E()
{
	UnicodeString tmp;
	const char *slash = ((StringBase<char> &)m_fileName).reverseFind('\\');
	if (slash)
		tmp.translate(slash + 1);
	else
		tmp.translate(m_fileName);
	return tmp;
}
