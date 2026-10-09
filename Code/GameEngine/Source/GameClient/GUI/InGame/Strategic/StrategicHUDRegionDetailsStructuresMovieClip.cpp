// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /DNDEBUG /MD /EHsc
//
// DoShowProgress: WB161AAB0 names the IconSlot method and assertions290/294
// in this same source. Native5F0A9C..5F0BF2 is342B with two integer arguments.
// The retail primary vtable C78C70 holds it in slot9 (+0x24), between the
// progress flag getter and DoHideProgress; retain its virtual ABI. Slots with
// unknown original spellings are declarations only, not identity claims.
// Slot owner+C, index+10, cached total24/remaining28 and shown2C agree with
// the already matched callbacks/renderer in AptWotrIconSlotCallbacks.cpp.
// Owner level4/name8 are independently witnessed by both format/call sites.
// Build the localized turns text only when cached values differ; show its
// progress state once. Shared string types reproduce all four EH states.
// Reference lanes at verified BFME1 874e38488c yielded no applicable clean
// donor for this BFME2 construction-turns widget. WB strings, retail accesses
// and rowed providers supply the reconstruction; no new pins or lifted code.
//
// StrategicHUD::RegionDetailsStructuresMovieClip (WorldBuilder
// StrategicHUDRegionDetailsStructuresMovieClip.cpp names Impl::Impl).
// Target facts: the owner's ctor 0x005F16F9 (ret 0x10) installs vtable
// 0x00878EFC and builds its Impl (new 0x50) with this and its four
// arguments. The Impl ctor 0x005F141D (ret 0x14, unrowed, pinned) stores
// owner +0x00, level +0x04, the name copy +0x08 and the last word +0x0C,
// builds three name lists, sends SetIconSlotCount with the count and
// reserves and fills that many icon slots. The Impl's callbacks are rowed
// under the address-named view in GameClient/GUI/AptWotrIconSlotCallbacks.cpp.
#include "ascii_string.h"
#include "unicode_string.h"
#include "RegionArmyIconSlotView.h"
#include "Coord2D.h"

namespace StrategicHUD {
class RegionDetailsStructuresMovieClip
{
public:
	class Impl;

	RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg);
	virtual ~RegionDetailsStructuresMovieClip();

private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::RegionDetailsStructuresMovieClip::Impl
{
public:
	Impl(RegionDetailsStructuresMovieClip *owner, int level, const AsciiString &name, int iconSlotCount, int arg); // 0x005F141D (pinned)

public:
	RegionDetailsStructuresMovieClip *m_owner;
 int m_level;
 AsciiString m_name;
 int m_arg;
 AptCommandMapAdder m_commands;char pad1C[0x28-0x1C];char m_custom[12];char pad34[0x50-0x34];
public:
 class IconSlot;
};

StrategicHUD::RegionDetailsStructuresMovieClip::RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg)
	: m_impl(new Impl(this, level, name, iconSlotCount, arg))
{
}

class GameTextInterface {public:
 virtual ~GameTextInterface();
 virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();
 virtual void slot05();virtual void slot06();virtual void slot07();virtual void slot08();
 virtual void slot09();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();
 virtual UnicodeString fetch(const char *,bool *)=0;
};
extern GameTextInterface *TheGameText;
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00525338Fire(void *,void *,const char *,const char *,int *,void *);
class StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot : public Rva005EEF2FBase0,public Rva005EEF2FBase4 {
public:
 IconSlot(Impl*,int);
 virtual ~IconSlot();
 virtual void slot01(int);
 virtual int slot02()const;
 virtual void DoSetState(int);
 virtual void *slot04();
 virtual void slot05(void *);
 virtual unsigned slot06();
 virtual void slot07(void *);
 virtual unsigned char slot08()const;
 virtual void DoShowProgress(int total,int remaining);
 virtual void DoHideProgress();
private:
  Impl *m_owner;
 int m_index;
 void *m_listener;
 int m_state;
 int m_word1C,m_word20;
 int m_total,m_remaining;
 bool m_showProgress,m_turnsRolledOver;
};
void StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot::DoShowProgress(int total,int remaining) {
 if(total!=m_total || remaining!=m_remaining) {
  UnicodeString text;
  if(remaining!=1) {
   bool exists;
   UnicodeString format=TheGameText->fetch("STRATEGICHUD:ConstructionTurnsRemaining",&exists);
   if(exists) text.format(format.str(),remaining);
  } else {
   text=TheGameText->fetch("STRATEGICHUD:ConstructionOneTurnRemaining",0);
  }
  AsciiString key;
  key.format("APT:_level%u.%s_IconSlotTurnsRemaining%d",m_owner->m_level,m_owner->m_name.str(),m_index);
  ((BfmeAptWindowManager *)g_bfmeAptWindowManager)->bfmeSetText(key,text,true);
  m_total=total;
  m_remaining=remaining;
 }
 if(!m_showProgress) {
  Rva00525338Fire(g_bfmeAptWindowManager,(void *)m_owner->m_level,m_owner->m_name.str(),"SetIconSlotProgressState",&m_index,(void *)"_show");
  m_showProgress=true;
 }
}

#pragma pointers_to_members(full_generality, multiple_inheritance)
class Rva005F0CC9 {public:
 void OnIconSlotClicked(const char*);void OnIconSlotRollOver(const char*);void OnIconSlotRollOut(const char*);
 void OnIconSlotTypeRollOver(const char*);void OnIconSlotTypeRollOut(const char*);
 void OnRollOverTurnsRemaining(const char*);void OnRollOutTurnsRemaining(const char*);
 void RenderProgress(const Coord2D*,const Coord2D*,void*,void*);
};
class AptCustomRender;
class AptCustomRenderAdder {public:
 void AddCustomRender(const AsciiString&,AptRef<AptCustomRender>);
};
// IconSlot ctor: WB1619920 source158 independently names the native
// 5F0CC9..5F11D0 RET8 constructor. Primary interface/counting secondary
// base at4 share the proven army-slot header. Target stores establish ownerC,
// index10, listener14, state18, words1C/20, total24/remaining28=-1, flags2C/2D.
// The eight bound rowed callbacks supply identity and their existing ABI.
// Four-part name nodes and the counted functor carrier are existing BFME2
// providers; no applicable clean BFME1/ZH implementation at donor f98983a7d.
// Return the real binding before constructing the argument holder: retail
// reloads owner/adder after holder construction. The helper-on-adder form
// cached that receiver too soon and compiled16 extra bytes. No pins added.
template<class T> static __forceinline FunctorBinding structureBinding(T*target,void(T::*method)(const char*)){FunctorBinding binding(target,method);return binding;}
StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot::IconSlot(Impl*owner,int index)
 :m_owner(owner),m_index(index),m_listener(0),m_state(0),m_word1C(0),m_word20(0),m_total(-1),m_remaining(-1),m_showProgress(false),m_turnsRolledOver(false) {
 AsciiString prefix;prefix.format("_level%u.",m_owner->m_level);
 AsciiString number;number.format("%d",m_index);
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnIconSlotClicked"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnIconSlotClicked)));
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnIconSlotRollOver"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnIconSlotRollOver)));
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnIconSlotRollOut"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnIconSlotRollOut)));
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnIconSlotTypeRollOver"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnIconSlotTypeRollOver)));
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnIconSlotTypeRollOut"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnIconSlotTypeRollOut)));
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnRollOverTurnsRemaining"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnRollOverTurnsRemaining)));
 m_owner->m_commands.AddCommandMap(prefix+m_owner->m_name+"_OnRollOutTurnsRemaining"+number,AptRef<AptCommandMap>(structureBinding((Rva005F0CC9*)this,&Rva005F0CC9::OnRollOutTurnsRemaining)));
 ((AptCustomRenderAdder*)m_owner->m_custom)->AddCustomRender(prefix+m_owner->m_name+"_RenderProgress"+number,AptRef<AptCustomRender>(structureBinding((Rva005F0CC9*)this,reinterpret_cast<void(Rva005F0CC9::*)(const char*)>(&Rva005F0CC9::RenderProgress))));
}
typedef char StructuresIconSlotIs48[sizeof(StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot)==48 ? 1 : -1];
