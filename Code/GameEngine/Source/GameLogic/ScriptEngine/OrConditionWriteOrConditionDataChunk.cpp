// cl: /O1 /EHsc

// Evidence: retail 0x003B4A3C (60 bytes) references the string literal
// "OrCondition", which ZH's Scripts.cpp uses only as the chunk name in
// OrCondition::WriteOrConditionDataChunk() (GameLogic/ScriptEngine/Scripts.cpp):
//   void OrCondition::WriteOrConditionDataChunk(DataChunkOutput &chunkWriter, OrCondition *pOrCondition)
//   {
//       while (pOrCondition) {
//           chunkWriter.openDataChunk("OrCondition", K_SCRIPT_OR_CONDITION_DATA_VERSION_1);
//           if (pOrCondition->m_firstAnd) Condition::WriteConditionDataChunk(chunkWriter, pOrCondition->m_firstAnd);
//           chunkWriter.closeDataChunk();
//           pOrCondition = pOrCondition->getNextOrCondition();
//       }
//   }
// Field offsets from the retail body: m_nextOr at OrCondition+4, m_firstAnd
// at +8 (OrCondition : MemoryPoolObject, vtable at +0, no other members).
// Callees openDataChunk/closeDataChunk (0x307C76 / 0x306C88) and
// Condition::WriteConditionDataChunk (0x3B428C) are pinned in
// reverse/symbols.csv from this call site's argument shapes (two literal
// pushes + this vs bare this; a Condition* + chunkWriter-ref pair matching
// Condition::WriteConditionDataChunk's declared signature).

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject() {}
};

class DataChunkOutput
{
public:
	void openDataChunk( char *name, unsigned int ver );
	void closeDataChunk( void );
};

class Condition
{
public:
	static void WriteConditionDataChunk( DataChunkOutput &chunkWriter, Condition *pCond );
};

enum { K_SCRIPT_OR_CONDITION_DATA_VERSION_1 = 1 };

class OrCondition : public MemoryPoolObject
{
public:
	OrCondition *getNextOrCondition( void ) { return m_nextOr; }
	static void WriteOrConditionDataChunk( DataChunkOutput &chunkWriter, OrCondition *pCondition );

protected:
	OrCondition *m_nextOr;
	Condition *m_firstAnd;
};

void OrCondition::WriteOrConditionDataChunk( DataChunkOutput &chunkWriter, OrCondition *pOrCondition )
{
	while ( pOrCondition ) {
		chunkWriter.openDataChunk( "OrCondition", K_SCRIPT_OR_CONDITION_DATA_VERSION_1 );
		if ( pOrCondition->m_firstAnd ) Condition::WriteConditionDataChunk( chunkWriter, pOrCondition->m_firstAnd );
		chunkWriter.closeDataChunk();
		pOrCondition = pOrCondition->getNextOrCondition();
	}
}
