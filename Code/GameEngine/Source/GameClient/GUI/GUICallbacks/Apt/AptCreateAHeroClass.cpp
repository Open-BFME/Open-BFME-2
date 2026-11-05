// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /O1 /G7 /arch:SSE
// WB157C640 names Class::CreateDefaultHeroes; native5B566B..5B576B
// independently establishes the behavior and offsets. Retain a neutral
// target method spelling while the weak WB string association is unresolved.
#include "ascii_string.h"
#include "unicode_string.h"

class CreateAHeroData;
class Rva00219251 { public:
 CreateAHeroData *rva00219251(int,int,int,const UnicodeString &,int,int,int);
};
class CreateAHeroHero { public: bool SetDefaultColors(); };
class ModuleData;
class Rva00423A68 { public: void rva00423A68(const ModuleData *); };
#include "../../../../../Include/Common/Rva00222A8BTarget.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
class CreateAHeroData;
class Rva0040A3D2 { public: CreateAHeroData *rva0040A3D2(int, int); };
#include "../../../../../Include/GameClient/AptMyHero.h"
struct ClassScreenPrefix { char prefix[0x27C]; AptMyHero hero; };

struct Rva005B566BClassEntry { char bytes[32]; };
struct Rva005B566BClassVector {
 Rva005B566BClassEntry *start,*finish,*end;
 __forceinline unsigned int size() const { return finish-start; }
};
class CreateAHeroManager {
public:
 int rva00219D52(unsigned int);
 const AsciiString &GetClassImageName(unsigned int);
 const AsciiString &GetButtonImageName(unsigned, unsigned);
 const AsciiString &GetClassDescTag(unsigned);
 const AsciiString &GetSubClassDescTag(unsigned, unsigned);
 char pad[0x14C];
 Rva005B566BClassVector classes;
};
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva005B566B {
public: void rva005B566B(); void rva005B54ED(unsigned, unsigned, bool);
private:
 char pad[4];
 ClassScreenPrefix *screen;
 char gap[0x1C - 8];
 Rva00423A68 heroes;
};
void Rva005B566B::rva005B566B()
{
 if (!TheCreateAHeroManager) return;
 unsigned int count=TheCreateAHeroManager->classes.size();
 for (unsigned int i=0;i<count;++i) {
  unsigned int subCount=TheCreateAHeroManager->rva00219D52(i);
  for (unsigned int j=0;j<subCount;++j) {
   CreateAHeroData *hero=reinterpret_cast<Rva00219251 *>(TheCreateAHeroManager)->rva00219251(
     0,i,j,UnicodeString::TheEmptyString,-1,0xFF707070,-1);
   reinterpret_cast<CreateAHeroHero *>(hero)->SetDefaultColors();
   heroes.rva00423A68(reinterpret_cast<const ModuleData *>(hero));
  }
  AsciiString image(TheCreateAHeroManager->GetClassImageName(i));
  AsciiString key;
  key.format("Cah::ClassIcon%d",i);
  reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva002239FA(key,image);
 }
}

// Native5B54ED..5B566B,382B RET12: update the hero, subclass icons and
// class/subclass descriptions. WB157C3E0 names Class::SetCurrentHero;
// the existing receiver and provider spellings are retained.
// Bind the returned text by const reference. The identical call arms keep
// minor live through text construction, preserving retail's temporary homes.
static __forceinline void SetTypeDescription(const AsciiString &key,
    const UnicodeString &value, unsigned minor)
{
    (minor ? g_bfmeAptWindowManager->bfmeSetText(key, value, true)
           : g_bfmeAptWindowManager->bfmeSetText(key, value, true));
}

void Rva005B566B::rva005B54ED(unsigned major, unsigned minor, bool animate)

{
 CreateAHeroData *hero = reinterpret_cast<Rva0040A3D2 *>(&heroes)->rva0040A3D2(major, minor);
 if (!hero)
 return;
 screen->hero.rva005B21DA(hero, true, animate ? 1 : 0);
 unsigned count = TheCreateAHeroManager->rva00219D52(major);
 for (unsigned i = 0; i < count; ++i)
 {
  const AsciiString &image = TheCreateAHeroManager->GetButtonImageName(major, i);
  AsciiString key;
  key.format("Cah::TypeIcon%d", i);
  reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva002239FA(key, image);

 }

 {
  AsciiString key("APT:CahClassDescription");
  g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch(TheCreateAHeroManager->GetClassDescTag(major)), true);

 }

 {
  AsciiString key("APT:CahTypeDescription");
  SetTypeDescription(key,TheGameText->fetch(TheCreateAHeroManager->GetSubClassDescTag(major,minor)),minor);

 }

}
