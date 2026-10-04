// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport

// AIPlayer::removeAll_TeamReadyQueue from the donor AIPlayer.cpp. Retail
// 0x004F0499 drains the queued list at this+0x08: it reloads the head each
// iteration, calls the out-of-line unlink helper at 0x004F0479 with ecx = this
// and the node as argument, then invokes the callback. The unlink helper has no
// proven name, so it is pinned under the address-derived rva004F0479. Only this
// body is emitted here; donor's sibling teardown bodies omitted.
// It is the second DLINK list (ZH declares TeamReadyQueue after
// TeamBuildQueue): removeAll_TeamBuildQueue is 0x004F042F, which drains
// this+0x04 through removeFrom_TeamBuildQueue 0x004F040F.
class TeamInQueue;
typedef void (*RemoveAllProc)( TeamInQueue *queueEntry );

class Rva004F0479
{
public:
	void rva004F0479( TeamInQueue *entry );
	void firstUnlink( TeamInQueue *entry );
};

class AIPlayer
{
public:
	void removeAll_TeamReadyQueue( RemoveAllProc removeCallback );
	void removeAll_TeamBuildQueue( RemoveAllProc removeCallback );
	void clearTeamsInQueue();

private:
	char m_pad[4];
	TeamInQueue *m_firstHead; // +04
	TeamInQueue *m_queueHead;	// +0x08
};

void AIPlayer::removeAll_TeamReadyQueue( RemoveAllProc removeCallback )
{
	while (m_queueHead)
	{
		TeamInQueue *tmp = m_queueHead;
		((Rva004F0479 *)this)->rva004F0479( tmp );
		if (removeCallback)
			(*removeCallback)( tmp );
	}
}

// Actual rowed/link-clean two-list wrappers in Rva004F040FList.cpp.
// These existing declaration-only receiver projections have the same
// RET4 node-pointer call ABI; no original owner or full layout is inferred.
#pragma comment(linker, "/alternatename:?rva004F0479@Rva004F0479@@QAEXPAVTeamInQueue@@@Z=?rva004F0479@Rva004F040F@@QAEXPAX@Z")
#pragma comment(linker, "/alternatename:?firstUnlink@Rva004F0479@@QAEXPAVTeamInQueue@@@Z=?rva004F040F@Rva004F040F@@QAEXPAX@Z")

void AIPlayer::removeAll_TeamBuildQueue(RemoveAllProc removeCallback)
{
    while (m_firstHead)
    {
        TeamInQueue *entry = m_firstHead;
        ((Rva004F0479 *)this)->firstUnlink(entry);
        if (removeCallback)
            (*removeCallback)(entry);
    }
}

// Whole BFME1 AIPlayerQueueTeardown.cpp and AIPlayer.cpp@1281192
// provide the two-list drain and deleteInstance protocol. Target first
// loop4F042F/39 independently proves receiver head+4 and callback RET4;
// sibling4F0499/39 proves head+8. The existing owner prefix is extended,
// not a new private copy. Reference supplies original labels; the target
// proves the offsets/calls/control flow, not an unrecovered full layout.

// Callback body is rowed at4F05C0/22 in the existing TeamInQueue
// predicate home. Native4F05D8 loads that exact address and both calls
// use this owner; first4F042F drains head+4, second4F0499 head+8.
void rva004F05C0(TeamInQueue *entry);

void AIPlayer::clearTeamsInQueue()
{
    removeAll_TeamBuildQueue(rva004F05C0);
    removeAll_TeamReadyQueue(rva004F05C0);
}
