// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport
// ?rva004DF9B9@AIStatCollector@@QAEXPAXH@Z RVA 0x004DF9B9 size 43
// Sibling of 0x004DF9E4: iterates +0x2c..+0x30 calling vtable+0 when [elem+4] & mask with (arg 1).
// Evidence: callers in 0x004E01E3; neighbours use /O1 /MD; same layout as 0x004DF9E4.
#include <hash_map>
#include <vector>

class Player;

class Object;

class ModuleData;

class Rva005961D6;

class Rva00596069;

class Rva005965A5;

class AIEconomyStats;

class Rva00283081;

class AIStatCollector {
public: AIStatCollector(Player *);
 void Register(Object *,int);
 void Register(Object *);
 void UnRegister(void *);
 void addInfoReceiver(const ModuleData *);
 bool rva004DFB7E(Object *);
 void rva004DF9B9(void *,int);
private:
 Rva005961D6 *units;
 Rva00596069 *otherUnits;
 Rva005965A5 *structures;
 AIEconomyStats *resources;
 Rva00283081 *positions;
 _STL::hash_map<int,int> counts;
 Player *player;
 _STL::vector<const ModuleData *> listeners;
};

typedef char AIStatCollectorNativeSize[(sizeof(AIStatCollector)==0x38)?1:-1];

class FilterElem
{
public:
	virtual void v0(void *a, int b);
	virtual void v1(void *a);
	int m_flags;
};

void AIStatCollector::rva004DF9B9(void *a, int mask)
{
	FilterElem **beg = (FilterElem **)listeners.begin();
	FilterElem **end = (FilterElem **)listeners.end();
	for (; beg != end; ++beg)
	{
		FilterElem *filterElem = *beg;
		if (filterElem->m_flags & mask)
			filterElem->v0(a, 1);
	}
}
