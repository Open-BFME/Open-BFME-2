// ?bfmePrivateCommand49@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
// partial score=0.9 date=2026-10-09
// ?bfmePrivateCommand49@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native26C0D6..26C150: AI command49, dispatch slot41, state21.
// Target fields: owner8/stateMachine30/source48/blocked16C/locomotor1F0,
// byte3B8 and dead3BD. StateMachine vslots14/38/20 are native calls.
// Existing Object::isMobile2907A1, locomotor1E4147 and proven voice
// playVoiceEnterStateAttackMove26B37F now resolve without surrogate pins.
// Coord3D is canonical; command values0/1 agree with native tests and readonly
// BFME1 9cbfb551 command_source_type.h. Opaque prefixes assert only accesses.
// Fresh123B instead122: target is reloaded from argument rather than cached
// in EBX; O1/O2-Os/forceinline/named target unchanged, Ot126.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
class Object {public:bool isMobile()const;const Coord3D*getPosition()const{return &position;}private:char prefix[0x38];Coord3D position;};
enum StateID {BFME_AI_ATTACK_MOVE_TO=0x21};
class StateMachine {
public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void clear();virtual void s6();virtual void s7();virtual void setState(StateID);virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void setGoalObject(const Object*);
};
struct Rva001E4147Twelve;
class Rva001E4147{public:void rva001E4147(Rva001E4147Twelve*);};
class AIUpdateInterface {
protected:virtual void bfmePrivateCommand49(Object*,CommandSourceType);void playVoiceEnterStateAttackMove(const Coord3D*);
private:char p4[4];Object*m_object;char pC[0x30-0xC];StateMachine*m_stateMachine;char p34[0x48-0x34];CommandSourceType m_lastCommandSource;char p4C[0x16C-0x4C];int m_blockedFrames;char p170[0x1F0-0x170];Rva001E4147*m_curLocomotor;char p1F4[0x3B8-0x1F4];unsigned char m_bfmeByte3B8;char p3B9[4];unsigned char m_isAiDead;
};
void AIUpdateInterface::bfmePrivateCommand49(Object*obj,CommandSourceType source){
 if(m_isAiDead)return;
 if(!m_object->isMobile())return;
 if(m_curLocomotor)m_curLocomotor->rva001E4147((Rva001E4147Twelve*)m_object);
 m_stateMachine->clear();m_stateMachine->setGoalObject(obj);
 m_blockedFrames=0;m_bfmeByte3B8=0;m_lastCommandSource=source;
 m_stateMachine->setState(BFME_AI_ATTACK_MOVE_TO);
 if(source==CMD_FROM_PLAYER||source==CMD_FROM_SCRIPT)playVoiceEnterStateAttackMove(obj->getPosition());
}
