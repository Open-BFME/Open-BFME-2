// ?createGadget@@YAPAVGameWindow@@PADPAXPAVGadgetCreateView@@PAV1@@Z
// partial score=0.8206 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?createGadget@@YAPAVGameWindow@@PADPAXPAVGadgetCreateView@@PAV1@@Z at retail 0x00316518 (1722B).
// BFME1 donor GameWindowManagerScriptCreateGadget.cpp (four-arg descriptor ABI,
// WinInstanceData +0x0c style +0x14 owner +0x184 font +0x18c decorated name).
// BFME2 manager vtable is donor +0x14 (5 slots); callers and LINK BONUS prove
// the cdecl createGadget name; copyGadgetDrawData and gadget getters are rowed.
#include "ascii_string.h"
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;

class GameWindow;
class WinInstanceData;
class GadgetCreateView;
class GameWindowManager;
class BfmeObjENK;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern const char g_Rva0107301CEmptyString[];
extern int g_00E00960[];
extern int g_00E009D0[];
extern int g_00E00A40[];
extern int g_00E00D50[];
extern int g_00E00DC0[];
extern int g_00E00E30[];
extern int g_00E00C00[];
extern int g_00E00C70[];
extern int g_00E00CE0[];
extern int g_00E00AB0[];
extern int g_00E00B20[];
extern int g_00E00B90[];
extern int g_00E01140[];
extern int g_00E011B0[];
extern int g_00E01220[];

extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);
extern int strcmp(const char *a, const char *b);

class GameWindow
{
public:
	GameWindow *winGetChild();
	char m_pad[0x6c];
	void *m_field6C;
};

class WinInstanceData
{
public:
	char m_pad00[0x0c];
	UnsignedInt m_style;
	char m_pad10[0x04];
	void *m_owner;
	char m_pad18[0x184 - 0x18];
	void *m_font;
	char m_pad188[0x18c - 0x188];
	AsciiString m_decoratedNameString;
};

class GadgetCreateView
{
public:
	GameWindow *m_window;
	char m_pad04[0x30 - 0x04];
	WinInstanceData *m_instData;
};

class GameWindowManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34();
	virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
	virtual void v48();
	virtual GameWindow *v4cPushButton(GadgetCreateView *view, void *font, bool flag);
	virtual GameWindow *v50CommandButton(GadgetCreateView *view, void *font, bool flag);
	virtual GameWindow *v54CheckBox(GadgetCreateView *view, void *font, bool flag);
	virtual GameWindow *v58RadioButton(GadgetCreateView *view, void *data, void *font, bool flag);
	virtual GameWindow *v5cTabControl(GadgetCreateView *view, void *data, void *font, bool flag);
	virtual GameWindow *v60ScrollListBox(GadgetCreateView *view, void *data, void *font, bool flag);
	virtual GameWindow *v64VertSlider(GadgetCreateView *view, void *data, void *font, bool flag);
	virtual GameWindow *v68ProgressBar(GadgetCreateView *view, void *font, bool flag);
	virtual GameWindow *v6cStaticText(GadgetCreateView *view, void *data, void *font, bool flag);
	virtual GameWindow *v70EntryField(GadgetCreateView *view, void *data, void *font, bool flag);
	virtual GameWindow *v74ComboBox(GadgetCreateView *view, void *data, void *font, bool flag);
};

void copyGadgetDrawData_Rva003157BE(GameWindow *dst, GameWindow *src, void *a, void *b, void *c);
GameWindow *winGetChildProxy(GameWindow *w);
GameWindow *GadgetListBoxGetUpButton(GameWindow *w);
GameWindow *GadgetListBoxGetDownButton(GameWindow *w);
GameWindow *GadgetListBoxGetSlider(GameWindow *w);
GameWindow *GadgetComboBoxGetDropDownButton(GameWindow *w);
GameWindow *GadgetComboBoxGetEditBox(GameWindow *w);
GameWindow *GadgetComboBoxGetListBox(GameWindow *w);
void Rva0032857F(GameWindow *w, int v);
void bfmeGoENK(BfmeObjENK *o, char v);

struct ComboEntryData
{
	char m_pad00[12];
	UnsignedInt m_dword0C;
	short m_word10;
	char m_tail[22];
};

struct ComboListData
{
	short m_word00;
	short m_word02;
	void *m_dword04;
	char m_byte08;
	char m_byte09;
	char m_byte0A;
	char m_byte0B;
	char m_byte0C;
	char m_byte0D;
	char m_pad0E[6];
	void *m_dword14;
	char m_tail[0x4c - 0x18];
};

struct ComboData
{
	char m_pad00[8];
	short m_word08;
	short m_pad0A;
	UnsignedInt m_dword0C;
	ComboListData *m_list;
	ComboEntryData *m_entry;
	char m_pad18[8];
	int m_dword20;
};

GameWindow *createGadget(char *type, void *data, GadgetCreateView *record, GameWindow *source)
{
	GameWindow *window = 0;
	record->m_instData->m_owner = record->m_window;
	if (!strcmp(type, "PUSHBUTTON"))
	{
		record->m_instData->m_style |= 1;
		window = ((GameWindowManager *)TheWindowManager)->v4cPushButton(record, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "COMMANDBUTTON"))
	{
		record->m_instData->m_style |= 1;
		window = ((GameWindowManager *)TheWindowManager)->v50CommandButton(record, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "RADIOBUTTON"))
	{
		char filename[64];
		char *c;
		_mbscpy(filename, record->m_instData->m_decoratedNameString.str());
		c = strchr(filename, ':');
		if (c)
			*c = 0;
		if (TheNameKeyGenerator)
			*(int *)data = (int)TheNameKeyGenerator->nameToKey(AsciiString(filename));
		record->m_instData->m_style |= 2;
		window = ((GameWindowManager *)TheWindowManager)->v58RadioButton(record, data, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "CHECKBOX"))
	{
		record->m_instData->m_style |= 4;
		window = ((GameWindowManager *)TheWindowManager)->v54CheckBox(record, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "TABCONTROL"))
	{
		record->m_instData->m_style |= 0x2000;
		window = ((GameWindowManager *)TheWindowManager)->v5cTabControl(record, data, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "VERTSLIDER"))
	{
		record->m_instData->m_style |= 8;
		window = ((GameWindowManager *)TheWindowManager)->v64VertSlider(record, data, record->m_instData->m_font, false);
		GameWindow *thumb = window->winGetChild();
		if (thumb)
		{
			GameWindow *srcChild = source ? source->winGetChild() : 0;
			copyGadgetDrawData_Rva003157BE(thumb, srcChild, g_00E00960, g_00E009D0, g_00E00A40);
			if (thumb->m_field6C)
				Rva0032857F(thumb, 1);
		}
	}
	else if (!strcmp(type, "HORZSLIDER"))
	{
		record->m_instData->m_style |= 0x10;
		window = ((GameWindowManager *)TheWindowManager)->v64VertSlider(record, data, record->m_instData->m_font, false);
		GameWindow *thumb = window->winGetChild();
		if (thumb)
			copyGadgetDrawData_Rva003157BE(thumb, source ? source->winGetChild() : 0, g_00E00960, g_00E009D0, g_00E00A40);
	}
	else if (!strcmp(type, "SCROLLLISTBOX"))
	{
		record->m_instData->m_style |= 0x20;
		window = ((GameWindowManager *)TheWindowManager)->v60ScrollListBox(record, data, record->m_instData->m_font, false);
		GameWindow *upButton = GadgetListBoxGetUpButton(window);
		copyGadgetDrawData_Rva003157BE(upButton, source ? GadgetListBoxGetUpButton(source) : 0, g_00E00D50, g_00E00DC0, g_00E00E30);
		GameWindow *downButton = GadgetListBoxGetDownButton(window);
		copyGadgetDrawData_Rva003157BE(downButton, source ? GadgetListBoxGetDownButton(source) : 0, g_00E00C00, g_00E00C70, g_00E00CE0);
		GameWindow *slider = GadgetListBoxGetSlider(window);
		if (slider)
		{
			GameWindow *sourceSlider = source ? GadgetListBoxGetSlider(source) : 0;
			copyGadgetDrawData_Rva003157BE(slider, sourceSlider, g_00E00AB0, g_00E00B20, g_00E00B90);
			GameWindow *thumb = slider->winGetChild();
			if (thumb)
			{
				GameWindow *srcThumb = sourceSlider ? sourceSlider->winGetChild() : 0;
				copyGadgetDrawData_Rva003157BE(thumb, srcThumb, g_00E00960, g_00E009D0, g_00E00A40);
				if (thumb->m_field6C)
				{
					Rva0032857F(thumb, 1);
					bfmeGoENK((BfmeObjENK *)window, 1);
				}
			}
		}
	}
	else if (!strcmp(type, "COMBOBOX"))
	{
		ComboData *cData = (ComboData *)data;
		cData->m_entry = new ComboEntryData;
		memset(cData->m_entry, 0, sizeof(ComboEntryData));
		cData->m_list = new ComboListData;
		memset(cData->m_list, 0, sizeof(ComboListData));
		cData->m_dword20 = 0;
		cData->m_entry->m_dword0C = cData->m_dword0C;
		cData->m_entry->m_word10 = cData->m_word08;
		cData->m_list->m_word00 = 10;
		cData->m_list->m_byte08 = 0;
		cData->m_list->m_byte0D = 0;
		cData->m_list->m_byte09 = 0;
		cData->m_list->m_byte0A = 1;
		cData->m_list->m_byte0B = 0;
		cData->m_list->m_byte0C = 1;
		cData->m_list->m_word02 = 1;
		cData->m_list->m_dword14 = 0;
		cData->m_list->m_dword04 = 0;
		record->m_instData->m_style |= 0x8000;
		window = ((GameWindowManager *)TheWindowManager)->v74ComboBox(record, data, record->m_instData->m_font, false);
		GameWindow *dropDownButton = GadgetComboBoxGetDropDownButton(window);
		copyGadgetDrawData_Rva003157BE(dropDownButton, source ? GadgetComboBoxGetDropDownButton(source) : 0, g_00E01140, g_00E011B0, g_00E01220);
		GameWindow *editBox = GadgetComboBoxGetEditBox(window);
		copyGadgetDrawData_Rva003157BE(editBox, source ? GadgetComboBoxGetEditBox(source) : 0, g_00E00AB0, g_00E00B20, g_00E00B90);
		GameWindow *listBox = GadgetComboBoxGetListBox(window);
		if (listBox)
		{
			GameWindow *sourceList = source ? GadgetComboBoxGetListBox(source) : 0;
			copyGadgetDrawData_Rva003157BE(listBox, sourceList, g_00E00AB0, g_00E00B20, g_00E00B90);
			GameWindow *upButton = GadgetListBoxGetUpButton(listBox);
			copyGadgetDrawData_Rva003157BE(upButton, source ? GadgetListBoxGetUpButton(source) : 0, g_00E00D50, g_00E00DC0, g_00E00E30);
			GameWindow *downButton = GadgetListBoxGetDownButton(listBox);
			copyGadgetDrawData_Rva003157BE(downButton, source ? GadgetListBoxGetDownButton(source) : 0, g_00E00C00, g_00E00C70, g_00E00CE0);
			GameWindow *slider = GadgetListBoxGetSlider(listBox);
			if (slider)
			{
				GameWindow *sourceSlider = sourceList ? GadgetListBoxGetSlider(sourceList) : 0;
				copyGadgetDrawData_Rva003157BE(slider, sourceSlider, g_00E00AB0, g_00E00B20, g_00E00B90);
				GameWindow *thumb = slider->winGetChild();
				if (thumb)
				{
					GameWindow *srcThumb = sourceSlider ? sourceSlider->winGetChild() : 0;
					copyGadgetDrawData_Rva003157BE(thumb, srcThumb, g_00E00960, g_00E009D0, g_00E00A40);
					if (thumb->m_field6C)
						Rva0032857F(thumb, 1);
				}
			}
		}
	}
	else if (!strcmp(type, "ENTRYFIELD"))
	{
		record->m_instData->m_style |= 64;
		window = ((GameWindowManager *)TheWindowManager)->v70EntryField(record, data, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "STATICTEXT"))
	{
		record->m_instData->m_style |= 128;
		window = ((GameWindowManager *)TheWindowManager)->v6cStaticText(record, data, record->m_instData->m_font, false);
	}
	else if (!strcmp(type, "PROGRESSBAR"))
	{
		record->m_instData->m_style |= 256;
		window = ((GameWindowManager *)TheWindowManager)->v68ProgressBar(record, record->m_instData->m_font, false);
	}
	return window;
}
