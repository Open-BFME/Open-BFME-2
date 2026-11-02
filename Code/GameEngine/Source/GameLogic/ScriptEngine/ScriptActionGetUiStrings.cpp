// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?getUiStrings@ScriptAction@@QAEHQAVAsciiString@@@Z, retail 0x003B2843, 21 bytes.
// Thin wrapper: fetch the ActionTemplate for m_actionType (+4) via the rowed
// ScriptEngine::getActionTemplate, then tail-jump to the rowed
// Template::getUiStrings. Donor: BFME1 Scripts.cpp ScriptAction::getUiStrings.
// (Scripts.cpp declares ScriptEngine::getActionTemplate virtual, which emits
// a virtual call here; retail calls it directly, hence this TU with a
// non-virtual declaration.)

class AsciiString;

class Template
{
public:
	int getUiStrings(AsciiString * const strings) const;
};

class ActionTemplate : public Template
{
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptAction.h"

int ScriptAction::getUiStrings(AsciiString * const strings)
{
	const ActionTemplate *pTemplate = TheScriptEngine->getActionTemplate(m_actionType);
	return pTemplate->getUiStrings(strings);
}
