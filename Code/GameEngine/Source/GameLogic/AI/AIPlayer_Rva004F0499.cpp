// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport

// AIPlayer::removeAll_TeamBuildQueue from the donor AIPlayer.cpp. Retail
// 0x004F0499 drains the queued list at this+0x08: it reloads the head each
// iteration, calls the out-of-line unlink helper at 0x004F0479 with ecx = this
// and the node as argument, then invokes the callback. The unlink helper has no
// proven name, so it is pinned under the address-derived rva004F0479. Only this
// body is emitted here; donor's sibling teardown bodies omitted.
class TeamInQueue;
typedef void (*RemoveAllProc)( TeamInQueue *queueEntry );

class Rva004F0479
{
public:
	void rva004F0479( TeamInQueue *entry );
};

class AIPlayer
{
public:
	void removeAll_TeamBuildQueue( RemoveAllProc removeCallback );

private:
	char m_pad[8];
	TeamInQueue *m_queueHead;	// +0x08
};

void AIPlayer::removeAll_TeamBuildQueue( RemoveAllProc removeCallback )
{
	while (m_queueHead)
	{
		TeamInQueue *tmp = m_queueHead;
		((Rva004F0479 *)this)->rva004F0479( tmp );
		if (removeCallback)
			(*removeCallback)( tmp );
	}
}
