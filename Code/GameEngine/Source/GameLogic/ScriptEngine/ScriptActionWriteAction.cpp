// cl: /O1 /DNDEBUG /MD
//
// ?WriteActionDataChunk@@YAXPADAAVDataChunkOutput@@PAVScriptAction@@@Z,
// retail 0x003B3DFF, 169 bytes. Dedicated TU.
//
// Unified BFME2 action writer: Zero Hour keeps separate
// ScriptAction::WriteActionDataChunk / WriteActionFalseDataChunk statics,
// while retail takes the chunk name as the first parameter and the script
// writer (0x3B5994) passes "ScriptAction" or "ScriptActionFalse" for the two
// action lists. Content otherwise follows the BFME1 donor
// (ScriptAction::WriteActionDataChunk): v3 chunk, action type, template key
// or NAMEKEY("Bogus"), parm count, per-parm WriteParameter calls, a trailing
// tail byte, close, next. The template key lives at ActionTemplate+0x10 and
// the tail byte at ScriptAction+0x41 (both retail-measured). All callees are
// matched rows (openDataChunk, writeInt folded with writeReal, the landed
// getActionTemplate, nameToKey, writeNameKey, WriteParameter, closeDataChunk)
// plus DIR32 globals filled by the gate, so no pins are needed.

typedef int Int;
typedef unsigned char Byte;
typedef unsigned char Bool;

enum NameKeyType
{
	NK_NONE = 0
};

class AsciiString;

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void writeInt(Int value);
	void writeNameKey(NameKeyType key);
	void closeDataChunk(void);
};

class ActionTemplate
{
public:
	Byte m_pad[0x10];
	NameKeyType m_internalNameKey; // +0x10
};

class ScriptEngine
{
public:
	const ActionTemplate *getActionTemplate(Int actionType);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

class Parameter
{
public:
	void WriteParameter(DataChunkOutput &chunkWriter);
};

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	virtual ~ScriptAction();

	Int m_actionType; // +0x04
	Int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
	ScriptAction *m_nextAction; // +0x3C
	Bool m_hasWarnings; // +0x40
	Byte m_tailByte; // +0x41
};

// ?WriteActionDataChunk@@YAXPADAAVDataChunkOutput@@PAVScriptAction@@@Z
void WriteActionDataChunk(char *chunkName, DataChunkOutput &chunkWriter, ScriptAction *action)
{
	for (ScriptAction *scriptAction = action; scriptAction; scriptAction = scriptAction->m_nextAction) {
		chunkWriter.openDataChunk(chunkName, 3);
		chunkWriter.writeInt(scriptAction->m_actionType);
		const ActionTemplate *actionTemplate = TheScriptEngine->getActionTemplate(scriptAction->m_actionType);
		if (actionTemplate)
			chunkWriter.writeNameKey(actionTemplate->m_internalNameKey);
		else
			chunkWriter.writeNameKey(TheNameKeyGenerator->nameToKey("Bogus"));
		chunkWriter.writeInt(scriptAction->m_numParms);
		Int i;
		for (i = 0; i < scriptAction->m_numParms; i++) {
			scriptAction->m_parms[i]->WriteParameter(chunkWriter);
		}
		chunkWriter.writeInt(scriptAction->m_tailByte);
		chunkWriter.closeDataChunk();
	}
}
