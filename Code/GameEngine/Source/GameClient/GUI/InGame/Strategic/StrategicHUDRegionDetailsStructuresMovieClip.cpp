// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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
 char m_data10[0x50-0x10];
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
class StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot {
public:
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
 char pad04[0xc-4];
 Impl *m_owner;
 int m_index;
 void *m_listener;
 int m_state;
 char pad1c[0x24-0x1c];
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
