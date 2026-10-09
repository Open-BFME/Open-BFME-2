// ?testDefeat@VictoryConditions@@QAE_NPAVPlayer@@@Z
// partial score=0.8200263484660347 date=2026-10-10
// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD
extern "C" void *memset(void*,int,unsigned);
struct Rva0039DDC2Filter {Rva0039DDC2Filter(const Rva0039DDC2Filter&);__forceinline Rva0039DDC2Filter(int bit){memset(w,0,28);((unsigned char*)w)[bit/8]|=1<<(bit%8);} unsigned w[7];};
struct Rva0039DF1CFilter {Rva0039DF1CFilter(const Rva0039DF1CFilter&);__forceinline Rva0039DF1CFilter(int bit){memset(w,0,28);((unsigned char*)w)[bit/8]|=1<<(bit%8);}unsigned w[7];};
class BfmeFixedStorage0004543D{unsigned w[7];};extern const BfmeFixedStorage0004543D g_009FEFA4;
class BfmeTab1026{unsigned data;};
class Rva002AA22AByteField{public:unsigned char get()const;};
class Player {public:bool rva002AA22A();bool rva002AB295(Rva0039DDC2Filter,bool)const;bool hasAnyObjects(bool)const;bool rva002AB2D9(BfmeTab1026*,bool)const;bool rva002AB390(BfmeTab1026*)const;bool rva002AB341(Rva0039DF1CFilter,Rva0039DF1CFilter)const;};
class GameLogic;extern GameLogic*TheGameLogic;
class LivingWorldLogic {public:bool rva0004253A()const;};extern LivingWorldLogic*TheLivingWorldLogic;
class GameData;extern const GameData*TheGameData;
struct DefeatState{char prefix[0x110];int mode,network;};
struct DefeatTables{char prefix[0xebc];BfmeTab1026 buildings,units;};
class VictoryConditions {char prefix[12];int condition;public:bool testDefeat(Player*);};
bool VictoryConditions::testDefeat(Player *player) {
 if(((const Rva002AA22AByteField*)player)->get())goto defeated;
 DefeatState *state=(DefeatState*)TheGameLogic;
 if(state->network!=3 && TheLivingWorldLogic && TheLivingWorldLogic->rva0004253A())goto alive;
 if(state->mode==9)goto alive;
 switch(condition) {
 case 0:{Rva0039DDC2Filter mask(177);if(player->rva002AB295(mask,false))goto alive;goto defeated;}
 case 1:if(player->hasAnyObjects(false))goto alive;goto defeated;
 case 2:{if(player->rva002AB2D9(&((DefeatTables*)TheGameData)->buildings,false))goto alive;Rva0039DF1CFilter mask(14);return !player->rva002AB341(mask,reinterpret_cast<const Rva0039DF1CFilter&>(g_009FEFA4));}
 case 3:if(player->rva002AB2D9(&((DefeatTables*)TheGameData)->buildings,false))goto alive;return !player->rva002AB390(&((DefeatTables*)TheGameData)->units);
 default:goto alive;
 }
defeated:return true;
alive:return false;
}
