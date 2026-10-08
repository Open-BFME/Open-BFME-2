// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ob2
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
// Semantic guide: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameClient/InGameUICanSelectedObjectsDoAction.cpp,
// originally adapted from GeneralsMD InGameUI.cpp.
// Identity: named WB DBA3A0 dispatcher, native selected-list/rule loop and
// individually owned ActionManager callees corroborate the reference method.
// Target: retail 29C823..29CB52 is 815 bytes through RET16; its 21-dword
// switch table immediately follows at 29CB52..29CBA6 (899-byte full extent).
// Case 7 goes to the default path; case 12 first obtains the capture interface.
// Layout evidence: native Drawable object +FC, Object ID +74 and contain +250,
// Thing template +4, template kind bits +108 (WB tests 15 and 69); UI slot 73,
// contain slots 6/13 and exit slot 6. These are accessed prefixes, not complete
// recovered class layouts. Member labels follow the reference and rowed getters.
// hasDispatchKind is a local accessed-prefix reader, avoiding a competing
// emitted definition of the engine-owned Thing::isKindOf.
// The truth byte preserves the existing byte-return helpers without normalizing
// them differently from retail; their established returns are already 0 or 1.
// The address-named ActionManager methods retain uncertain original names.
enum KindOfType { KINDOF_INVALID=0 };
enum ObjectID { INVALID_ID=0 };
enum CommandSourceType { CMD_FROM_PLAYER=0 };
enum CanEnterType { CHECK_CAPACITY=0,DONT_CHECK_CAPACITY=1,COMBATDROP_INTO=2 };
enum SpecialPowerType { SPECIAL_POWER_INVALID=0 };
class ContainModuleInterface; class ExitInterface; class SpecialPowerModuleInterface; class CapturePowerView;
struct ThingTemplate { char pad[0x108]; unsigned char kinds[28]; };
class Thing { public:
 void *vptr; ThingTemplate *m_template;
 __forceinline bool hasDispatchKind(KindOfType kind)const { return (m_template->kinds[(unsigned)kind/8] & (1<<((unsigned)kind%8)))!=0; }
};
class Object:public Thing { public:
 char pad8[0x74-8]; ObjectID m_id; char pad78[0x250-0x78]; ContainModuleInterface *m_contain;
 ObjectID getSoleHealingBenefactor()const;
 ExitInterface *getObjectExitInterface()const;
 bool isLocallyControlled()const;
 SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType)const;
};
class Drawable:public Thing { public: char pad8[0xfc-8]; Object *m_object; Object *getObject()const{return m_object;} };
class ContainModuleInterface { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual bool isHealContain()const;
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual bool rva0029C823Slot13()const;
};
class ExitInterface { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual bool rva0029C823Slot6()const;
};
class Rva0041B8D2Obj;




class ActionManager { public:
 unsigned char Rva0041BB87IsRelated(Object*,Object*,int);
 bool Rva0041CE27Check(Object*,Object*,int);
 bool Rva0041B94AGet(Object*,Object*,int);
 unsigned char Rva0041B8D2Check(Rva0041B8D2Obj*,Rva0041B8D2Obj*,int);
 bool canGetRepairedAt(const Object*,const Object*,CommandSourceType);
 bool canDockAt(const Object*,const Object*,CommandSourceType,bool);
 bool canGetHealedAt(const Object*,const Object*,CommandSourceType);
 bool canRepairObject(const Object*,const Object*,CommandSourceType);
 bool canHijackVehicle(const Object*,const Object*,CommandSourceType);
 bool canConvertObjectToCarBomb(const Object*,const Object*,CommandSourceType);
 bool canMakeObjectDefector(const Object*,const Object*,CommandSourceType);
 bool rva0041C79C(const Object*,const Object*,CommandSourceType,CapturePowerView*);
};
class BFMEActionManager { public:
 bool canEnterObject(const Object*,const Object*,CommandSourceType,CanEnterType,bool,bool*);
 bool rva0041D435(const Object*,const Object*,CommandSourceType);
};
extern ActionManager *TheActionManager;
struct DrawableListNode { DrawableListNode *next,*prev; Drawable *value; };
class DrawableList { public:
 class const_iterator { DrawableListNode *node; public:
 const_iterator(DrawableListNode*n):node(n){}
 bool operator!=(const const_iterator&b)const{return node!=b.node;}
 Drawable *operator*()const{return node->value;}
 const_iterator &operator++(){node=node->next;return *this;}
 };
 DrawableListNode *head;
 const_iterator begin()const{return const_iterator(head->next);}
 const_iterator end()const{return const_iterator(head);}
};
class InGameUI { public:
 enum ActionType { ACTIONTYPE_NONE=0 };
 enum SelectionRules { SELECTION_ANY=0,SELECTION_ALL=1 };
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual const DrawableList *getAllSelectedDrawables()const;
 bool canSelectedObjectsDoAction(ActionType,const Object*,SelectionRules,bool)const;
};
extern InGameUI *TheInGameUI;
bool InGameUI::canSelectedObjectsDoAction(ActionType action,const Object *target,SelectionRules rule,bool additionalChecking) const {
 const DrawableList *selected=TheInGameUI->getAllSelectedDrawables();
 int count=0;
 int qualify=0;
 Drawable *other;
 for(DrawableList::const_iterator it=selected->begin();it!=selected->end();++it) {
  other=*it;
  count++;
  unsigned char success=false;
  switch(action) {
   case 0: return true;
   case 2: success=TheActionManager->canGetRepairedAt(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 20: success=TheActionManager->canDockAt(other->getObject(),target,CMD_FROM_PLAYER,true); break;
   case 3: success=TheActionManager->canDockAt(other->getObject(),target,CMD_FROM_PLAYER,false); break;
   case 4: success=TheActionManager->Rva0041B8D2Check((Rva0041B8D2Obj*)other->getObject(),(Rva0041B8D2Obj*)target,0); break;
   case 5:
    success=TheActionManager->canGetHealedAt(other->getObject(),target,CMD_FROM_PLAYER);
    if(success) { ContainModuleInterface *contain=target->m_contain; if(contain && contain->isHealContain()) success=false; }
    break;
   case 6: {
    ObjectID currentRepairer=target->getSoleHealingBenefactor();
    success=TheActionManager->canRepairObject(other->getObject(),target,CMD_FROM_PLAYER);
    if(success && !other->hasDispatchKind((KindOfType)15) && (currentRepairer==INVALID_ID || currentRepairer==other->getObject()->m_id)) success=false;
    break;
   }
   case 15: success=((BFMEActionManager*)TheActionManager)->canEnterObject(other->getObject(),target,CMD_FROM_PLAYER,COMBATDROP_INTO,true,0); break;
   case 8: {
    bool special;
    success=((BFMEActionManager*)TheActionManager)->canEnterObject(other->getObject(),target,CMD_FROM_PLAYER,additionalChecking?CHECK_CAPACITY:DONT_CHECK_CAPACITY,true,&special);
    if(success && special) success=false;
    break;
   }
   case 9: {
    bool special;
    success=((BFMEActionManager*)TheActionManager)->canEnterObject(other->getObject(),target,CMD_FROM_PLAYER,additionalChecking?CHECK_CAPACITY:DONT_CHECK_CAPACITY,true,&special);
    if(success && !special) success=false;
    break;
   }
   case 1: return false;
   case 10: success=TheActionManager->canHijackVehicle(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 11: success=TheActionManager->canConvertObjectToCarBomb(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 16: success=TheActionManager->Rva0041B94AGet(other->getObject(),const_cast<Object*>(target),0); break;
   case 12: { CapturePowerView *capture=(CapturePowerView*)other->getObject()->findSpecialPowerModuleInterface((SpecialPowerType)0x1d); success=TheActionManager->rva0041C79C(other->getObject(),target,CMD_FROM_PLAYER,capture); break; }
   case 17: success=((BFMEActionManager*)TheActionManager)->rva0041D435(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 13: success=TheActionManager->canMakeObjectDefector(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 18: success=TheActionManager->Rva0041CE27Check(other->getObject(),const_cast<Object*>(target),0); break;
   case 14: {
    Object *obj=other->getObject();
    if(!obj) {success=false;break;}
    ContainModuleInterface *contain=target?target->m_contain:0;
    ExitInterface *exit=obj->getObjectExitInterface();
    if(contain && exit && contain->rva0029C823Slot13() && exit->rva0029C823Slot6()) success=true; else success=(obj->hasDispatchKind((KindOfType)69) && obj->isLocallyControlled());
    break;
   }
   case 19: success=TheActionManager->Rva0041BB87IsRelated(other->getObject(),const_cast<Object*>(target),0); break;
  }
  if(success) { if(rule==SELECTION_ANY) return true; ++qualify; }
 }
 if(rule==SELECTION_ALL && count>0 && qualify==count) return true;
 return false;
}
