// ?rva0057ABD0@ChecklistUIImpl@StrategicHUD@@QBEMXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc
class Rva004987FEFloatField {public: float get() const;};
class Rva0057A24A {public: float rva0057A24A() const;};
extern unsigned g_Va00E06360;
struct ChecklistHeightItem {char prefix[0x38];float top;};
struct ChecklistHeightNode {ChecklistHeightNode* next,*prev;ChecklistHeightItem* item;};
namespace StrategicHUD {class ChecklistUIImpl {public: char prefix[0x30];ChecklistHeightNode *items;float rva0057ABD0() const;};}
float StrategicHUD::ChecklistUIImpl::rva0057ABD0() const
{
 if(items->next!=items) {
  ChecklistHeightItem *last=items->prev->item;
  float top=last->top;
  return reinterpret_cast<Rva004987FEFloatField*>(reinterpret_cast<char*>(last)+8)->get()
    + reinterpret_cast<Rva0057A24A*>(&g_Va00E06360)->rva0057A24A() + top;
 }
 return reinterpret_cast<Rva0057A24A*>(&g_Va00E06360)->rva0057A24A();
}
