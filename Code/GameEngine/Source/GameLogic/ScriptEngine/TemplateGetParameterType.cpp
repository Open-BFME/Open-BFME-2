// cl: /DNDEBUG /MD
//
// ?getParameterType@Template@@QBE?AW4ParameterType@Parameter@@H@Z, retail 0x003B27A3 (24 bytes).
// Template::getParameterType shared by ActionTemplate and ConditionTemplate
// (both derive from Template in ZH Scripts.h; BFME2 callers pass both types:
// 0x003B4343 via getActionTemplate, 0x003B4A94/0x003B6D92 via getConditionTemplate).
// Layout from ScriptEngine_initTemplateNameKeys.cpp (m_numParameters +0x48,
// m_parameters +0x4C, sizeof 0x80). Donor ZH Scripts.cpp Template::getParameterType
// with DEBUG_CRASH compiled out (/DNDEBUG) returns Parameter::INT (0) out of range,
// matching retail xor eax,eax.
//
// ?setActionType@ScriptAction@@QAEXW4ScriptActionType@1@@Z, retail 0x003B4343
// (137 bytes), and ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z,
// retail 0x003B4A94 (137 bytes). BFME1 donor Scripts.cpp
// ScriptAction::setActionType / Condition::setConditionType: free the old
// parameters, store the type, look the template up through the pinned
// ScriptEngine::getActionTemplate 0x00203926 / getConditionTemplate
// 0x00203941 and new one Parameter per template slot. Retail deltas: the
// delete inlines to the rowed releaseBuffer 0x00036410 plus ::operator delete
// (not a pooled deleteInstance), Parameter is 0x28 bytes with its AsciiString
// at +0x10. Retail keeps the new parameter pointer in edx across the
// getParameterType call, which cl only does when that callee was compiled
// earlier in the same TU, so all three bodies share this file as they shared
// retail's Scripts.cpp. ScriptAction caller 0x003B5413 is its ctor (vtable
// 0x0081F3FC).

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class AsciiString : public StringBase<char>
{
public:
	__forceinline ~AsciiString() {}
};

void __cdecl operator delete(void *ptr);

class Parameter
{
public:
	enum ParameterType
	{
		INT = 0
	};
	Parameter(ParameterType type, int val = 0) throw();
	__forceinline ~Parameter() {}
	void deleteInstance() { this->~Parameter(); ::operator delete(this); }
private:
	char m_head[0x10];
	AsciiString m_string; // +0x10
	char m_tail[0x28 - 0x14];
};

class Template
{
public:
	int getNumParameters() const throw() { return m_numParameters; }
	Parameter::ParameterType getParameterType(int ndx) const;

private:
	char m_pad[0x48];
	int m_numParameters; // +0x48
	Parameter::ParameterType m_parameters[12]; // +0x4C
};

Parameter::ParameterType Template::getParameterType(int ndx) const
{
	if (ndx >= 0 && ndx < m_numParameters) {
		return m_parameters[ndx];
	}
	return Parameter::INT;
}

class ActionTemplate : public Template
{
};

class ConditionTemplate : public Template
{
};

class ScriptEngine
{
public:
	const ActionTemplate *getActionTemplate(int type) throw();
	const ConditionTemplate *getConditionTemplate(int type) throw();
};
extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	enum ScriptActionType
	{
		NO_OP = 5
	};
	void setActionType(ScriptActionType type);
private:
	void *m_vtable; // +0x00
	int m_actionType; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
};

void ScriptAction::setActionType(ScriptActionType type)
{
	int i;
	for (i = 0; i < m_numParms; i++) {
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}
	m_actionType = type;
	const ActionTemplate *pTemplate = TheScriptEngine->getActionTemplate(m_actionType);
	m_numParms = pTemplate->getNumParameters();
	for (i = 0; i < m_numParms; i++) {
		m_parms[i] = new Parameter(pTemplate->getParameterType(i));
	}
}

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0
	};
	virtual ~Condition();
	void setConditionType(ConditionType type);
private:
	int m_conditionType; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
};

void Condition::setConditionType(ConditionType type)
{
	int i;
	for (i = 0; i < m_numParms; i++) {
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}
	m_conditionType = type;
	const ConditionTemplate *pTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	m_numParms = pTemplate->getNumParameters();
	for (i = 0; i < m_numParms; i++) {
		m_parms[i] = new Parameter(pTemplate->getParameterType(i));
	}
}
