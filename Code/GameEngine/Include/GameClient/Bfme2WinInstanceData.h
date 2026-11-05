#pragma once
// Target WinInstanceData: ctor32225A installs C0D830; one virtual dtor slot.
// GameWindow member30..1D7 and last ctor word1A4 prove extent1A8.
// Unknown storage stays opaque. Lifetime bodies remain the matched owners.
#include "WinDrawData.h"

class WinInstanceData
{
public:
 WinInstanceData();
 virtual ~WinInstanceData();
 int m_id; // +04, GameWindow::winSetWindowId at 0x0031404A
 unsigned char m_opaque08[4];
 unsigned int m_style; // +0C
 unsigned char m_opaque10[8];
 // init at 0x00322174 and the nine rowed GameWindow draw-data setters
 // establish the three arrays and their 0x0C stride (see WinDrawData.h).
 WinDrawData m_enabledDrawData[9]; // +18
 WinDrawData m_disabledDrawData[9]; // +84
 WinDrawData m_hiliteDrawData[9]; // +F0
 int m_enabledColor, m_enabledBorderColor;
 int m_disabledColor, m_disabledBorderColor;
 int m_hiliteColor, m_hiliteBorderColor;
 int m_imecompositeColor, m_imecompositeBorderColor;
 unsigned char m_opaque17C[0x1A8-0x17C];
private:
 WinInstanceData(const WinInstanceData &);
 WinInstanceData &operator=(const WinInstanceData &);
};
typedef char Bfme2WinInstanceData_extent_1A8[(sizeof(WinInstanceData)==0x1A8)?1:-1];
