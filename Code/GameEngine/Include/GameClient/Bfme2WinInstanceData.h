#pragma once
// Target WinInstanceData: ctor32225A installs C0D830; one virtual dtor slot.
// GameWindow member30..1D7 and last ctor word1A4 prove extent1A8; init322174 stores every named field.
// Zero Hour WinInstanceData.h names the fields; unknown storage stays opaque.
#include "WinDrawData.h"

class GameWindow;
class GameFont;
class DisplayString;
class VideoBuffer;
class UnicodeString;

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
 int m_enabledColor, m_enabledBorderColor;
 int m_disabledColor, m_disabledBorderColor;
 int m_hiliteColor, m_hiliteBorderColor;
 int m_imecompositeColor, m_imecompositeBorderColor;
 unsigned char m_opaque17C[0x184-0x17C];
 GameFont *m_font; // +184, init store
 unsigned char m_opaque188[0x198-0x188];
 int m_tooltipDelay; // +198, init stores -1
 DisplayString *m_text; // +19C, init frees it through TheDisplayStringManager
 DisplayString *m_tooltip; // +1A0, init frees it through TheDisplayStringManager
 VideoBuffer *m_videoBuffer; // +1A4, init store
private:
 WinInstanceData(const WinInstanceData &);
};
typedef char Bfme2WinInstanceData_extent_1A8[(sizeof(WinInstanceData)==0x1A8)?1:-1];
