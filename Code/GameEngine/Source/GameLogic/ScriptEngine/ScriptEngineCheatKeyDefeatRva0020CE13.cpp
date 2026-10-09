// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva0020CE13@ScriptEngine@@QAEXXZ, retail 0x0020CE13..0x0020CE84 (113B).
//
// Builds a fresh ScriptAction of type 4 (DEFEAT in the Zero Hour action
// enum) and runs it through ScriptEngine::executeActions with no script and
// the name "Cheat Key Defeat".
//
// Identity (target): the only reference to the literal "Cheat Key Defeat"
// (.rdata 0x007E3EB8) is this body (reverse/data_xrefs.tsv). WorldBuilder twin
// 0xB46380 (strings lead score 1.0) has the same shape: operator new(0x48)
// 0x0002FDA0 then ScriptAction::ScriptAction(4) 0x003B5413 then the
// AsciiString literal ctor 0x00037BA0 then ScriptEngine::executeActions
// 0x0020C5C7 (this in ecx) then the AsciiString release 0x00036410. No direct
// caller or address reference exists in retail; the method name stays
// address-derived.
#include "ascii_string.h"

class ScriptAction
{
public:
	enum ScriptActionType
	{
		DEFEAT = 4
	};

	ScriptAction(ScriptActionType type);

private:
	char m_storage[0x48];
};

class ScriptEngine
{
public:
	void rva0020CE13();

protected:
	void executeActions(ScriptAction *pActionHead, void *a, void *b);
};

void ScriptEngine::rva0020CE13()
{
	ScriptAction *action = new ScriptAction(ScriptAction::DEFEAT);
	{
		AsciiString name("Cheat Key Defeat");
		executeActions(action, 0, &name);
	}
}
