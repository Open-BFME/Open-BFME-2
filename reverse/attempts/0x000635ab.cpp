// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /MD /DNDEBUG /Ireference/shims/moduledata
// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z @0x000635AB 77B
//
// BFME 2 W3DGhostObjectManager shroud-refresh sweep over m_usedModules.
// The class view, the field offsets and the compiler settings are the ones the
// sibling W3DGhostObjectScene.cpp already matches: m_localPlayer +0x04 on the
// manager base, m_usedModules +0x10, and on the node m_parentObject +0x0C,
// m_partitionData +0x7C, m_parentSnapshots[20] +0x80, m_nextSystem +0xE0.
//
// Per node: if the node has NO parent object, refresh its shroud for the local
// player through the rowed W3DGhostObject::getShroudStatus (0x00063508); when
// that refresh left the local player's snapshot slot clear, drop the node's
// partition data through the rowed scalar deleting destructor
// BfmeThingCDE::bfmeGoCDE (0x0073B220). The walk advances through the sbb/neg
// select, so a node pointing at itself terminates the loop.
//
// Two corrections over the banked attempt, both settled from the retail bytes:
// (1) the parent test is `cmp [esi+0x0c],0 / jne advance`, so the body runs
// when m_parentObject is NULL -- the bank had the polarity inverted; and
// (2) the signature is (Int, Int), not (void*, Int, Int): retail ends in
// `ret 8`. With both fixed the body is 75 bytes and every byte from 0x635AB
// through 0x635ED matches. The one remaining gap is retail's redundant
// `test esi,esi` at 0x635EE before the backedge `jne`, which MSVC folds into
// the `and` in every spelling tried here (do-while, goto-backedge, an explicit
// advance variable, and /O1 /O2 /Ob1 /Ob2).
#include "Common/Snapshot.h"

typedef int Int;
typedef bool Bool;

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID
};

class PartitionData
{
public:
	// The rowed scalar deleting destructor retail calls at 0x0073B220. It is
	// called through a direct thiscall, so it is modelled as a plain member.
	void bfmeGoCDE();
	ObjectShroudStatus getShroudedStatus( Int playerIndex );
};

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager();
	inline Int getLocalPlayerIndex( void ) { return m_localPlayer; }
protected:
	Int m_localPlayer;																					///< 0x04
	Bool m_lockGhostObjects;																		///< 0x08
	Bool m_saveLockGhostObjects;																///< 0x09
};

class Object;
class W3DRenderObjectSnapshot;

class W3DGhostObject
{
	friend class W3DGhostObjectManager;
public:
	void getShroudStatus( int playerIndex );
	char m_unrecovered00[ 0x0C ];
	Object *m_parentObject;																			///< 0x0C
	char m_unrecovered10[ 0x7C - 0x10 ];
	PartitionData *m_partitionData;																			///< 0x7C
	W3DRenderObjectSnapshot *m_parentSnapshots[ 20 ];						///< 0x80
	char m_unrecoveredD0[ 0xE0 - 0xD0 ];
	W3DGhostObject *m_nextSystem;																///< 0xE0
	W3DGhostObject *m_prevSystem;																///< 0xE4
};

class W3DGhostObjectManager : public GhostObjectManager
{
public:
	void rva000635AB( Int a, Int b );
protected:
	W3DGhostObject *m_freeModules;															///< 0x0C
	W3DGhostObject *m_usedModules;															///< 0x10
};

// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z
void W3DGhostObjectManager::rva000635AB( Int a, Int b )
{
	(void)a;
	(void)b;
	W3DGhostObject *mod = m_usedModules;
	if (!mod)
		return;
	do
	{
		// Retail preloads m_nextSystem before the parent test and re-reads it
		// after the call, so the shroud refresh sees an unmodified node.
		W3DGhostObject *next = mod->m_nextSystem;
		if (mod->m_parentObject == 0)
		{
			mod->getShroudStatus(m_localPlayer);
			if (!mod->m_parentSnapshots[m_localPlayer])
			{
				PartitionData *data = mod->m_partitionData;
				if (data)
					data->bfmeGoCDE();
			}
		}
		// The sbb/neg/and select: a node that is its own successor stops the
		// walk instead of spinning forever.
		mod = (mod != next) ? next : 0;
	} while (mod);
}
