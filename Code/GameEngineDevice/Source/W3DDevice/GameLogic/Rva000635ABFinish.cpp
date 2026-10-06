// cl: /MD /DNDEBUG /Ireference/shims/moduledata
// ?rva000635AB@Rva000635AB@@QAEXHH@Z @0x000635AB 77B
//
// BFME 2 W3DGhostObjectManager shroud-refresh sweep over m_usedModules. The
// class view, the field offsets and the compiler settings are the ones the
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
// The advance is spelled `if (mod != next) mod = next; else mod = 0;` under a
// `loop:` label with an explicit `if (mod) goto loop;` back edge. That goto form
// is what preserves retail's redundant `test esi,esi` at 0x635EE: the do/while
// spelling makes MSVC fold that test into the flags the `and esi,ebx` at 0x635EC
// already set, dropping the body to 75 bytes. Here the flags the `and` leaves are
// not the ones the back edge tests, so the test survives and the body is the
// full 77 bytes.
//
// The ledger name is QAEXHH, not the address-derived QAEXPAHH: retail ends in
// `ret 8`, and MSVC emits `ret 0xc` for a three-argument thiscall, so the
// pointer form is refuted by the epilogue itself.
//
// The +0x7C field is typed BfmeThingCDE rather than the sibling's PartitionData
// because retail loads it straight into ecx for a direct call to
// BfmeThingCDE::bfmeGoCDE (0x73B220).
typedef int Int;
typedef bool Bool;

class BfmeThingCDE
{
public:
	void bfmeGoCDE();
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
	friend class Rva000635AB;
protected:
	void getShroudStatus( int playerIndex );
public:
	char m_unrecovered00[ 0x0C ];
	Object *m_parentObject;																			///< 0x0C
	char m_unrecovered10[ 0x7C - 0x10 ];
	BfmeThingCDE *m_partitionData;															///< 0x7C
	W3DRenderObjectSnapshot *m_parentSnapshots[ 20 ];						///< 0x80
	char m_unrecoveredD0[ 0xE0 - 0xD0 ];
	W3DGhostObject *m_nextSystem;																///< 0xE0
	W3DGhostObject *m_prevSystem;																///< 0xE4
};

class Rva000635AB : public GhostObjectManager
{
public:
	void rva000635AB( Int a, Int b );
protected:
	W3DGhostObject *m_freeModules;															///< 0x0C
	W3DGhostObject *m_usedModules;															///< 0x10
};

// ?rva000635AB@Rva000635AB@@QAEXHH@Z
void Rva000635AB::rva000635AB( Int a, Int b )
{
	(void)a;
	(void)b;
	W3DGhostObject *mod = m_usedModules;
	if (!mod)
		return;
loop:
	{
		// Retail preloads m_nextSystem before the parent test and re-reads it
		// after the call, so the shroud refresh sees an unmodified node.
		W3DGhostObject *next = mod->m_nextSystem;
		if (mod->m_parentObject == 0)
		{
			mod->getShroudStatus(m_localPlayer);
			if (!mod->m_parentSnapshots[m_localPlayer])
			{
				BfmeThingCDE *data = mod->m_partitionData;
				if (data)
					data->bfmeGoCDE();
			}
		}
		// The sbb/neg/and select: a node that is its own successor stops the
		// walk instead of spinning forever.
		if (mod != next)
			mod = next;
		else
			mod = 0;
	}
	if (mod)
		goto loop;
}