// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// stlport
// ?rva0021BCA7@Rva0021BCA7@@QAEPAXHI@Z @ 0x0021BCA7 67B
// __thiscall vector-index lookup via rowed 0x0021BC0D find: map<int,vector<unsigned>>
// at +0x24, bounds-check index vs (finish-start)/4, then forwards element through
// rowed Rva00219B9E::rva00219D85 on global g_00DFE344, else null. Evidence: lea/push
// out+key call 0x0021BC0D test je xor, node+0x14/+0x18 sar 2 cmp jb push [ecx+eax*4]
// mov ecx [0x00DFE344] call 0x00219D85 ret 8; unblocks 0x0021C970/0x0021C9A6.
#include <map>
#include <vector>

class Rva0021BC0D
{
public:
	unsigned char rva0021BC0D(int key, void **out);
};

class Rva00219B9E
{
public:
	void *rva00219D85(unsigned int index);
};

extern Rva00219B9E *g_00DFE344;

struct MapNodeVec
{
	char hdr[0x10];
	int key;
	unsigned *m_start;
	unsigned *m_finish;
	unsigned *m_end;
};

struct Rva0021BCA7
{
	char pad[0x24];
	_STL::map<int, _STL::vector<unsigned int> > m_map;
	void *rva0021BCA7(int key, unsigned int index);
};

void *Rva0021BCA7::rva0021BCA7(int key, unsigned int index)
{
	void *node = 0;
	if (!((Rva0021BC0D *)this)->rva0021BC0D(key, &node))
		return 0;
	MapNodeVec *n = (MapNodeVec *)node;
	unsigned int count = (unsigned int)(((char *)n->m_finish - (char *)n->m_start) >> 2);
	if (index >= count)
		return 0;
	return g_00DFE344->rva00219D85(n->m_start[index]);
}
