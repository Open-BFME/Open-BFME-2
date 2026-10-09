// ?createGadget@@YAPAVGameWindow@@PADPAXPAVGadgetCreateView@@PAV1@@Z
// partial score=0.8642263912 date=2026-10-09
// ?createGadget@@YAPAVGameWindow@@PADPAXPAVGadgetCreateView@@PAV1@@Z
// partial score=0.8206 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/GameClient/GUI
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
struct WinDrawData;
extern WinDrawData hiliteSliderThumbDrawData[];
extern WinDrawData disabledSliderThumbDrawData[];
extern WinDrawData enabledSliderThumbDrawData[];
extern WinDrawData hiliteUpButtonDrawData[];
extern WinDrawData disabledUpButtonDrawData[];
extern WinDrawData enabledUpButtonDrawData[];
extern WinDrawData hiliteDownButtonDrawData[];
extern WinDrawData disabledDownButtonDrawData[];
extern WinDrawData enabledDownButtonDrawData[];
extern WinDrawData hiliteSliderDrawData[];
extern WinDrawData disabledSliderDrawData[];
extern WinDrawData enabledSliderDrawData[];
extern WinDrawData hiliteDropDownButtonDrawData[];
extern WinDrawData disabledDropDownButtonDrawData[];
extern WinDrawData enabledDropDownButtonDrawData[];

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

#include "GameWindowManagerRecordView.h"

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

class BfmeKeyLC;void *bfmeGo925A(BfmeKeyLC*);
GameWindow *createGadget(char *type, void *data, GadgetCreateView *record, GameWindow *source)
{
	GameWindow *window = 0;
 char *volatile &input=type;
	record->instance->m_owner = record->parent;
	if (!strcmp(input, "PUSHBUTTON"))
	{
		record->instance->m_style |= 1;
		window = ((GameWindowManager *)TheWindowManager)->v4cPushButton(record, record->instance->m_font, false);
	}
	else if (!strcmp(input, "COMMANDBUTTON"))
	{
		record->instance->m_style |= 1;
		window = ((GameWindowManager *)TheWindowManager)->v50CommandButton(record, record->instance->m_font, false);
	}
	else if (!strcmp(input, "RADIOBUTTON"))
	{
		char filename[64];
		char *c;
		_mbscpy(filename, record->instance->m_decoratedNameString.str());
		c = strchr(filename, ':');
		if (c)
			*c = 0;
		if (TheNameKeyGenerator)
			*(int *)data = (int)TheNameKeyGenerator->nameToKey(AsciiString(filename));
		record->instance->m_style |= 2;
		window = ((GameWindowManager *)TheWindowManager)->v58RadioButton(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(input, "CHECKBOX"))
	{
		record->instance->m_style |= 4;
		window = ((GameWindowManager *)TheWindowManager)->v54CheckBox(record, record->instance->m_font, false);
	}
	else if (!strcmp(input, "TABCONTROL"))
	{
		record->instance->m_style |= 0x2000;
		window = ((GameWindowManager *)TheWindowManager)->v5cTabControl(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(input, "VERTSLIDER"))
	{
		record->instance->m_style |= 8;
		window = ((GameWindowManager *)TheWindowManager)->v64VertSlider(record, data, record->instance->m_font, false);
		GameWindow *thumb = window->winGetChild();
		if (thumb)
		{
			GameWindow *srcChild = source ? source->winGetChild() : 0;
			copyGadgetDrawData_Rva003157BE(thumb, srcChild, hiliteSliderThumbDrawData, disabledSliderThumbDrawData, enabledSliderThumbDrawData);
			if (thumb->m_field6C)
				Rva0032857F(thumb, 1);
		}
	}
	else if (!strcmp(input, "HORZSLIDER"))
	{
		record->instance->m_style |= 0x10;
		window = ((GameWindowManager *)TheWindowManager)->v64VertSlider(record, data, record->instance->m_font, false);
		GameWindow *thumb = window->winGetChild();
		if (thumb)
			copyGadgetDrawData_Rva003157BE(thumb, source ? source->winGetChild() : 0, hiliteSliderThumbDrawData, disabledSliderThumbDrawData, enabledSliderThumbDrawData);
	}
	else if (!strcmp(input, "SCROLLLISTBOX"))
	{
		record->instance->m_style |= 0x20;
		window = ((GameWindowManager *)TheWindowManager)->v60ScrollListBox(record, data, record->instance->m_font, false);
		GameWindow *upButton = GadgetListBoxGetDownButton(window);
		copyGadgetDrawData_Rva003157BE(upButton, source ? GadgetListBoxGetDownButton(source) : 0, hiliteUpButtonDrawData, disabledUpButtonDrawData, enabledUpButtonDrawData);
		GameWindow *downButton = GadgetListBoxGetSlider(window);
		copyGadgetDrawData_Rva003157BE(downButton, source ? GadgetListBoxGetSlider(source) : 0, hiliteDownButtonDrawData, disabledDownButtonDrawData, enabledDownButtonDrawData);
		GameWindow *slider = GadgetComboBoxGetEditBox(window);
		if (slider)
		{
			GameWindow *sourceSlider = source ? GadgetComboBoxGetEditBox(source) : 0;
			copyGadgetDrawData_Rva003157BE(slider, sourceSlider, hiliteSliderDrawData, disabledSliderDrawData, enabledSliderDrawData);
			GameWindow *thumb = slider->winGetChild();
			if (thumb)
			{
				GameWindow *srcThumb = sourceSlider ? sourceSlider->winGetChild() : 0;
				copyGadgetDrawData_Rva003157BE(thumb, srcThumb, hiliteSliderThumbDrawData, disabledSliderThumbDrawData, enabledSliderThumbDrawData);
				if (thumb->m_field6C)
				{
					Rva0032857F(thumb, 1);
					bfmeGoENK((BfmeObjENK *)window, 1);
				}
			}
		}
	}
	else if (!strcmp(input, "COMBOBOX"))
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
		record->instance->m_style |= 0x8000;
		window = ((GameWindowManager *)TheWindowManager)->v74ComboBox(record, data, record->instance->m_font, false);
		GameWindow *dropDownButton = GadgetComboBoxGetEditBox(window);
		copyGadgetDrawData_Rva003157BE(dropDownButton, source ? GadgetComboBoxGetEditBox(source) : 0, hiliteDropDownButtonDrawData, disabledDropDownButtonDrawData, enabledDropDownButtonDrawData);
		GameWindow *editBox = GadgetComboBoxGetListBox(window);
		copyGadgetDrawData_Rva003157BE(editBox, source ? GadgetComboBoxGetListBox(source) : 0, hiliteSliderDrawData, disabledSliderDrawData, enabledSliderDrawData);
		GameWindow *listBox = ((GameWindow*)bfmeGo925A((BfmeKeyLC*)window));
		if (listBox)
		{
			GameWindow *sourceList = source ? ((GameWindow*)bfmeGo925A((BfmeKeyLC*)source)) : 0;
			copyGadgetDrawData_Rva003157BE(listBox, sourceList, hiliteSliderDrawData, disabledSliderDrawData, enabledSliderDrawData);
			GameWindow *upButton = GadgetListBoxGetDownButton(listBox);
			copyGadgetDrawData_Rva003157BE(upButton, source ? GadgetListBoxGetDownButton(source) : 0, hiliteUpButtonDrawData, disabledUpButtonDrawData, enabledUpButtonDrawData);
			GameWindow *downButton = GadgetListBoxGetSlider(listBox);
			copyGadgetDrawData_Rva003157BE(downButton, source ? GadgetListBoxGetSlider(source) : 0, hiliteDownButtonDrawData, disabledDownButtonDrawData, enabledDownButtonDrawData);
			GameWindow *slider = GadgetComboBoxGetEditBox(listBox);
			if (slider)
			{
				GameWindow *sourceSlider = sourceList ? GadgetComboBoxGetEditBox(sourceList) : 0;
				copyGadgetDrawData_Rva003157BE(slider, sourceSlider, hiliteSliderDrawData, disabledSliderDrawData, enabledSliderDrawData);
				GameWindow *thumb = slider->winGetChild();
				if (thumb)
				{
					GameWindow *srcThumb = sourceSlider ? sourceSlider->winGetChild() : 0;
					copyGadgetDrawData_Rva003157BE(thumb, srcThumb, hiliteSliderThumbDrawData, disabledSliderThumbDrawData, enabledSliderThumbDrawData);
					if (thumb->m_field6C)
						Rva0032857F(thumb, 1);
				}
			}
		}
	}
	else if (!strcmp(input, "ENTRYFIELD"))
	{
		record->instance->m_style |= 64;
		window = ((GameWindowManager *)TheWindowManager)->v70EntryField(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(input, "STATICTEXT"))
	{
		record->instance->m_style |= 128;
		window = ((GameWindowManager *)TheWindowManager)->v6cStaticText(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(input, "PROGRESSBAR"))
	{
		record->instance->m_style |= 256;
		window = ((GameWindowManager *)TheWindowManager)->v68ProgressBar(record, record->instance->m_font, false);
	}
	return window;
}
