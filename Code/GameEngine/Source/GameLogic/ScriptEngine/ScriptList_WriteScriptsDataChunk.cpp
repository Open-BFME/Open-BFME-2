// cl: /DNDEBUG /MD /EHsc
//
// ?WriteScriptListDataChunk@ScriptList@@QAEXAAVDataChunkOutput@@@Z,
// retail 0x003B73C5, 49 bytes, plus
// ?WriteScriptsDataChunk@ScriptList@@SAXAAVDataChunkOutput@@QAPAV1@H@Z,
// retail 0x003B73F6, 82 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp,
// ScriptList::WriteScriptsDataChunk / WriteScriptListDataChunk, following the
// Zero Hour shape): the outer writer opens the PlayerScriptsList chunk and one
// ScriptList chunk per list, delegating each list to the member writer; the
// member writer emits the script chunk before the group chunk (the Zero Hour
// order, m_firstScript at +0x08 after m_firstGroup at +0x04). The per-chunk writers
// are free functions resolving through the 0x3B5994/0x3B6975 pins, the chunk
// open through the matched 0x307C76 row, and the chunk close through the
// 0x306C88 pin. Retail pushes version 1 for both chunks.

typedef int Int;

enum
{
	K_SCRIPT_LIST_DATA_VERSION_1 = 1,
	K_SCRIPTS_DATA_VERSION_1 = 1
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void closeDataChunk(void);
};

class Script;
class ScriptGroup;

class ScriptList
{
public:
	static void WriteScriptsDataChunk(DataChunkOutput &chunkWriter, ScriptList *scriptLists[], Int numLists);
	void WriteScriptListDataChunk(DataChunkOutput &chunkWriter);

private:
	unsigned char m_pad[4];
	ScriptGroup *m_firstGroup; // +0x04
	Script *m_firstScript; // +0x08
};

void WriteGroupDataChunk(DataChunkOutput &chunkWriter, ScriptList *scriptList, ScriptGroup *scriptGroup);
void WriteScriptDataChunk(DataChunkOutput &chunkWriter, ScriptList *scriptList, Script *script);

// ?WriteScriptListDataChunk@ScriptList@@QAEXAAVDataChunkOutput@@@Z
void ScriptList::WriteScriptListDataChunk(DataChunkOutput &chunkWriter)
{
	if (m_firstScript)
		WriteScriptDataChunk(chunkWriter, this, m_firstScript);
	if (m_firstGroup)
		WriteGroupDataChunk(chunkWriter, this, m_firstGroup);
}

// ?WriteScriptsDataChunk@ScriptList@@SAXAAVDataChunkOutput@@QAPAV1@H@Z
void ScriptList::WriteScriptsDataChunk(DataChunkOutput &chunkWriter, ScriptList *scriptLists[], Int numLists)
{
	/**********SCRIPTS DATA ***********************/
	chunkWriter.openDataChunk("PlayerScriptsList", K_SCRIPTS_DATA_VERSION_1);
	Int i;
	for (i = 0; i < numLists; i++) {
		chunkWriter.openDataChunk("ScriptList", K_SCRIPT_LIST_DATA_VERSION_1);

		if (scriptLists[i])
			scriptLists[i]->WriteScriptListDataChunk(chunkWriter);

		chunkWriter.closeDataChunk();
	}
	chunkWriter.closeDataChunk();
}
