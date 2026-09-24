// cl: /O1 /EHsc
//
// ScriptEngine template finishing pass, retail 0x00204D87 (221 bytes).
// ScriptEngine::init calls it right after the action (0x003D46DB) and
// condition (0x003CF6B7) tables; the method name is descriptive, since no
// retail symbol names it.
//
// Donor: the loop pair that closes Zero Hour's ScriptEngine::init
// (GeneralsMD ScriptEngine.cpp), which tags every m_uiName with "[index]" and
// caches NAMEKEY(m_internalName). ZH runs conditions first; retail runs the
// 599 action records first, then the 202 condition records, and that is the
// order here. The record layout is the one the two table initializers
// establish from retail store offsets.

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
	void concat(const StringBase<T> &that);

private:
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	void format(const char *fmt, ...);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class Template
{
public:
	int         m_targetOnly00;    // +0x00
	AsciiString m_uiName;          // +0x04
	AsciiString m_uiName2;         // +0x08
	AsciiString m_internalName;    // +0x0C
	NameKeyType m_internalNameKey; // +0x10
	int         m_numUiStrings;    // +0x14
	AsciiString m_uiStrings[12];   // +0x18
	int         m_numParameters;   // +0x48
	int         m_parameters[12];  // +0x4C
	AsciiString m_helpText;        // +0x7C
};

class ScriptEngine
{
public:
	void initTemplateNameKeys();

private:
	char     m_pre[0x20];
	Template m_actionTemplates[599];    // +0x20
	Template m_conditionTemplates[202]; // +0x12BA0
};

void ScriptEngine::initTemplateNameKeys()
{
	int i;
	for (i = 0; i < 599; i++) {
		AsciiString str;
		str.format("[%d]", i);
		m_actionTemplates[i].m_uiName.concat(str);
		m_actionTemplates[i].m_internalNameKey = NAMEKEY(m_actionTemplates[i].m_internalName);
	}
	for (i = 0; i < 202; i++) {
		AsciiString str;
		str.format("[%d]", i);
		m_conditionTemplates[i].m_uiName.concat(str);
		m_conditionTemplates[i].m_internalNameKey = NAMEKEY(m_conditionTemplates[i].m_internalName);
	}
}
