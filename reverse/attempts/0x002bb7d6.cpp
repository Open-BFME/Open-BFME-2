// ?Update@Rva002B74DE@@QAEHXZ
// partial score=0.8 date=2026-10-10
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP=
// Complete target623B resolver Update trial; structural bank only.
// Native2BB7D6..2BBA45 and WB D7B800 establish purpose and control.
// Every REL32 uses an actual provider or existing admitted pin; native
// region-end20FB8B is still an unprovided link prerequisite. Fields below
// reflect target accesses only and do not assert complete original types.
typedef int Int;typedef bool Bool;
class Rva004FA2E2;struct ResolverUnit2B74DE;
struct Rva002B89BBInfo;struct Rva003F4E07Results;
class LivingWorldAutoResolveBattle;
class LivingWorldBattle {
public:
 void ComputeBattleResultsForPlayersAfterAutoBattle(Rva003F4E07Results*);
 char pad00[0x18];struct SideRecord {char data[0x1c];} *m_sides,*m_sidesEnd;
 char pad20[0x18];int m_side;
};
class LivingWorldLogic {public:
 void OnBattleComplete(LivingWorldBattle*);
 void rva002B3833(LivingWorldBattle*,Rva002B89BBInfo*);
};
class LivingWorldRegionManager {public:void rva0020FB8B(LivingWorldBattle*);};
class Rva003F468D {public:Int rva003F468D(Int,Int);Int rva003F4DAE(Int);};
class Rva002B74DE {
public:Int Update();
private:LivingWorldLogic *m_logic;LivingWorldBattle *m_battle;
 ResolverUnit2B74DE *m_units;Rva004FA2E2 *m_sim;char tail10[0x18];
};
class Rva002B471B {public:Bool rva002B471B();};
class Rva002B466E {public:Bool rva002B466E();};
class Rva004FA10FOwner {public:void rva004FA10F();};
struct ResolverSimHeader {int winner()const{return winner78;}void *players;char pad04[0x78-4];int winner78;};
struct ResolverPlayerRecord {char pad00[0x2c];int side2c;int tail30;};
struct ResolverUnit2B74DE {char pad00[0xc];float value0c;float getValue()const{return value0c;}char pad10[0x1c-0x10];int value1c;char tail20[0x2c-0x20];};
struct ResolverArmyView {char pad00[0x1c8];float value1c8;};
class Rva004E05E9DwordField {public:int get()const;};
class Rva002E062EDwordSlot {public:void set(int);};
class Rva002B6126Listener {public:virtual void slot00();virtual void slot04(void*,int,int);virtual void slot08(void*,int,int);};
class Rva002B6126List {public:void forEach(void(Rva002B6126Listener::*)(void*,int,int),void*,int,int);};
class Rva002B4349 {public:~Rva002B4349();Rva002B4349(Rva002B4349 &from){Rva004FA2E2 *p=from.m_ptr;from.m_ptr=0;m_ptr=p;} Rva002B4349 &transfer(){return *this;}Rva004FA2E2 *m_ptr;};
class Rva002B430C {public:void clear();};
class Rva002B43E7 {public:Rva002B43E7(Rva002B4349);~Rva002B43E7(){((Rva002B430C*)this)->clear();}Rva004FA2E2 *m_ptr;};
class Rva002B54BB {public:Rva002B4349 rva002B54BB();};
class LivingWorldAutoResolveBattle {public:void applyResults();};

Int Rva002B74DE::Update(){
 if(m_sim){
 if(!((Rva002B466E*)this)->rva002B466E())return 0;
 if(((ResolverSimHeader*)m_sim)->winner()==-1){
  Bool fast=((Rva002B471B*)this)->rva002B471B();
  for(;;){
   ((Rva004FA10FOwner*)m_sim)->rva004FA10F();
   ((Rva002B6126List*)((char*)m_logic+0x2c))->forEach(&Rva002B6126Listener::slot04,m_logic,(int)m_battle,(int)m_sim);
   if(((ResolverSimHeader*)m_sim)->winner()!=-1)break;
   fast=fast || ((Rva002B471B*)this)->rva002B471B();
   if(!fast && !((Rva002B466E*)this)->rva002B466E())return 0;
  }
 }
 Rva002B43E7 owned(((Rva002B54BB*)&m_sim)->rva002B54BB().transfer());
 ((LivingWorldAutoResolveBattle*)owned.m_ptr)->applyResults();
 ResolverSimHeader *result=(ResolverSimHeader*)owned.m_ptr;
 int index=0;
 for(int side=0;side<m_battle->m_sidesEnd-m_battle->m_sides;++side){
  int count=((Rva003F468D*)m_battle)->rva003F4DAE(side);
  for(int army=0;army<count;++army,++index){
   ResolverArmyView *a=(ResolverArmyView*)((Rva003F468D*)m_battle)->rva003F468D(side,army);
   a->value1c8=m_units[index].getValue();
   int value=m_units[index].value1c;
   value-=((Rva004E05E9DwordField*)a)->get();
   ((Rva002E062EDwordSlot*)a)->set(value);
  }
 }
 index=0;
 for(int side=0;side<m_battle->m_sidesEnd-m_battle->m_sides;++side){
  Bool found=false;
  int count=((Rva003F468D*)m_battle)->rva003F4DAE(side);
  for(int army=0;army<count;++army,++index){
   if(((ResolverPlayerRecord*)result->players)[index].side2c==((ResolverSimHeader*)owned.m_ptr)->winner78){
    if(!found){m_battle->m_side=side;found=true;}
   }else{
    struct Rva002B89BBInfo *a=(struct Rva002B89BBInfo*)((Rva003F468D*)m_battle)->rva003F468D(side,army);
    m_logic->rva002B3833(m_battle,a);
   }
  }
 }
 m_battle->ComputeBattleResultsForPlayersAfterAutoBattle((Rva003F4E07Results*)owned.m_ptr);
 m_logic->OnBattleComplete(m_battle);
 ((Rva002B6126List*)((char*)m_logic+0x2c))->forEach(&Rva002B6126Listener::slot08,m_logic,(int)m_battle,(int)owned.m_ptr);
 ((LivingWorldRegionManager*)*(void**)((char*)m_logic+0xb0))->rva0020FB8B(m_battle);
 }
 return 1;
}
