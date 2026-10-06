// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/scriptenginevtable /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ?getUiText@ScriptAction@@QAE?AVAsciiString@@XZ retail 0x003B54DC 285 bytes.
// BFME2 ScriptAction::getUiText via ZH Scripts.cpp donor with BFME2 deltas:
// initial empty set plus hasWarnings concat plus tailByte disabled concat.
// Layout from ScriptActionWriteAction.cpp: hasWarnings +0x40 and tailByte +0x41.
// Callees rowed getUiStrings 0x3B2843 and pinned param getUiText 0x3B4B1D.
// Callers at 0x0020CBFF and 0x003B6BBA and 0x003B6C0E.

#include "ascii_string.h"


class Parameter
{
public:
	AsciiString getUiText() const;
};

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	AsciiString getUiText();
	int getUiStrings(AsciiString * const strings);
private:
	void *m_vtable;
	int m_actionType;
	int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	void *m_nextAction;
	unsigned char m_hasWarnings;
	unsigned char m_tailByte;
	char m_pad[2];
};

static __forceinline void appendUiText(AsciiString &dst, const AsciiString &src)
{
	((StringBase<char> *)&dst)->concat(*(const StringBase<char> *)&src);
}

AsciiString ScriptAction::getUiText()
{
	AsciiString uiText;
	AsciiString strings[MAX_PARMS];
	int numStrings = getUiStrings(strings);
	int i;

	((StringBase<char> *)&uiText)->set("");
	if (m_hasWarnings) {
		((StringBase<char> *)&uiText)->concat("[???]");
	}
	if (m_tailByte == 0) {
		((StringBase<char> *)&uiText)->concat("(DISABLED) ");
	}

	for (i = 0; i < MAX_PARMS; i++) {
		if (i < numStrings) {
			((StringBase<char> *)&uiText)->concat(*(const StringBase<char> *)&strings[i]);
		}
		if (i < m_numParms) {
			appendUiText(uiText, m_parms[i]->getUiText());
		}
	}

	return uiText;
}
