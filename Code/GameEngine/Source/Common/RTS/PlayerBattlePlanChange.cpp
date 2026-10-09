// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc
// Donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705;
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/Player.cpp3420.
// Rva002AA14DBonuses is the existing BFME2 owner; its named constructor
// and apply provider already establish this 4C-byte record. Donor purpose
// and native/WB transition evidence below establish the counter meanings.
#define __max(a,b) (((a)>(b))?(a):(b))
class Rva002AA14DBonuses {public:float m_armorScalar;int m_bombardment,m_searchAndDestroy,m_holdTheLine;float m_sightRangeScalar;unsigned char masks[0x38];};
typedef Rva002AA14DBonuses BattlePlanBonuses;
enum BattlePlanStatus {PLANSTATUS_BOMBARDMENT=1,PLANSTATUS_HOLDTHELINE=2,PLANSTATUS_SEARCHANDDESTROY=3};
class Player {public:void changeBattlePlan(BattlePlanStatus,int,BattlePlanBonuses*);void applyBattlePlanBonusesForPlayerObjects(const BattlePlanBonuses*);private:char pad[0xAC];int m_bombardBattlePlans,m_holdTheLineBattlePlans,m_searchAndDestroyBattlePlans;};
// ZH Player.cpp changeBattlePlan; WB C1E400 uses plan values1/2/3 and
// the same add/remove transition. Target2ADB4F..2ADC03 establishes counts
// AC/B0/B4, and bonus field offsets0/10 and4/C/8, capped reciprocals and
// the existing applyBattlePlanBonusesForPlayerObjects target2AC9BF.
void Player::changeBattlePlan(BattlePlanStatus plan,int delta,BattlePlanBonuses*bonus){
 int*count;
 switch(plan){case PLANSTATUS_BOMBARDMENT:count=&m_bombardBattlePlans;break;
 case PLANSTATUS_HOLDTHELINE:count=&m_holdTheLineBattlePlans;break;
 case PLANSTATUS_SEARCHANDDESTROY:count=&m_searchAndDestroyBattlePlans;break;
 default:return;}
 *count+=delta;
 if(*count==1&&delta==1)applyBattlePlanBonusesForPlayerObjects(bonus);
 else if(*count==0&&delta==-1){
 bonus->m_armorScalar=1.f/__max(bonus->m_armorScalar,0.01f);
 bonus->m_sightRangeScalar=1.f/__max(bonus->m_sightRangeScalar,0.01f);
 if(bonus->m_bombardment>0)bonus->m_bombardment=-1;
 if(bonus->m_holdTheLine>0)bonus->m_holdTheLine=-1;
 if(bonus->m_searchAndDestroy>0)bonus->m_searchAndDestroy=-1;
 applyBattlePlanBonusesForPlayerObjects(bonus);
 }
}
