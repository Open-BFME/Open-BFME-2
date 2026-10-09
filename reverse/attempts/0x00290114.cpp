// ?setDisabledUntil@Object@@QAEXW4DisabledType@@I@Z
// partial score=0.9335248 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /I.
// SPDX-License-Identifier: GPL-3.0-or-later
// ZH Object.cpp::setDisabledUntil at BFME1 9cbfb551 is the semantic spine.
// WB CCCA00 independently names the target 290114..290357 (579B).
// Target deltas: early frame guard;11 types; mask1C8/frames1CC; audio refs
// 40/48/50; native model word14C bit20000 for type1; tint excludes types
// 3/9/5/4/1/8; rider at contain250 slot72. ZH's spawn and pilot tail is absent.
// Accessed prefixes only; these views do not assert complete object extents.
#include "Common/BfmeAudioEventPrefix136.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
extern GameLogic *TheGameLogic;
enum DisabledType { DISABLED_ANY=-1,DISABLED_TYPE0=0,DISABLED_TYPE1=1,DISABLED_EMP=2,DISABLED_HELD=3,
 DISABLED_PARALYZED=4,DISABLED_UNMANNED=5,DISABLED_UNDERPOWERED=6,
 DISABLED_TYPE7=7,DISABLED_TYPE8=8,DISABLED_SCRIPT_DISABLED=9,DISABLED_TYPE10=10,DISABLED_COUNT=11 };
template<int N> class BitFlags { public: bool any() const;unsigned m_words[(N+31)/32]; };
class ModelConditionFlags { public: void rva000B3FA5(int,int); };
class Rva001E4A4E { public: int rva001E4A4E(int); };
class Rva002D9508 { public: void rva002D9508(const void *); };
struct DisabledMiscAudioView {
 char pad[0x40];OpaqueRefElement4 building;char pad44[4];
 OpaqueRefElement4 vehicle;char pad4c[4];OpaqueRefElement4 pilots;
};
class AudioManager { public:
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
 virtual unsigned addAudioEvent(const BfmeAudioEventPrefix136 *);
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
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual const DisabledMiscAudioView *getMiscAudio();
};
extern AudioManager *TheAudio;
struct DisabledThingTemplateView {
 char pad[0x108];unsigned m_kindOf[7];
 __forceinline unsigned testKind(unsigned bit) const {return ((const unsigned char *)m_kindOf)[bit>>3] & (1u<<(bit&7));}
};
class Drawable { public: char pad[0x118];unsigned m_tintStatus; };
class DisabledContainView { public:
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
 virtual Object *friend_getRider();
};
struct ObjectModelBitsView { unsigned words[19];__forceinline unsigned test(unsigned bit) const {return words[bit>>5] & (1u<<(bit&31));} __forceinline void set(unsigned bit){words[bit>>5] |= (1u<<(bit&31));} };
class Object { public:
 void setDisabledUntil(DisabledType,unsigned);
 void rva0028B292(int) const;void rva0028AE6D();void rva0028B8A6(bool);
 __forceinline bool isDisabledByType(DisabledType type) {return (unsigned char)((Rva001E4A4E *)this)->rva001E4A4E(type)!=0;}
 char pad00[4];DisabledThingTemplateView *m_template;
 char pad08[0x38-8];Coord3D m_position;
 char pad44[0x84-0x44];Drawable *m_drawable;
 char pad88[0x10c-0x88];ObjectModelBitsView m_modelFlags;
 char pad158[0x1c8-0x158];BitFlags<11> m_disabledMask;
 unsigned m_disabledTillFrame[11];char pad1f8[0x250-0x1f8];DisabledContainView *m_contain;
};
// ?setDisabledUntil@Object@@QAEXW4DisabledType@@I@Z present-unmatched
void Object::setDisabledUntil(DisabledType type,unsigned frame) {
 if(frame<=TheGameLogic->getFrame()) return;
 bool edgeCase=!m_disabledMask.any();
 if(type<0 || type>=DISABLED_COUNT) return;
 if(type==DISABLED_UNMANNED && !m_template->testKind(73)) {
  BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->pilots,0);
  ((Rva002D9508 *)&sound)->rva002D9508(&m_position);
  TheAudio->addAudioEvent(&sound);
 } else if(type==DISABLED_UNDERPOWERED || type==DISABLED_EMP) {
  if(!(m_disabledMask.m_words[0] & 0x44u)) {
   if(m_template->testKind(7)) {
    BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->building,0);
    ((Rva002D9508 *)&sound)->rva002D9508(&m_position);
    TheAudio->addAudioEvent(&sound);
   } else if(m_template->testKind(11)) {
    BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->vehicle,0);
    ((Rva002D9508 *)&sound)->rva002D9508(&m_position);
    TheAudio->addAudioEvent(&sound);
   }
  }
 }
 if(m_disabledTillFrame[type]!=frame) {
  if(type!=DISABLED_HELD && !isDisabledByType(type)) rva0028B292(1);
  m_disabledTillFrame[type]=frame;
  ((ModelConditionFlags *)&m_disabledMask)->rva000B3FA5(type,frame>TheGameLogic->getFrame());
  if(type==DISABLED_TYPE1 && !m_modelFlags.test(529)) {
   m_modelFlags.set(529);rva0028AE6D();
  }
  if(m_drawable) {
   if(m_disabledMask.any()) {
    if(type!=DISABLED_HELD && type!=DISABLED_SCRIPT_DISABLED && type!=DISABLED_UNMANNED && type!=DISABLED_PARALYZED && type!=DISABLED_TYPE1 && type!=DISABLED_TYPE8) m_drawable->m_tintStatus |= 1u;
   }
  }
  DisabledContainView *contain=m_contain;
  if(contain) {Object *rider=contain->friend_getRider();if(rider) rider->setDisabledUntil(type,frame);}
 }
 if(edgeCase) rva0028B8A6(true);
}
