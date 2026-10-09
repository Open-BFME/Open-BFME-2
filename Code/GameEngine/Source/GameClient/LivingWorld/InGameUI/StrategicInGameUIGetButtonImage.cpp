// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /DNDEBUG /arch:SSE
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
class Image;
class ImageCollection {public:const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
class ThingFactory;
extern ThingFactory *TheThingFactory;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002D06CA {public:void *rva002D06CA(const AsciiString *);};
class ThingTemplate {public:const Image *getButtonImage();const Image *rva0033BA46();};
class Rva002E2903Player;
class Rva002BA8F1Logic {public:Rva002E2903Player *find(int,unsigned int *);};
class Rva002E06B8 {public:void *rva002E06EF();};
class CreateAHeroHero;
class CreateAHeroManager {public:const AsciiString &GetButtonImageName(const CreateAHeroHero *);};
extern CreateAHeroManager *TheCreateAHeroManager;
struct StrategicButtonImageView { int unknown;AsciiString templateName; };
namespace StrategicInGameUI {
const Image *GetButtonImage(const StrategicButtonImageView *view,int playerID) {
 static const Image *noArtImage=TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
 const AsciiString &name=view->templateName;
 const Image *image=noArtImage;
 if(!((const StringBase<char> *)&name)->isEmpty()) {
  ThingTemplate *definition=(ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name);
  if(definition) {
   image=definition->getButtonImage();
   if(!image) image=definition->rva0033BA46();
   if(((const unsigned char *)definition)[0x11f]&0x40) {
    Rva002E2903Player *player=((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerID,0);
    if(player) {
     const CreateAHeroHero *hero=(const CreateAHeroHero *)((Rva002E06B8 *)player)->rva002E06EF();
     if(hero) image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName(hero));
    }
   }
  }
 }
 return image ? image : noArtImage;
}
}
