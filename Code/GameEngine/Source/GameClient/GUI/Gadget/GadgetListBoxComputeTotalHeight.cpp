// cl: /O1 /DNDEBUG /MD
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

class GameWindow
{
public:
	void *winGetUserData();
	WinInstanceData *winGetInstanceData();
	unsigned int winGetStatus();
};

class WinInstanceData
{
public:
	char m_pad00[0x184];
	void *m_font;
};

class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual int getHeight(void *font);
};

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

struct ListEntryCell
{
	int cellType;
	char m_pad04[8];
	void *data;
	char m_pad10[8];
	int height;
};

struct ListEntryRow
{
	int listHeight;
	int rowHeight;
	ListEntryCell *cell;
	int m_pad0C;
};

struct ListboxData
{
	char m_pad00[2];
	short columns;
	char m_pad04[0x14];
	ListEntryRow *listData;
	char m_pad1C[0x0C];
	int totalHeight;
	short endPos;
};

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
					cellHeight = TheWindowManager->getHeight(font);
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
					cellHeight = TheWindowManager->getHeight(font);
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
