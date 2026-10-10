// ?UpdateNotice@InGameNotificationBoxMovieClip@@QAEXXZ
// partial score=0.9957343321965674 date=2026-10-10
// ?UpdateNotice@InGameNotificationBoxMovieClip@@QAEXXZ
// partial score=0.985 date=2026-10-10
// ?UpdateNotice@InGameNotificationBoxMovieClip@@QAEXXZ
// partial score=0.96 date=2026-10-09
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include <math.h>
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// Notification-box ownership transfer: native004E6BF6..004E6C34 RET4;
// WorldBuilder013238A0 returns a consuming holder through a hidden result.
// Rva004E6A1D clear and Rva004E6A37 destructor/assignment establish the
// existing owner spellings. Copy empties its source before publishing the
// pointer; the returned holder has the independently rowed destructor.
// The original method name is unproven; preserve a neutral address name.
class Image;
class Rva004E6935 {public:
 UnicodeString title;
 const Image *icon;
 OpaqueRefElement4 audio;
 UnicodeString label;
 void *font;
 int color;
 unsigned unknown18;
 bool openOption;
 unsigned char unknown1D[3];
 int location;
 ~Rva004E6935();
};
class Rva004E6A37 {
public:
 Rva004E6935 *m_ptr;
 Rva004E6A37(Rva004E6935 *p=0):m_ptr(p) {}
 __forceinline Rva004E6935 *release() { Rva004E6935 *p=m_ptr; m_ptr=0; return p; }
 Rva004E6A37(Rva004E6A37 &v) { Rva004E6935 *p=v.m_ptr; v.m_ptr=0; m_ptr=p; }
 ~Rva004E6A37();
 Rva004E6A37 &operator=(Rva004E6A37);
};
class Rva004E6A1D {
public:
 Rva004E6935 *m_ptr;
 __forceinline Rva004E6935 *get()const{return m_ptr;}
 void clear();
 Rva004E6A37 rva004E6BF6();
};
class Rva00222A8BTarget {public:
 int invoke(void*,const char*,int,const char*,void*,void*,void*,void*);
};
AsciiString Rva002228E8Get(float);
char **Rva004E678BGet(char**,bool);
static __forceinline int invokeFormatted(Rva00222A8BTarget *target,void *owner,const char *method,
 const AsciiString &number,const bool *flag,const char *const *location, char **flagText)
{
 const char *place=*location;
 char *value=*Rva004E678BGet(flagText,*flag);
 return target->invoke(owner,method,3,number.str(),value,const_cast<char*>(place),0,0);
}

inline __declspec(noinline) int Rva004E697DCall(Rva00222A8BTarget *target,void *owner,const char *method,
 const float *height,const bool *flag,const char *const *location)
{
 char *flagText;
 return invokeFormatted(target,owner,method,Rva002228E8Get(*height),flag,location,&flagText);
}

static __forceinline void consumeNotice(Rva004E6A37 &destination, const Rva004E6A37 &source)
{
 destination=Rva004E6A37(const_cast<Rva004E6A37 &>(source).release());
}
static __forceinline void openNotice(Rva00222A8BTarget *target, void *const &owner,
 const float &height, const bool *option, const char *const *location)
{
 Rva004E697DCall(target,owner,"Open",&height,option,location);
}
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
void Rva004E6816Fire(Rva00222A8BTarget*,void*,const char*,bool*);
class Rva00524306 {public:
 void *begin,*end;
 void rva00524725(const AsciiString&,const Image*);
};
class NotificationDisplayQuery {public:
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
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
virtual bool query88();
};
class Display;extern Display *TheDisplay;
class NotificationAptScales {public:
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
virtual const float *getScale15();
virtual const float *getScale16();
};
class NotificationAudioSlots {public:
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
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
virtual void addAudioEvent(BfmeAudioEventPrefix136*);
};
class AudioManager;extern AudioManager *TheAudio;
class NotificationTextSurface {public:
 virtual void slot0();
 virtual void setText(UnicodeString);
 virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();
 virtual void setFont(void*);
 virtual void slot7();
 virtual void setWidth(int);
 virtual void setCenter(bool);
 virtual void setColor(int,int);
 virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();
 virtual void getSize(int*,int*);
};
class InGameNotificationBoxMovieClip {public:
 void UpdateNotice();void CloseImmediately();
 char unknown00[4];void *owner;int state;
 char unknown0C[0x30-0x0c];
 Rva00524306 images;
 char unknown38[4];float widthScale;
 Rva004E6A1D pending;
 Rva004E6A37 active;
 char unknown48[4];NotificationTextSurface *surface;
 char unknown50;bool iconVisible;
};
static const char *const noticeLocations[3]={"main","spellStore","objectives"};
void InGameNotificationBoxMovieClip::UpdateNotice()
{
 if(widthScale<=0.0f || !pending.m_ptr->font || reinterpret_cast<NotificationDisplayQuery*>(TheDisplay)->query88()){
  CloseImmediately();return;
 }
 Rva004E6A1D &notice=pending;
 AsciiString titleKey;
 titleKey.format("APT:_level%u_Title",owner);
 g_bfmeAptWindowManager->bfmeSetText(titleKey,notice.get()->title,true);
 bool shown=notice.get()->icon!=0;
 if(shown!=iconVisible){
  Rva004E6816Fire(reinterpret_cast<Rva00222A8BTarget*>(g_bfmeAptWindowManager),owner,"SetIconVisibility",&shown);
  iconVisible=shown;
 }
 if(*reinterpret_cast<const volatile unsigned char*>(&shown)){
  AsciiString iconKey;
  iconKey.format("_level%u_Icon",owner);
  images.rva00524725(iconKey,notice.get()->icon);
 }
 surface->setFont(notice.get()->font);
 surface->setText(notice.get()->label);
 surface->setColor(notice.get()->color,0);
 surface->setCenter(true);
 {
 float pixels=(float)floor(*reinterpret_cast<NotificationAptScales*>(g_bfmeAptWindowManager)->getScale15()*widthScale+0.5f);
 int pixelCount;
 __asm { fld pixels
 fistp pixelCount }
 surface->setWidth(pixelCount);
 }
 if(notice.get()->audio.referent){
  BfmeAudioEventPrefix136 sound(notice.get()->audio,2);
  reinterpret_cast<NotificationAudioSlots*>(TheAudio)->addAudioEvent(&sound);
 }
 int w,h;
 surface->getSize(&w,&h);
 openNotice(reinterpret_cast<Rva00222A8BTarget*>(g_bfmeAptWindowManager),owner,(float)h*reinterpret_cast<NotificationAptScales*>(g_bfmeAptWindowManager)->getScale16()[1],&notice.get()->openOption,&noticeLocations[notice.get()->location]);
 state=2;
 consumeNotice(active,notice.rva004E6BF6());
}

static __forceinline int invokeFormatted(Rva00222A8BTarget *target,void *owner,const char *method,
 const AsciiString &number,const bool *flag,const char *const *location, char **flagText)
{
 const char *place=*location;
 char *value=*Rva004E678BGet(flagText,*flag);
 return target->invoke(owner,method,3,number.str(),value,const_cast<char*>(place),0,0);
}

inline __declspec(noinline) int Rva004E697DCall(Rva00222A8BTarget *target,void *owner,const char *method,
 const float *height,const bool *flag,const char *const *location)
{
 char *flagText;
 return invokeFormatted(target,owner,method,Rva002228E8Get(*height),flag,location,&flagText);
}
