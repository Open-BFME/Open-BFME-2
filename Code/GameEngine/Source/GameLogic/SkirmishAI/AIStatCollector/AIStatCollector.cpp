// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// Native 4DF983..4DF98B is a cdecl field-address callback, ending before
// the independently owned collector dispatch at 4DF98B. The collector
// constructor at 4E030B passes its address into the tracker at +10.
// Target bytes establish only the +38 field address, not its original name.
void *Rva004DF983Field(void *owner) {
    return static_cast<char *>(owner)+0x38;
}

// Native4E030B..4E0425 constructs the 38-byte collector allocated by the
// independently named manager addNewAIForPlayer WB twin. Register/UnRegister
// establish its five tracker slots and count map at14. Child allocation sizes
// and constructor bindings come from retail; storage-only views retain their
// established neutral names. The final tracker call has no allocation cleanup
// EH state: its declaration preserves that nonthrowing native call boundary.
// The callback is a recovered function symbol; no numeric code address remains.
// stlport
#include <hash_map>
#include <vector>
#include <new>
struct Rva004E02B8Element { char bytes[1]; bool operator<(const Rva004E02B8Element&)const; bool operator==(const Rva004E02B8Element&)const; };
struct BfmeE16 { float x,y,z,w; };
namespace _STL {
template<> hash_map<int,Rva004E02B8Element>::hash_map();
}
class Player;
class Rva005961D6 { public: Rva005961D6(); char storage[0xa4]; };
class Rva00596069 { public: Rva00596069(); char storage[0x10]; };
class Rva005965A5 { public: Rva005965A5(); char storage[0x1c]; };
class Rva00596389 { public: Rva00596389(int); char storage[0x1c]; };
class Rva00283081 { public: Rva00283081(float,int) throw(); char storage[0x24]; };
void *Rva004DF983Field(void *);
class Rva002A8F24 { public: char prefix[0x878]; float sample878; };
extern Rva002A8F24 *g_00DFEEF8;
class AIStatCollector {
public:
 AIStatCollector(Player *player);
private:
 Rva005961D6 *unit00;
 Rva00596069 *unit04;
 Rva005965A5 *unit08;
 Rva00596389 *unit0c;
 Rva00283081 *unit10;
 _STL::hash_map<int,Rva004E02B8Element> map14;
 Player *player28;
 _STL::vector<BfmeE16> vector2c;
};
AIStatCollector::AIStatCollector(Player *player)
 : unit00(0),unit04(0),unit08(0),unit0c(0),player28(player) {
 unit00=new Rva005961D6;
 unit04=new Rva00596069;
 unit08=new Rva005965A5;
 unit0c=new Rva00596389((int)player28);
 unit10=new Rva00283081(g_00DFEEF8->sample878,(int)&Rva004DF983Field);
}
