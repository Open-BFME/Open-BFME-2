// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// CreateAHeroManager::CreateAHeroSubClass::GetBling @ 0x0021BCA7 67B and
// ::GetBlingIndex @ 0x0021BCEA 56B (WorldBuilder names; both look the bling
// key up through 0x0021BC0D as WB's do, GetBling then calls
// CreateAHeroManager::GetBling 0x00219D85 as WB's does).
// __thiscall vector-index lookup via rowed 0x0021BC0D find: map<int,vector<unsigned>>
// at +0x24, bounds-check index vs (finish-start)/4, then forwards element through
// rowed CreateAHeroManager::GetBling on global TheCreateAHeroManager, else null. Evidence: lea/push
// out+key call 0x0021BC0D test je xor, node+0x14/+0x18 sar 2 cmp jb push [ecx+eax*4]
// mov ecx [0x00DFE344] call 0x00219D85 ret 8; unblocks 0x0021C970/0x0021C9A6.
#include <map>
#include <vector>

class CreateAHeroManager
{
public:
	struct CreateAHeroSubClass;
	void *GetBling(unsigned int index);
};

extern CreateAHeroManager *TheCreateAHeroManager;

struct MapNodeVec
{
	char hdr[0x10];
	int key;
	unsigned *m_start;
	unsigned *m_finish;
	unsigned *m_end;
};

struct CreateAHeroManager::CreateAHeroSubClass
{
	char pad[0x24];
	_STL::map<int, _STL::vector<unsigned int> > m_map;
	unsigned char rva0021BC0D(int key, void **out);
	void *GetBling(int key, unsigned int index);
	unsigned int GetBlingIndex(int key, unsigned int index);
};

void *CreateAHeroManager::CreateAHeroSubClass::GetBling(int key, unsigned int index)
{
	void *node = 0;
	if (!rva0021BC0D(key, &node))
		return 0;
	MapNodeVec *n = (MapNodeVec *)node;
	unsigned int count = (unsigned int)(((char *)n->m_finish - (char *)n->m_start) >> 2);
	if (index >= count)
		return 0;
	return TheCreateAHeroManager->GetBling(n->m_start[index]);
}
unsigned int CreateAHeroManager::CreateAHeroSubClass::GetBlingIndex(int key, unsigned int index)
{
	void *node = 0;
	if (!rva0021BC0D(key, &node))
		return 0;
	MapNodeVec *n = (MapNodeVec *)node;
	unsigned int count = (unsigned int)(((char *)n->m_finish - (char *)n->m_start) >> 2);
	if (index >= count)
		return 0;
	return n->m_start[index];
}
