// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD
// Native51353..514BB RET4 /360B. Primary clean BF1 f989 donor:
// MilesAudioManagerRva006AF840::rva00695B80 (subtitle setup/publish purpose).
// Target separately proves receiverBE8, 6C nonvirtual SubTitleWindow,
// settings94/9C/A0/A4, language font5C/size60/bold64 and display slots16/17.
// Width/height factors are the measured BF63E4/E8/F0/F4 floats; target
// uses isSelectionLocked4253A on the LivingWorldLogic global for the choice.
// FontLibrary2189E1 is independently owned and supplies the real font ABI.
// Constructor260865 RET28 and existing publish260BBF pin establish the
// nonvirtual receiver/argument contracts; the constructor itself is not claimed.
#include "ascii_string.h"
#include "unicode_string.h"
class GameFont;
class FontLibrary {public:GameFont *getFont(const AsciiString *,float,bool);};
extern FontLibrary *TheFontLibrary;
class GlobalLanguage;extern GlobalLanguage *TheGlobalLanguageData;
struct SubtitleFontOptions {char at00[0x5C];AsciiString name;int size;bool bold;};
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
class BfmeSelectionState {public:bool isSelectionLocked()const;};
class Display;extern Display *TheDisplay;
class SubtitleDisplayView {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual unsigned int getWidth();virtual unsigned int getHeight();};
class SubTitleWindow {public:SubTitleWindow(GameFont *,float,float,int,int,int,int);char at00[0x6C];};
class Rva00435A40Sink {public:void publish(const StringBase<unsigned short> &,unsigned int);};
struct SubtitleSettings {char at00[0x94];int m_at94;char at98[4];int m_at9C;int m_atA0;unsigned int m_atA4;};
class MilesAudioManager {public:
 void rva00051353(const UnicodeString &text);
 char at00[0x10];SubtitleSettings *m_settings;char at14[0xBE8-0x14];SubTitleWindow *m_window;
};
void MilesAudioManager::rva00051353(const UnicodeString &text)
{
 if(!m_window) {
  SubtitleFontOptions *options=reinterpret_cast<SubtitleFontOptions *>(TheGlobalLanguageData);
  if(options) {
   GameFont *font=TheFontLibrary->getFont(&options->name,(float)options->size,options->bold);
   float scale=reinterpret_cast<BfmeSelectionState *>(TheLivingWorldLogic)->isSelectionLocked()?0.9765625f:0.8138020634651184f;
   int width=(int)((float)reinterpret_cast<SubtitleDisplayView *>(TheDisplay)->getWidth()*0.4228515625f);
   int height=(int)((float)reinterpret_cast<SubtitleDisplayView *>(TheDisplay)->getHeight()*scale);
   int scaledWidth=(int)((float)reinterpret_cast<SubtitleDisplayView *>(TheDisplay)->getWidth()*0.52734375f);
   m_window=new SubTitleWindow(font,(float)width,(float)height,scaledWidth,m_settings->m_at9C,m_settings->m_at94,m_settings->m_atA0);
  }
 }
 if(m_window)reinterpret_cast<Rva00435A40Sink *>(m_window)->publish(text,m_settings->m_atA4);
}
