// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Script::getUiText @0x003B6AB2..0x003B6C6F (445 bytes).
// Donor: ZH Scripts.cpp via BFME1 6583b3c1ff21db4a561285717028fdafc780b7db,
// Script_getUiText_Thunk.cpp. Clause heads +30/+34/+38, next links +3C,
// and Condition +4C/+4D tests are independently read from the target body.
// Native string literals identify the added disabled and negated displays.
// Target calls rowed Condition::getUiText @3B5BA4 and ScriptAction::getUiText
// @3B54DC; no parser or pool declaration is needed for this UI body.
#include "ascii_string.h"
typedef int Int;
class Condition {
public:
    AsciiString getUiText();
    Condition *getNext() const { return m_next; }
    char m_prefix[0x3C];
    Condition *m_next;
    char m_middle[0xC];
    bool m_flag4C;
    bool m_flag4D;
};
class OrCondition {
public:
    Condition *getFirstAndCondition() const { return m_first; }
    OrCondition *getNextOrCondition() const { return m_next; }
    void *m_vtable;
    OrCondition *m_next;
    Condition *m_first;
};
class ScriptAction {
public:
    AsciiString getUiText();
    ScriptAction *getNext() const { return m_next; }
    char m_prefix[0x3C];
    ScriptAction *m_next;
};
class Script {
public:
    AsciiString getUiText();
private:
    char m_prefix[0x30];
    OrCondition *m_condition;
    ScriptAction *m_action;
    ScriptAction *m_actionFalse;
};

static __forceinline void appendUiText(AsciiString &dst, const AsciiString &src)
{
	((StringBase<char> *)&dst)->concat(*(const StringBase<char> *)&src);
}

AsciiString Script::getUiText(void) 
{
	AsciiString uiText("*** IF ***\r\n");
	OrCondition *pOr = m_condition;
	Int count=0;

	while (pOr) {
		Condition *pCond = pOr->getFirstAndCondition();
		if (count>0) ((StringBase<char> *)&uiText)->concat("  *** OR ***\r\n");
		count = 0;
		while (pCond) {
			if (count>0) {
				((StringBase<char> *)&uiText)->concat("    *AND* ");
			} else {
				((StringBase<char> *)&uiText)->concat("    ");
			}
			if (!pCond->m_flag4C) ((StringBase<char> *)&uiText)->concat(" (DISABLED) ");
			if (pCond->m_flag4D) ((StringBase<char> *)&uiText)->concat(" NOT ");
			appendUiText(uiText, pCond->getUiText());
			((StringBase<char> *)&uiText)->concat("\r\n");
			pCond = pCond->getNext();
			count++;
		}
		pOr = pOr->getNextOrCondition();
	}
	((StringBase<char> *)&uiText)->concat("*** THEN ***\r\n");
	ScriptAction *pAction = m_action;
	while (pAction) {
		((StringBase<char> *)&uiText)->concat("  ");
		appendUiText(uiText, pAction->getUiText());
		((StringBase<char> *)&uiText)->concat("\r\n");
		pAction = pAction->getNext();
	}
	pAction = m_actionFalse;
	if (pAction) {
		((StringBase<char> *)&uiText)->concat("*** ELSE ***\r\n");
		while (pAction) {
			((StringBase<char> *)&uiText)->concat("  ");
			appendUiText(uiText, pAction->getUiText());
			((StringBase<char> *)&uiText)->concat("\r\n");
			pAction = pAction->getNext();
		}
	}
	return uiText;
}
