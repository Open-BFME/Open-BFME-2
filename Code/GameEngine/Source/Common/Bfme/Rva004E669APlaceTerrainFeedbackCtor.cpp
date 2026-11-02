// cl: /O1 /Oy /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// PlaceTerrainResourceClaimantFeedback::Impl constructor (retail 0x004E669A,
// 171B): stores the four caller arguments, creates the claimant display
// string through the display-string manager vslot 14, applies the params
// font/colour, then builds the potential-claim decal (rowed 0x004E65CF).
// Codegen: retail stores the arguments in declaration order ahead of the
// ICoord2D(-1,-1) and decal members, so every member is initialised in the
// mem-init list; assigning m00..m0C in the body moves them behind position.
#include "PlaceTerrainResourceClaimantFeedbackView.h"
class GameFont;
#include "../../../Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;
class FeedbackDisplayString {public: virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void setFont(GameFont*);virtual void s1C();virtual void s20();virtual void s24();virtual void setColor(unsigned,unsigned);};
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
class FeedbackManager {public: virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual void s34();virtual FeedbackDisplayString *newDisplayString();};
void GameGetColorComponents(int,unsigned char*,unsigned char*,unsigned char*,unsigned char*);
PlaceTerrainResourceClaimantFeedback::Impl::Impl(PlaceTerrainResourceClaimantFeedback *owner,FeedbackParams *params,Drawable *drawable,const TerrainResourceBehaviorModuleData *data):m00(owner),m04(params),m08(drawable),m0C(data),m10(0),position(-1,-1),decal(0) {
 m10=((FeedbackManager*)TheDisplayStringManager)->newDisplayString();
 GameFont *font=TheFontLibrary->getFont(&m04->font,(float)m04->size,m04->bold);
 if(font) m10->setFont(font);
 unsigned char r,g,b,a;
 GameGetColorComponents(m04->color,&r,&g,&b,&a);
 m10->setColor(m04->color,(unsigned)a<<24);
 createPotentialClaimDecal();
}
