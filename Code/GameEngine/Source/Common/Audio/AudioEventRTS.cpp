// cl: /O1
// Audio/AudioEventRTS.cpp: three address-named forwarders retail links from this
// TU (tu_map approved by address contiguity), folded from split units with
// these exact flags, in retail order.

// ?rva002D9AD4@Rva002D9AD4@@QAEAAVBfmePoolRef10@@ABV2@@Z @ 0x002D9AD4 8B
// Tail-jmp assign forwarder: return m_pool = other where m_pool is BfmePoolRef10 at +0x10.
// Evidence: honest address name; add ecx 0x10 jmp to rowed ??4BfmePoolRef10@@QAEAAV0@ABV0@@Z; callers in FUN_0045a451 and FUN_0045dd40; neighbours BfmeStringTailRecord144 dtor and CDManager getPath.
class BfmePoolRef10
{
public:
	BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
};
class Rva002D9AD4
{
public:
	BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other);
	char m_pad[0x10];
	BfmePoolRef10 m_pool;
};
BfmePoolRef10 &Rva002D9AD4::rva002D9AD4(const BfmePoolRef10 &other)
{
	return m_pool = other;
}

// ?rva002D9BDC@Rva002D9BDC@@QAEXMM@Z @ 0x002D9BDC 43B
// Evidence: honest address method; thiscall void(float float) ret 8; member float at +0x64 clamped via rowed clamp<float>(lo val hi); callers at 0x0005AAC2 0x0005D60F; neighbours AsciiStringRvoGetters and Rva002D9C2FAssign.
template <class NUM>
NUM clamp(NUM lo, NUM val, NUM hi);

class Rva002D9BDC
{
	char m_pad[0x64];
	float m_64;

public:
	void rva002D9BDC(float lo, float hi);
};

void Rva002D9BDC::rva002D9BDC(float lo, float hi)
{
	m_64 = clamp(lo, m_64, hi);
}

// ?rva002D9C2F@Rva002D9C2F@@QAEAAUOpaqueRefElement4@@ABU2@@Z @ 0x002D9C2F 8B
// Tail-jmp assign forwarder: return m_ref = other where m_ref is OpaqueRefElement4 at +8.
// Evidence: honest address name; add ecx 8 jmp to rowed ??4OpaqueRefElement4@@QAEAAU0@ABU0@@Z; callers in FUN_0045a451 and others; neighbours CDManager getPath and BfmeStringTailRecord144 deleting dtor.
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
class Rva002D9C2F
{
public:
	OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other);
	char m_pad[8];
	OpaqueRefElement4 m_ref;
};
OpaqueRefElement4 &Rva002D9C2F::rva002D9C2F(const OpaqueRefElement4 &other)
{
	return m_ref = other;
}

// ?rva002D9AC3@Rva002D9AC3@@QAEPBDXZ @ 0x002D9AC3 17B
// Honest address-named thiscall getter: if ptr at +8 is null return empty
// string else return ptr+8. Evidence: 17B shape mov eax [ecx+8] test je
// add 8 ret mov empty ret; compiler empty-string literal; callers at
// 0x00054777 0x000547BC 0x00055ED8 0x00055F5E 0x0005BC43 0x002D9D8D;
// neighbours 0x002D9A43 dtor and 0x002D9AD4 forwarder in this TU.
class Rva002D9AC3
{
public:
	const char *rva002D9AC3();
	char m_pad[8];
	char *m_ptr;
};

const char *Rva002D9AC3::rva002D9AC3()
{
	if (m_ptr != 0)
		return m_ptr + 8;
	return "";
}

#include "../GameLogicObjectLookupView.h"
// Native2D9C7A..2D9D39 no-arg getter. Event fields34/38/70 and all
// accessed result fields below are native evidence. WorldBuilder BD6820
// corroborates the owner/player lookup; world-provider names remain opaque.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class Rva002BFDAE {public: void *rva002BFDAE(void *);};
struct Rva002B488EResult {char unknown[0x54]; int value54;};
struct Rva002B2579Result;
class Rva002BA8F1Logic {public: Rva002B488EResult *rva002B488E(int);Rva002B2579Result *rva002B2579(int);};
struct Rva002BFF5AData {char unknown[0x10]; int key;};
class Rva0035C95FView {public: const Rva002BFF5AData *rva0035C95F() const; void *head;};
struct Rva002D9C7AEntry {char unknown[8]; Rva0035C95FView version; char unknown0c[4]; unsigned int key10;};
class Rva004E06FBPtrChase32Field {public: int get() const;};
struct Rva002D9C7ASecond {char unknown[0x38]; Rva004E06FBPtrChase32Field *value38;};
unsigned int __cdecl Rva00318D4E(unsigned int);
unsigned int __cdecl Rva0052B225(unsigned int);

class GameClient {public:
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
 virtual Drawable *findDrawableByID(int);
};
extern GameLogic *TheGameLogic;
class ClientFrameSubsystem;
extern ClientFrameSubsystem *TheGameClient;

class Rva002DA318 {
 char m_pad00[0x34];
 int m_id34;
 int m_tag38;
public:
 bool rva002DA318();
};
bool Rva002DA318::rva002DA318() {
 switch(m_tag38) {
 case 1: return ((GameClient *)TheGameClient)->findDrawableByID(m_id34) == 0;
 case 2: return TheGameLogic->findObjectByID((ObjectID)m_id34) == 0;
 case 3: return g_00DFEF18 && ((Rva002BFDAE *)g_00DFEF18)->rva002BFDAE((void*)m_id34) ? 0 : 1;
 case 4: return TheLivingWorldLogic && ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B488E(m_id34) ? 0 : 1;
 case 5: return TheLivingWorldLogic && ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B2579(m_id34) ? 0 : 1;
 }
 return false;
}

class Rva002D9C7A {
 char unknown[0x34];
 int m_id34;
 int m_tag38;
 char unknown3c[0x70-0x3c];
 int m_value70;
public:
 int rva002D9C7A();
};
int Rva002D9C7A::rva002D9C7A() {
 if(m_value70 != -1) return m_value70;
 switch(m_tag38) {
 case 3:
  if(g_00DFEF18 && TheLivingWorldLogic) {
   Rva002D9C7AEntry *entry=(Rva002D9C7AEntry *)((Rva002BFDAE *)g_00DFEF18)->rva002BFDAE((void*)m_id34);
   if(entry) {
    switch(entry->version.rva0035C95F()->key) {
    case 0:
     if(entry->key10) {
      Rva002B488EResult *value=(Rva002B488EResult *)Rva00318D4E(entry->key10);
      if(value) return value->value54;
     }
     break;
    case 4:
     if(entry->key10) {
      Rva002D9C7ASecond *value=(Rva002D9C7ASecond *)Rva0052B225(entry->key10);
      if(value && value->value38) return value->value38->get();
     }
     break;
    }
   }
  }
  break;
 case 4:
  if(TheLivingWorldLogic) {
   Rva002B488EResult *value=((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B488E(m_id34);
   if(value) return value->value54;
  }
  break;
 case 5:
  if(TheLivingWorldLogic) {
   Rva002B2579Result *value=((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B2579(m_id34);
   if(value) return ((Rva004E06FBPtrChase32Field *)value)->get();
  }
  break;
 }
 return -1;
}
