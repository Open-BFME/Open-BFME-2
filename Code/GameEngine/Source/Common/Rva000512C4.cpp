// cl: /DNDEBUG /MD
// ?internalSetReverbRoomType@MilesAudioManager@@QAEXH@Z @ 0x000512C4 143B.
// WorldBuilder 0x0078DC90 names it (MilesAudioManager.cpp:6327);
// the full retail body shares its LOD gate, provider layout, AIL calls
// and reverb-enabled/dirty byte updates at +0x6A7/+0x6A8.
class GameLODManager
{
public:
	struct Entry { unsigned char flag; char _q[7]; };
	char _p0[0x21d];
	Entry entries[3];
	char _p1[0x1770 - 0x235];
	int m_1770;
};
extern GameLODManager *TheGameLODManager;
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_room_type(int room, int unk);
extern "C" __declspec(dllimport) void __stdcall AIL_set_digital_master_room_type(int room, int unk);

struct RoomEntry { int room; char _p[8]; };

class MilesAudioManager
{
public:
	char _p0[0x678];
	int m_678;
	char _p1[0x6a7 - 0x67c];
	unsigned char m_6a7;
	unsigned char m_6a8;
	char _p2[0x6d0 - 0x6a9];
	RoomEntry m_rooms[64];
	int m_9d0;
	char _p3[0x9dc - 0x9d4];
	int m_9dc;
	void internalSetReverbRoomType(int a);
};

void MilesAudioManager::internalSetReverbRoomType(int a)
{
	int edi = a;
	if (edi != 0)
	{
		if (m_678 != 0)
			edi = 0;
		if (edi != 0)
		{
			GameLODManager *mgr = TheGameLODManager;
			if (mgr != 0)
			{
				int idx = mgr->m_1770;
				if (idx >= 0 && idx <= 2)
				{
					if (mgr->entries[idx].flag == 0)
						edi = 0;
				}
			}
		}
	}
	int cur = m_9d0;
	if (cur != -1)
	{
		AIL_set_3D_room_type(m_rooms[cur].room, edi);
		AIL_set_digital_master_room_type(m_9dc, edi);
	}
	if (edi == 0)
	{
		if (m_6a7 != 0)
		{
			m_6a7 = 0;
			m_6a8 = 1;
		}
	}
	else
	{
		m_6a7 = 1;
		m_6a8 = 1;
	}
}
