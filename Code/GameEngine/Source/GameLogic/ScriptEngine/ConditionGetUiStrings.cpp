// cl: /DNDEBUG /MD
//
// ?getUiStrings@Condition@@QAEHQAVAsciiString@@@Z, retail 0x003B39B2, 21 bytes.
// Thin wrapper: fetch the ConditionTemplate for m_conditionType (+4) via the
// rowed ScriptEngine::getConditionTemplate, then tail-jump to the rowed
// Template::getUiStrings. Donor: BFME1 Scripts.cpp Condition::getUiStrings.
// (Scripts.cpp declares ScriptEngine::getConditionTemplate virtual, which emits
// a virtual call here; retail calls it directly, hence this TU with a
// non-virtual declaration.)

class AsciiString;

class Template
{
public:
	int getUiStrings(AsciiString * const strings) const;
};

class ConditionTemplate : public Template
{
};

class ScriptEngine
{
public:
	const ConditionTemplate *getConditionTemplate(int type);
};
extern ScriptEngine *TheScriptEngine;

class Condition
{
public:
	int getUiStrings(AsciiString * const strings);
private:
	char _pad[4];
	int m_conditionType;
};

int Condition::getUiStrings(AsciiString * const strings)
{
	const ConditionTemplate *pTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	return pTemplate->getUiStrings(strings);
}
