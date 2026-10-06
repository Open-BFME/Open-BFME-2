// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?enableGenericScript@Team@@QAE_NABVAsciiString@@0_N@Z, retail 0x003A1F65
// (269 bytes).
// Identity (target): WorldBuilder's debug Team.cpp:4472 body
// Team::enableGenericScript has retail's callee order: the
// TeamPrototype::getGenericScript (0x0039EC1E) probe, the "group/script"
// name built from the copy constructor and two concats, then per slot
// getGenericScript with the out string and three compares.
// Donor (Zero Hour Team): per-slot m_shouldAttemptGenericScript flags, here
// at Team+0x70 (the constructor sets the 32 of them). BFME 2 deltas
// (target): a slot matches when its group string (getGenericScript's second
// result) equals the group argument and its script name (prototype +0x244)
// equals the bare or the group-qualified name; the result says whether any
// slot changed.
#include "ascii_string.h"

class Script;

// Retail expands the one-character concat in place as StringBase::concat(text, 1).
inline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

enum { MAX_GENERIC_SCRIPTS = 32 };

class TeamPrototype
{
public:
	Script *getGenericScript(int scriptToRetrieve, AsciiString *outName);
	const AsciiString &getGenericScriptName(int i) const { return m_teamGenericScripts[i]; }

private:
	unsigned char m_pad000[0x244];
	AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS]; // +0x244
};

class Team
{
public:
	bool enableGenericScript(const AsciiString &scriptName, const AsciiString &groupName, bool enable);

private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
	unsigned char m_pad34[0x70 - 0x34];
	bool m_shouldAttemptGenericScript[MAX_GENERIC_SCRIPTS]; // +0x70
};

bool Team::enableGenericScript(const AsciiString &scriptName, const AsciiString &groupName, bool enable)
{
	if (m_proto == 0)
		return false;
	if (m_proto->getGenericScript(0, 0) == 0)
		return false;
	bool found = false;
	AsciiString fullName(groupName);
	concatChar(fullName, '/');
	fullName.concat(scriptName);
	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
	{
		const AsciiString &name = m_proto->getGenericScriptName(i);
		AsciiString group;
		Script *script = m_proto->getGenericScript(i, &group);
		bool match = false;
		if (script && groupName == group)
		{
			if (name == scriptName)
				match = true;
			if (name == fullName)
				match = true;
		}
		if (match)
		{
			m_shouldAttemptGenericScript[i] = enable;
			found = true;
		}
	}
	return found;
}
