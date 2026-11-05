// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
template<int N> class MovieSlots:public MovieSlots<N-1>{public:virtual void gap(char(*)[N]);};
template<> class MovieSlots<0>{};
class SubTitleManager;
struct MovieSubtitle {char unknown[0x18];SubTitleManager *font;};
class MovieStream:public MovieSlots<14>{public:virtual bool start(void*);char pad4[4];MovieSubtitle *subtitles;int unknownC;void(__cdecl *callback)(int);};
class VideoPlayerInterface:public MovieSlots<17>{public:virtual MovieStream *open(AsciiString,int);};
extern VideoPlayerInterface *TheVideoPlayer;
#include "../../Include/GameClient/Display.h"
class BfmeSelectionState {public:bool isSelectionLocked()const;};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Object;
class ObjectLookupMap
{
public:
	Object**findSlot(int*);
};
extern unsigned g_Va00E04938;
void Rva00524CC6(int);
extern const float MovieSubtitleXScale, MovieSubtitleYScale, MovieSubtitleNormalWidth,MovieSubtitleLockedWidth;
extern const int MovieSubtitleDrawWord0,MovieSubtitleDrawWord1,MovieSubtitleDrawWord2;
class PlaybackOpenVirtualView:public MovieSlots<9>{public:virtual void clearMovie();virtual void refresh();};
// ??0MovieWindowPlayback@@QAE@XZ @0x00524B7A 58B
// Ctor with explicit vtable in the middle via single-class model plus
// baseConstruct through a cast. Calls rowed base 0x001B4E63; sole caller
// Locomotor 0x005C9716 at +0x218. Single-class keeps source order per
// Rva005A7A90Ctor precedent. Honest owner.
extern "C" const void *const __identifier("??_7Rva00524BB4@@6B@")[];

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class MovieWindowPlayback
{
public:
	MovieWindowPlayback();
 void OpenMovie(const AsciiString &,int);
 void clear(); // 0x00524A4C (Rva00524A4CClear.cpp)

private:
	void *m_vtable;
	char m_basePad[8];
	MovieStream *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
};
MovieWindowPlayback::MovieWindowPlayback()
{
	reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface();
	m_24 &= 0xF8;
	m_28 = -1;
	m_0C = 0;
	m_20 = 0;
	m_2C = 0;
	m_30 = 0;
	m_vtable = (void *)__identifier("??_7Rva00524BB4@@6B@");
	_ReadWriteBarrier();
	m_34 = 0;
	m_38 = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}
// WB MovieWindowPlayback.cpp:219..242 and native 524D01..524E95 establish
// OpenMovie, video/subtitle setup, lookup registration, callback and flags.
// Copy the movie name by value as the verified Display opener does; the
// virtual callee owns that argument. The three draw words are integers.
void MovieWindowPlayback::OpenMovie(const AsciiString &name,int value){
 ((PlaybackOpenVirtualView*)this)->clearMovie();m_24&=0xfb;m_28=-1;m_20=value;
 m_0C=TheVideoPlayer->open(name,value&0x40);
 if(!m_0C)return;
 if(m_0C->subtitles && m_0C->subtitles->font){
  float width=((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked()?MovieSubtitleLockedWidth:MovieSubtitleNormalWidth;
  int subtitleY=(int)(TheDisplay->getWidth()*MovieSubtitleYScale);
  int subtitleWidth=(int)(TheDisplay->getHeight()*width);
  int subtitleX=(int)(TheDisplay->getWidth()*MovieSubtitleXScale);
  TheDisplay->slot28(m_0C->subtitles->font,(float)subtitleY,(float)subtitleWidth,subtitleX,MovieSubtitleDrawWord0,MovieSubtitleDrawWord1,MovieSubtitleDrawWord2);
 }
 MovieStream *playing=m_0C;
 if(!playing->start(TheDisplay->createVideoBuffer((value&0x40)!=0))){clear();return;}
 value=(int)m_0C;
 *((ObjectLookupMap*)&g_Va00E04938)->findSlot(&value)=(Object*)this;
 m_0C->callback=Rva00524CC6;
 m_24=(m_24&0xfd)|1;
 ((PlaybackOpenVirtualView*)this)->refresh();
}
