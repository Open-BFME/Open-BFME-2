// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// stlport
// ?rva0032A587@SidesList@@QAE_NHHPAVBuildListInfo@@H@Z retail
// 0x0032A587..0x0032A5FC (117 bytes ret 0x10). Copies one BuildListInfo
// out of the 20 keyed build-list records at SidesList +0xF80 (stride 0x1C:
// key then two STLport vectors of 0x80-byte BuildListInfo at +4 and +0x10;
// the same records SidesList::swap 0x0032B690 exchanges). Mode 0 or 1
// picks the vector; any other mode or an index past the end returns false;
// a key with no record returns false. The copy goes through the rowed
// BuildListInfo::operator= 0x003299AD. No direct caller (reached through a
// pointer). WorldBuilder twin 0x00A82E50 (align evidence) has two separate
// mode branches with their own size check and indexed copy; retail
// tail-merges them which is what fixes the re-read of the vector begin.
// Method name and record field names are address-derived or inferred.
#include <vector>

class BuildListInfo
{
public:
	BuildListInfo &operator=(const BuildListInfo &);

private:
	void *m_vtable;
	unsigned char m_body[0x7C];
};

struct SidesListBuildLists
{
	int m_key;
	std::vector<BuildListInfo> m_list0;
	std::vector<BuildListInfo> m_list1;
};

class SidesList
{
public:
	bool rva0032A587(int key, int index, BuildListInfo *out, int mode);

private:
	char m_pad[0xF80];
	SidesListBuildLists m_buildLists[20]; // +0xF80
};

bool SidesList::rva0032A587(int key, int index, BuildListInfo *out, int mode)
{
	if (mode != 0 && mode != 1)
		return false;
	for (int i = 0; i < 20; ++i)
	{
		if (m_buildLists[i].m_key == key)
		{
			if (mode == 0)
			{
				int size = m_buildLists[i].m_list0.size();
				if (index >= size)
					return false;
				*out = m_buildLists[i].m_list0[index];
			}
			else if (mode == 1)
			{
				int size = m_buildLists[i].m_list1.size();
				if (index >= size)
					return false;
				*out = m_buildLists[i].m_list1[index];
			}
			return true;
		}
	}
	return false;
}
