// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva0020CDA2@ScriptEngine@@QAEXXZ, retail 0x0020CDA2..0x0020CE13 (113B).
//
// Builds a fresh ScriptAction of type 3 (VICTORY in the Zero Hour action
// enum) and runs it through ScriptEngine::executeActions with no script and
// the name "Cheat Key Victory": the twin of the rowed "Cheat Key Defeat"
// body 0x0020CE13 that follows it, byte for byte apart from the type and
// the literal (.rdata 0x007E3EA4). No direct caller or address reference
// exists in retail; the method name stays address-derived.
#include "ascii_string.h"

class ScriptAction
{
public:
	enum ScriptActionType
	{
		VICTORY = 3
	};

	ScriptAction(ScriptActionType type);

private:
	char m_storage[0x48];
};

class ScriptEngine
{
public:
	void rva0020CDA2();

protected:
	void executeActions(ScriptAction *pActionHead, void *a, void *b);
};

void ScriptEngine::rva0020CDA2()
{
	ScriptAction *action = new ScriptAction(ScriptAction::VICTORY);
	{
		AsciiString name("Cheat Key Victory");
		executeActions(action, 0, &name);
	}
}
