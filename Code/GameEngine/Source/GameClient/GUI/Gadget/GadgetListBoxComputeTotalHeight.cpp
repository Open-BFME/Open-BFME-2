// cl: /DNDEBUG /MD
//
// ?computeTotalHeight@@YAXPAVGameWindow@@@Z, retail 0x00324C61, 291 bytes.
// Free-function listbox layout: walks rows at user+0x18, cells 0x1c,
// max per column, total at user+0x28 then rowed Rva003249D2(window,1).
// Evidence: donor game/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// computeTotalHeight, callers 0x00324E7F 0x00325622 0x0032636F 0x00326588 0x00326F72,
// LINK BONUS 378B Rva00326E21Permuted, pin ?computeTotalHeight.
// Type1 via virtual [obj+0x3c](0,&cur) unless status has 0x4000,
// type2 via height+1, else WindowManager [0x120](font at inst+0x184).
class GameWindow;
class WinInstanceData;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

class ListDisplayString
{
public:
	virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
	virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
	virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
	virtual void w12(); virtual void w13(); virtual void w14();
	virtual void getSize(int zero, int *out);
};

#include "../../../../Include/Common/ListEntryCell.h"

struct ListEntryRow
{
	int listHeight;
	int rowHeight;
	ListEntryCell *cell;
	int m_pad0C;
};

#include "../../../../Include/GameClient/ListboxData.h"

void __cdecl Rva003249D2(GameWindow *window, bool update);

void __cdecl computeTotalHeight(GameWindow *window)
{
	int i;
	int height = 0;
	int tempHeight;
	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	for (i = 0; i < *(short *)((char *)list + 0x2C); i++)
	{
		if (!(*(ListEntryRow **)((char *)list + 0x18))[i].cell)
			continue;
		tempHeight = 0;

		for (int j = 0; j < list->columns; j++)
		{
			int cellHeight = 0;
			if ((*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].cellType == 1)
			{
				if ((window->winGetStatus() & 0x4000) != 0)
				{
					void *font = instData->m_font;
					cellHeight = TheWindowManager->winFontHeight((GameFont *)font);
				}
				else
				{
					ListDisplayString *displayString = (ListDisplayString *)(*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].data;
					if (displayString)
						displayString->getSize(0, &cellHeight);
				}
			}
			else if ((*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].cellType == 2)
			{
				if ((*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].height > 0)
					cellHeight = (*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].height + 1;
				else
				{
					void *font = instData->m_font;
					cellHeight = TheWindowManager->winFontHeight((GameFont *)font);
				}
			}
			if (cellHeight > tempHeight)
				tempHeight = cellHeight;
		}
		*(int *)((char *)(*(ListEntryRow **)((char *)list + 0x18) + i) + 4) = tempHeight;
		height += (*(int *)((char *)(*(ListEntryRow **)((char *)list + 0x18) + i) + 4) + 1);
		(*(ListEntryRow **)((char *)list + 0x18))[i].listHeight = height;
	}

	*(int *)((char *)list + 0x28) = height;

	Rva003249D2(window, true);
}
