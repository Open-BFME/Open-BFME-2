#pragma once
// Target WinInstanceData: ctor32225A installs C0D830; one virtual dtor slot.
// GameWindow member30..1D7 and last ctor word1A4 prove extent1A8; init322174 stores every named field.
// Zero Hour WinInstanceData.h names the fields; unknown storage stays opaque.
#include "WinDrawData.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class GameWindow;
class GameFont;
class DisplayString;
class VideoBuffer;
class UnicodeString;

// Text colours of one window state. Layout: two dwords, read as a pair by the matched text-colour rows
// of GameWindowManagerScript.cpp (+15C/+164/+16C below). Names: Zero Hour WinInstanceData.h.
struct TextDrawData
{
 int color;
 int borderColor;
};

class WinInstanceData
{
public:
 WinInstanceData();
 virtual ~WinInstanceData();
 void init();
 void setTooltipText(UnicodeString tip);
 void setText(UnicodeString text);
 UnicodeString getTooltipText();
 UnicodeString getText();
 int getTextLength();
 int getTooltipTextLength();
 unsigned int getStyle() { return m_style; }
 unsigned int getStatus() { return m_status; }
 unsigned int getState() { return m_state; }
 GameWindow *getOwner() { return m_owner; }
 GameFont *getFont() { return m_font; }
 WinInstanceData &operator=(const WinInstanceData &); // row 0x00313EBD copies field by field
 int m_id; // +04, GameWindow::winSetWindowId at 0x0031404A
 unsigned int m_state; // +08, init store; GadgetCheckBoxIsChecked 0x00327B33 tests it with shr
 unsigned int m_style; // +0C
 unsigned int m_status; // +10, init store
 GameWindow *m_owner; // +14, init store
 // init at 0x00322174 and the nine rowed GameWindow draw-data setters
 // establish the three arrays and their 0x0C stride (see WinDrawData.h).
 WinDrawData m_enabledDrawData[9]; // +18
 WinDrawData m_disabledDrawData[9]; // +84
 WinDrawData m_hiliteDrawData[9]; // +F0
 // +15C..+174: the four rowed GameWindow text-colour setters (GameWindow.cpp) store both dwords of each.
 // +188/+194: GameWindowManagerScript.cpp's matched rows compile against these offsets;
 // Zero Hour WinInstanceData.h names the fields.
 TextDrawData m_enabledText; // +15C
 TextDrawData m_disabledText; // +164
 TextDrawData m_hiliteText; // +16C
 TextDrawData m_imeCompositeText; // +174
 unsigned char m_opaque17C[0x184-0x17C];
 GameFont *m_font; // +184, init store
 AsciiString m_textLabelString; // +188
 AsciiString m_decoratedNameString; // +18C, parseName 0x00316355 sets it; Zero Hour WinInstanceData.h names it
 AsciiString m_tooltipString; // +190, parseTooltipText 0x00315CFD sets it; Zero Hour WinInstanceData.h names it
 AsciiString m_headerTemplateName; // +194
 int m_tooltipDelay; // +198, init stores -1
 DisplayString *m_text; // +19C, init frees it through TheDisplayStringManager
 DisplayString *m_tooltip; // +1A0, init frees it through TheDisplayStringManager
 VideoBuffer *m_videoBuffer; // +1A4, init store
private:
 WinInstanceData(const WinInstanceData &);
};
typedef char Bfme2WinInstanceData_extent_1A8[(sizeof(WinInstanceData)==0x1A8)?1:-1];
