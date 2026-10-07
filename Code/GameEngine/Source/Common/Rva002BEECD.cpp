// cl: /O1 /arch:SSE /G7 /MD
// Native 002BEECD..002BEF29 RET4: category 7 accepts any subject category;
// flag +4 with category 0 additionally tests the subject's +10 lookup ID
// against LivingWorldLogic's +98 context. The receiver identity is open.
// The existing folded OVERRIDE getter is used as its pointer-chain ABI;
// this does not identify the subject's template as a LocomotorTemplate.
class LocomotorTemplate;
template<class T> class OVERRIDE
{
public:
 const T *operator->() const;
private:
 const T *head;
};
struct Rva002BEECDCategory { char pad[0x10]; int category; };
struct Rva002BEECDSubject
{
 char pad[8];
 OVERRIDE<LocomotorTemplate> templateView;
 unsigned unused;
 unsigned lookupID;
};
struct Rva00318CEBOther;
class Rva00318CEB { public: bool rva00318CEB(const Rva00318CEBOther *other); };
unsigned Rva00318D4E(unsigned key);
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002BEECDLogicView { char pad[0x98]; const Rva00318CEBOther *context; };
class Rva002BEECD
{
public:
 bool rva002BEECD(Rva002BEECDSubject *subject);
private:
 int m_category;
 bool m_contextOnly;
};

bool Rva002BEECD::rva002BEECD(Rva002BEECDSubject *subject)
{
 int category = m_category;
 if (category != 7 && ((const Rva002BEECDCategory *)subject->templateView.operator->())->category != category)
  return false;
 if (m_contextOnly && category == 0)
 {
  if (subject->lookupID == 0)
   return false;
  Rva00318CEB *owner = (Rva00318CEB *)Rva00318D4E(subject->lookupID);
  if (owner == 0 || !owner->rva00318CEB(((Rva002BEECDLogicView *)TheLivingWorldLogic)->context))
   return false;
 }
 return true;
}
