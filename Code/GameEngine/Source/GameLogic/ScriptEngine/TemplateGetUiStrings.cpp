// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?getUiStrings@Template@@QBEHQAVAsciiString@@@Z, retail 0x003B276B, 56 bytes.
// Template::getUiStrings copies m_numUiStrings AsciiStrings from +0x18 to the
// out array and returns the count. Donor: BFME1 Scripts.cpp Template::getUiStrings
// (same loop; BFME2 moved count/array to +0x14/+0x18). Callers (tail-jmps):
// Condition::getUiStrings 0x003B39B2 and ScriptAction::getUiStrings 0x003B2843.
// Callee ??4AsciiString@@QAEAAV0@ABV0@@Z pinned at 0x000366F0.

#include "ascii_string.h"

class Template
{
public:
	int getUiStrings(AsciiString * const strings) const;
private:
	char _pad[0x14];
	int m_numUiStrings;
	AsciiString m_uiStrings[12];
};

int Template::getUiStrings(AsciiString * const strings) const
{
	int i;
	for (i = 0; i < m_numUiStrings; i++) {
		strings[i] = m_uiStrings[i];
	}
	return m_numUiStrings;
}
