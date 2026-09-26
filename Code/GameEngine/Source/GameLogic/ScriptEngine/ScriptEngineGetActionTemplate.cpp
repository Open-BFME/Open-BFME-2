// cl: /O1 /DNDEBUG /MD
//
// ?getActionTemplate@ScriptEngine@@QAEPBVActionTemplate@@H@Z,
// retail 0x00203926, 27 bytes. Dedicated TU.
//
// Table lookup for the action writer (0x3B3DFF calls it with TheScriptEngine
// at 0xDFE16C and the action type): 0x257 entries of 128 bytes at this+0x20.
// Out-of-range indexes clamp to entry 0 (retail xors to zero then shares the
// shift-and-lea tail, so the caller-side null test is dead). Pure arithmetic
// with no callees. Name and Int parameter follow the Zero Hour ScriptEngine.h
// declaration; the table shape is retail-measured.

typedef int Int;
typedef unsigned char Byte;

class ActionTemplate
{
public:
	Byte m_pad[128];
};

class ScriptEngine
{
public:
	const ActionTemplate *getActionTemplate(Int actionType);

private:
	Byte m_pad0[0x20];
	ActionTemplate m_actionTemplates[0x257];
};

// ?getActionTemplate@ScriptEngine@@QAEPBVActionTemplate@@H@Z
const ActionTemplate *ScriptEngine::getActionTemplate(Int actionType)
{
	Int index = actionType;
	if (index < 0 || index >= 0x257)
		index = 0;
	return &m_actionTemplates[index];
}
