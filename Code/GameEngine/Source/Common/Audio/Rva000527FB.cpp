// cl: /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// Audibility check at 0x000527FB (92B): an audio event is audible when its
// +0x30 word is clear, its +0x8 referent carries flag 4 at +0x48, the owner
// position resolves valid, both singletons are present, and the local
// player's shroud status at the resolved position is not clear. Deeply nested
// guards route every false to the shared end block; the unsigned-char return
// with int literals selects the branchy mov-al-1 tail over setne.
// class-gate: allow BfmeAudioEventPrefix136 POD caller-view: the canonical header's user-defined ctors force a return-temp plus memcpy for rva002DA1CC, retail builds the 12B view in place
struct BfmeEventPositionView
{
	float x;
	float y;
	float z;
};

class BfmeAudioEventPrefix136
{
	char m_pad0[8];
public:
	void *m_sub8;
	char m_padC[0x30 - 0xC];
	int m_int30;
	BfmeEventPositionView rva002DA1CC(bool &valid);
};

enum CellShroudStatus
{
	SHROUD_CLEAR = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};

class PlayerList;
extern PlayerList *ThePlayerList;
extern PartitionManager *TheShroudManager;

unsigned char __stdcall Rva000527FB(BfmeAudioEventPrefix136 *ev)
{
	if (ev->m_int30 == 0)
	{
		void *sub = ev->m_sub8;
		if ((*(unsigned char *)((char *)sub + 0x48) & 4) != 0)
		{
			bool valid;
			BfmeEventPositionView pos = ev->rva002DA1CC(valid);
			if (valid)
			{
				if (ThePlayerList != 0)
				{
					if (TheShroudManager != 0)
					{
						int index = *(int *)((char *)*(void **)((char *)ThePlayerList + 0x10) + 0x54);
						if (TheShroudManager->getShroudStatusForPlayer(index, (const Coord3D *)&pos) != SHROUD_CLEAR)
							return 1;
					}
				}
			}
		}
	}
	return 0;
}
