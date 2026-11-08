// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /DNDEBUG /arch:SSE
// stlport
// WB 0x016150C0 names StrategicInGameUI::GetButtonImage and supplies its
// template/hero image selection purpose (StrategicInGameUIGetButtonImage.cpp
// assertions 36/39). Native 0x005F0383..0x005F0473 is the complete 240B cdecl
// body: input name at +4, player ID as the second argument and kind bit190.
// Input record type remains a TU-scoped target access view. Provider spellings
// retain their existing byte-verified names; no canonical layout is asserted.
// Native's local-static guard and EH states require a dynamic cache initializer
// with a temporary AsciiString, rather than a manually simulated init flag.
// No compatible clean BFME1/ZH GetButtonImage implementation was available at
// reference pointer 0bef414b52; target WB and retail supply this reconstruction.
#include "ascii_string.h"
#include "../../../../Include/GameClient/Image.h"
class ThingTemplate;
class ThingFactory;
extern ThingFactory *TheThingFactory;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../../../Include/Common/ThingFactory.h"
#include "../../../../Include/Common/ThingTemplate.h"
class Rva002E2903Player;
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../../../Include/GameLogic/LivingWorldPlayer.h"
class CreateAHeroHero;
#include "../../../../Include/GameLogic/CreateAHeroManager.h"
// Retail .CRT$XCU 0x007B521B is this unit's Drawable.h copy (static 0x00E068D0).
#include "../../../../Include/GameClient/Drawable.h"
extern CreateAHeroManager *TheCreateAHeroManager;
struct StrategicButtonImageView { int unknown;AsciiString templateName; };
namespace StrategicInGameUI {
const Image *GetButtonImage(const StrategicButtonImageView *view,int playerID) {
 static const Image *noArtImage=TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
 const AsciiString &name=view->templateName;
 const Image *image=noArtImage;
 if(!((const StringBase<char> *)&name)->isEmpty()) {
  ThingTemplate *definition=(ThingTemplate *)TheThingFactory->findTemplate(name);
  if(definition) {
   image=definition->getButtonImage();
   if(!image) image=definition->rva0033BA46();
   if(((const unsigned char *)definition)[0x11f]&0x40) {
    Rva002E2903Player *player=((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerID,0);
    if(player) {
     const CreateAHeroHero *hero=(const CreateAHeroHero *)((LivingWorldPlayer *)player)->rva002E06EF();
     if(hero) image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName(hero));
    }
   }
  }
 }
 return image ? image : noArtImage;
}
}
