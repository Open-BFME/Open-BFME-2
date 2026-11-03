// Target facts (retail RVAs): 0x002C13B5 allocates 0x4C bytes and 0x002C13BC copies that extent; 0x00316917 and 0x0031691E allocate and zero the same record. Retail has no virtual functions or base classes here: +0 holds a short (0x002C1404), and neither allocation calls a constructor or stores a vtable. No member methods or constructor/destructor tables are rowed. Zero Hour GeneralsMD GameClient/Gadget.h's _ListboxData declaration supplies the shared field names, not the BFME2 layout.
// 0x0031503A and 0x003150C2 pass +0 and +2 to scanShort. 0x003150DF allocates an int array, 0x003150EE stores its pointer at +4, and 0x003150FD indexes it. scanBool receives +8 at 0x00315049, +9 at 0x00315089, +A at 0x0031509B, +B at 0x003150AD, +C at 0x00315132 and +D at 0x0031506E. 0x00315124 clears +14; the pixel-width worker 0x003251F4 allocates and indexes that int array. Byte flags +E, +F, +10, +11, +12 and +13 are accessed at 0x00323A11, 0x00325DD6, 0x0032585C, 0x00324AC6, 0x00322B02 and 0x00322B06; +11 controls overflow-based scrollbar visibility.
// 0x00324C93 proves the row pointer at +18; 0x00324C80 reads the short at +2C. 0x00324603, 0x00324655 and 0x0032470D store the up-button, down-button and slider pointers at +1C, +20 and +24. The remaining accesses are +28 int (0x002C1454), +2E short (0x002C144C), +30 int (0x00322B0A), +34 int (0x002C143C), +38 int pointer (0x00326947), +3C short (0x002C141E), +40 dword (0x002C1449), +44 short (0x002C1445) and +48 int (0x003250C3). Unproven names remain offset placeholders; natural alignment leaves two bytes at +3E and +46.

#pragma once

class GameWindow;
struct ListEntryRow;

struct ListboxData
{
	short listLength;
	short columns;
	int *columnWidthPercentage;
	bool autoScroll;
	bool autoPurge;
	bool scrollBar;
	bool multiSelect;
	bool forceSelect;
	bool scrollIfAtEnd;
	bool m_0E;
	bool m_0F;
	bool m_10;
	bool m_11;
	bool m_12;
	bool m_13;
	int *columnWidth;
	ListEntryRow *listData;
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	int totalHeight;
	short endPos;
	short insertPos;
	int m_30;
	int selectPos;
	int *selections;
	short displayHeight;
	unsigned int doubleClickTime;
	short displayPos;
	int m_48;
};
