// ?AddArmy@LivingWorldPlayer@@QAEXPAVLivingWorldArmy@@@Z
// partial score=0.8929948491537896 date=2026-10-09
// cl: /O1 /Oy /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native2E246D..2E2504 RET4; WB DE3D70 names LivingWorldPlayer::AddArmy.
// Native fixes army data78, player color180/army-vector1B8 and summary
// color24/28. The lazy color count40/base-count38 match the already verified
// MultiplayerSettings provider; WB supplies color semantics, target offsets.
// Army-pointer storage uses the verified ModuleData-pointer vector view;
// the original vector's element spelling is not claimed by that view.
#include <vector>
class ModuleData;
struct Rva0040E6D6Arg;
class Rva0023CFFCLogic {public:void rva0023CFFC(Rva0040E6D6Arg*);};
class GameLogic;extern GameLogic*TheGameLogic;
struct ArmyData {char prefix[0x24];unsigned day,night;};
class LivingWorldArmy {public:char prefix[0x78];ArmyData*data;};
class MultiplayerColorDefinition {public:char prefix[0x10];unsigned day;char gap[0xc];unsigned night;};
class MultiplayerSettings {public:MultiplayerColorDefinition*getColor(int);__forceinline int getNumColors(){int*p=(int*)((char*)this+0x40);if(!*p)*p=*(int*)((char*)this+0x38);return *p;}};
extern MultiplayerSettings*TheMultiplayerSettings;
class LivingWorldPlayer {public:void AddArmy(LivingWorldArmy*);private:char prefix[0x180];int color;char gap[0x34];_STL::vector<const ModuleData*>armies;};
void LivingWorldPlayer::AddArmy(LivingWorldArmy*army){
 if(!army)return;
 armies.push_back(*(const ModuleData**)&army);
 if(color>=0&&color<TheMultiplayerSettings->getNumColors()){
  unsigned day=TheMultiplayerSettings->getColor(color)->day;
  unsigned night=TheMultiplayerSettings->getColor(color)->night;
  army->data->day=day;army->data->night=night;
 }else{army->data->day=0xff000000;army->data->night=0xff000000;}
 ((Rva0023CFFCLogic*)TheGameLogic)->rva0023CFFC((Rva0040E6D6Arg*)army->data);
}
