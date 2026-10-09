// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target: 002B7DE6..002B8019,563B RET4; WB D8C360 explicitly
// names LivingWorldLogic::RemovePlayer. Native fields independently fix
// players8C, region-managerB0, object-vector10C and army-vector118;
// player id14, objects1B8 and lost3C4; region army IDs164;
// army owner54/data78, whose endpoint range40/44 has eight-byte entries.
// The entries' original payload type is unknown; only their count is used.
// Existing LivingWorldLogic/STLport providers are the reference spine;
// WB gives campaign ownership behavior, native bytes determine each layout.
// Shape: copied find key, inline lost getter, pre-zeroed cached ID count,
// raw entry-range count, cached effects receiver and const borrowed owned
// IDs reproduce the complete native body. EHs preserves C-free unwind state.
// Army IDs use a four-byte enum view: retail dispatches the non-POD
// vector-copy path. The original enum spelling is unknown.
#include <vector>
#include <algorithm>
class ModuleData;
struct Rva0020FD7FFilter;
class Rva0020FD7F {public:void rva0020FD7F(Rva0020FD7FFilter*,_STL::vector<const ModuleData*>*);};
class Rva002E1F88 {public:void markLost();};
class Rva002E21D1 {public:void rva002E21D1();};
class Rva002E0687;
class Rva002B4E83 {public:void rva002B4E83(Rva002E0687*);};
struct ArmyEntry {unsigned a,b;};
struct ArmyData {char prefix[0x40];ArmyEntry*begin,*end,*capacity;__forceinline int count()const{return (int)(end-begin);}};
struct Rva002B488EResult {char prefix[0x54];int owner;char gap[0x20];ArmyData*data;};
class Rva002BA8F1Logic {public:Rva002B488EResult*rva002B488E(int);};
class LivingWorldPlayer {public:char prefix[0x14];int id;char gap[0x1a0];_STL::vector<int> objects;char gap2[0x200];bool lost;__forceinline bool hasLost()const{return lost;}};
enum Rva002B7DE6ArmyID { Rva002B7DE6InvalidArmyID=-1 };
class LivingWorldRegion {public:void rva003F2A8C(int);char prefix[0x164];_STL::vector<Rva002B7DE6ArmyID> armyIDs;};
class LivingWorldRegionEffectsManager {public:void SyncRegion(int);};
class Rva00DFE1C8Host {public:char prefix[0x268];LivingWorldRegionEffectsManager*effects;};
class LivingWorldManager;extern LivingWorldManager*TheLivingWorldManager;
class LivingWorldLogic {public:void RemovePlayer(LivingWorldPlayer*);private:char prefix[0x8c];_STL::vector<LivingWorldPlayer*> players;char gap[0x18];Rva0020FD7F*regionManager;char gap2[0x58];_STL::vector<void*>objects;_STL::vector<Rva002B488EResult*>armies;};
void LivingWorldLogic::RemovePlayer(LivingWorldPlayer*player){
 LivingWorldPlayer*key=player;
 if(_STL::find(players.begin(),players.end(),key)==players.end())return;
 if(player->hasLost())return;
 ((Rva002E1F88*)player)->markLost();
 _STL::vector<const ModuleData*>regions;
 regionManager->rva0020FD7F((Rva0020FD7FFilter*)player,&regions);
 for(unsigned i=0;i<regions.size();++i){
  int newOwner=-1;Rva002B488EResult*best=0;
  _STL::vector<Rva002B7DE6ArmyID>ids=((LivingWorldRegion*)regions[i])->armyIDs;
  unsigned j=0;const unsigned numIDs=ids.size();for(;j<numIDs;++j){
   Rva002B488EResult*army=((Rva002BA8F1Logic*)this)->rva002B488E(ids[j]);
   if(army&&army->owner!=player->id){
    if(!best||army->data->count()>best->data->count()){best=army;newOwner=army->owner;}
   }
  }
  ((LivingWorldRegion*)regions[i])->rva003F2A8C(newOwner);
  LivingWorldRegionEffectsManager*effects=((Rva00DFE1C8Host*)TheLivingWorldManager)->effects;effects->SyncRegion((int)regions[i]);
 }
 const _STL::vector<int>&owned=player->objects;for(unsigned i=0;i<owned.size();++i){
  for(unsigned j=0;j<objects.size();++j){
   if((int)objects[j]==owned[i]){objects.erase(objects.begin()+j);break;}
  }
 }
 int i=armies.size();while(--i>=0){if(armies[i]->owner==player->id){((_STL::vector<void*>*)&armies)->erase(((_STL::vector<void*>*)&armies)->begin()+i);}}
 ((Rva002E21D1*)player)->rva002E21D1();((Rva002B4E83*)this)->rva002B4E83((Rva002E0687*)player);
}
