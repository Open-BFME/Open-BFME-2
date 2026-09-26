// cl: /O1 /DNDEBUG /MD
//
// ?getParameterType@Template@@QBE?AW4ParameterType@Parameter@@H@Z, retail 0x003B27A3 (24 bytes).
// Template::getParameterType shared by ActionTemplate and ConditionTemplate
// (both derive from Template in ZH Scripts.h; BFME2 callers pass both types:
// 0x003B4343 via getActionTemplate, 0x003B4A94/0x003B6D92 via getConditionTemplate).
// Layout from ScriptEngine_initTemplateNameKeys.cpp (m_numParameters +0x48,
// m_parameters +0x4C, sizeof 0x80). Donor ZH Scripts.cpp Template::getParameterType
// with DEBUG_CRASH compiled out (/DNDEBUG) returns Parameter::INT (0) out of range,
// matching retail xor eax,eax.

class Parameter
{
public:
	enum ParameterType
	{
		INT = 0
	};
};

class Template
{
public:
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
