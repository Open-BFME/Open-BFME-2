// cl: /MD
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
