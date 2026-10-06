// ?cellCallback@Rva002ED01EInfo@@QAEHPAVPathfindCell@@0HH@Z
// partial score=0.85 date=2026-10-06
// Base: Code/GameEngine/Source/GameLogic/AI/PathfinderCellLineWalks.cpp @faa3c4dc70.
// REQUIRED base edits (revert-safe, additive):
//  1. PathfindCell: replace `char m_unreconstructed[0x10];` with
//     `char m_beforeTag[0x0c]; unsigned int m_tag0C;` (same size).
//  2. Replace `PATHFINDER_CELL_LINE_CALLBACK( Rva002ED01EInfo )` with:
//     struct Rva002ED01EInfo
//     {
//     	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
//     	void *m_00; Int m_04; Int m_08; Int m_0C; Int m_10;
//     	char m_pad14[0x3c - 0x14]; Int m_3C; char m_40[0x10]; Int m_50; Int m_54;
//     };
//  3. Append the code below at end of file. Flags stay // cl: /O1 /G7 /DNDEBUG /MD.
// OPEN (see re_attempts.log): R1 immediate-ret vs jmp-END; m50/m54 emission
// order; prev cmp-mem; tail regs. Pins NOT added (verify before adding):
// ?rva002EA658@Rva002EA658@@QAE_NHPAH0@Z @0x2EA658,
// ?rva002EA34A@Rva002EA34A@@QAE_NHPAH@Z @0x2EA34A.

struct Rva002EA658
{
	bool rva002EA658( Int a, Int *b, Int *c );
};

struct Rva002EA34A
{
	bool rva002EA34A( Int a, Int *b );
};

class Rva002E6DC4
{
public:
	bool rva002E6DC4( void *a_raw, void *b_raw );
};

bool Rva001E3679( Int tag );

// ?cellCallback@Rva002ED01EInfo@@QAEHPAVPathfindCell@@0HH@Z @0x002ED01E 174B.
Int Rva002ED01EInfo::cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY )
{
	m_08 = cellX;
	m_0C = cellY;
	unsigned int tag = ( currentCell->m_tag0C >> 4 ) & 0x3f;
	m_10 = tag;
	if ( previousCell != 0 ) {
		if ( ( (Rva002EA658 *)m_00 )->rva002EA658( m_04, &m_08, &m_50 ) )
			goto checkTag;
		else
			return 1;
	} else {
		if ( ( (Rva002EA34A *)m_00 )->rva002EA34A( m_04, &m_08 ) )
			goto checkTag;
		else
			return 1;
	}
checkTag:
	if ( m_3C != 0 )
		return 1;
	m_50 = cellX;
	m_54 = cellY;
	if ( previousCell == 0 )
		goto callWorker;
	unsigned int prevTagFull = previousCell->m_tag0C;
	unsigned int prevTag = ( prevTagFull >> 4 ) & 0x3f;
	unsigned char tagLo = (unsigned char)prevTagFull;
	if ( !Rva001E3679( prevTag ) )
		goto callWorker;
	if ( ( ( previousCell->m_tag0C >> 4 ) & 0x3f ) != prevTag )
		goto callWorker;
	if ( ( tagLo & 0xf ) != 0 )
		goto callWorker;
	return 0;
callWorker:
	return !( (Rva002E6DC4 *)m_00 )->rva002E6DC4( &m_40, currentCell );
}
