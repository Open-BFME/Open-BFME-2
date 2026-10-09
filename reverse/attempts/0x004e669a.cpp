// ??0Impl@PlaceTerrainResourceClaimantFeedback@@QAE@PAXPAUFeedbackParams@@PAVBFMERopeDrawable@@PAUFeedbackData@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /Oy /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class GameFont;
class FontLibrary {public: GameFont *getFont(const AsciiString*,float,bool);};
extern FontLibrary *TheFontLibrary;
class FeedbackDisplayString {public: virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void setFont(GameFont*);virtual void s1C();virtual void s20();virtual void s24();virtual void setColor(unsigned,unsigned);};
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
class FeedbackManager {public: virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual void s34();virtual FeedbackDisplayString *newDisplayString();};
struct FeedbackParams {AsciiString sound,font;int size;bool bold;char padD[3];int color;};
class BFMERopeDrawable;
struct FeedbackData;
void GameGetColorComponents(int,unsigned char*,unsigned char*,unsigned char*,unsigned char*);
struct ICoord2D {int x,y; ICoord2D(int xx,int yy):x(xx),y(yy){} };
class PlaceTerrainResourceClaimantFeedback {public: class Impl;};
class PlaceTerrainResourceClaimantFeedback::Impl {
 void *m00; FeedbackParams *m04; BFMERopeDrawable *m08; FeedbackData *m0C; FeedbackDisplayString *m10; ICoord2D position;void *decal;
 public: Impl(void*,FeedbackParams*,BFMERopeDrawable*,FeedbackData*);void createPotentialClaimDecal();
};
PlaceTerrainResourceClaimantFeedback::Impl::Impl(void *owner,FeedbackParams *params,BFMERopeDrawable *drawable,FeedbackData *data):m10(0),position(-1,-1) {
 m00=owner;m04=params;m08=drawable;m0C=data;decal=0;
 m10=((FeedbackManager*)TheDisplayStringManager)->newDisplayString();
 GameFont *font=TheFontLibrary->getFont(&m04->font,(float)m04->size,m04->bold);
 if(font) m10->setFont(font);
 unsigned char r,g,b,a;
 GameGetColorComponents(m04->color,&r,&g,&b,&a);
 m10->setColor(m04->color,(unsigned)a<<24);
 createPotentialClaimDecal();
}
