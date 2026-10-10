// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// AIStatCollector is established by the
// Register/UnRegister sibling owner and the SkirmishAIManager allocation.
// Native 4E030B..4E0425 proves the offsets and allocation sizes below.
// The hash table stores four-byte counts (Register increments node+8),
// while listener element identity is unresolved; an int header suffices
// only for this empty-vector constructor and its free-on-rollback path.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>
#include <vector>
class Player;
class Rva005961D6 { public: Rva005961D6(); private: char bytes[0xa4]; };
class Rva00596069 { public: Rva00596069(); private: char bytes[0x10]; };
class Rva005965A5 { public: Rva005965A5(); private: char bytes[0x1c]; };
class Rva00596389 { public: Rva00596389(int); private: char bytes[0x1c]; };
class Rva00283081 { public: Rva00283081(float,int) throw(); private: char bytes[0x24]; };
class Rva002A8F24;
extern Rva002A8F24 *g_00DFEEF8;
struct CollectorManagerView { char prefix[0x878]; float interval; };
void *Rva004DF983Field(void *);
class AIStatCollector {
public: AIStatCollector(Player *);
private:
 Rva005961D6 *units;
 Rva00596069 *otherUnits;
 Rva005965A5 *structures;
 Rva00596389 *resources;
 Rva00283081 *positions;
 _STL::hash_map<int,int> counts;
 Player *player;
 _STL::vector<int> listeners;
};
typedef char AIStatCollectorNativeSize[(sizeof(AIStatCollector)==0x38)?1:-1];
// The target has no operator-delete rollback state for this last helper's
// construction. Its throw() declaration preserves that native EH behavior;
// the existing helper provider keeps the same binary constructor ABI.
AIStatCollector::AIStatCollector(Player *owner)
 :units(0),otherUnits(0),structures(0),resources(0),player(owner)
{
 units=new Rva005961D6;
 otherUnits=new Rva00596069;
 structures=new Rva005965A5;
 resources=new Rva00596389(reinterpret_cast<int>(player));
 positions=new Rva00283081(reinterpret_cast<CollectorManagerView *>(g_00DFEEF8)->interval,
                          reinterpret_cast<int>(&Rva004DF983Field));
}

// Independently recovered native cdecl callback at4DF983..4DF98B.
void *Rva004DF983Field(void *owner) { return static_cast<char *>(owner)+0x38; }
