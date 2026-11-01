// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// createGadget, retail 0x00316518, 1722 bytes. Dedicated TU.
//
// BFME1 donor GameWindowManagerScriptCreateGadget.cpp (four-arg descriptor ABI,
// WinInstanceData +0x0c style +0x14 owner +0x184 font +0x18c decorated name).
// BFME2 manager vtable is donor +0x14 (5 slots); callers and LINK BONUS prove
// the cdecl createGadget name; copyGadgetDrawData and gadget getters are rowed.
// The child getters are ICF-folded userdata accessors and carry the names their
// addresses are rowed under: 0x2C02D0 (+0x1C), 0x2C02E7 (+0x20), 0x2C02FE
// (+0x24), 0x2C032C and 0x2C0315. Draw-data arguments follow copyGadgetDrawData's
// enabled, disabled, hilite order and retail's DIR32 targets.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef short Short;
typedef bool Bool;

#include "ascii_string.h"
#include <string.h>

#include "GameWindowManagerRecordView.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

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
	GameWindow *m_owner;
	char m_pad18[0x184 - 0x18];
	void *m_font;
	char m_pad188[0x18c - 0x188];
	AsciiString m_decoratedNameString;
};

// Factory slots of the window manager as createGadget calls them (+0x4C..+0x74).
class GameWindowManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48();
	virtual GameWindow *gogoGadgetPushButton(GadgetCreateView *view, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetCommandButton(GadgetCreateView *view, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetCheckbox(GadgetCreateView *view, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetRadioButton(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetTabControl(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetListBox(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetSlider(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetProgressBar(GadgetCreateView *view, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetStaticText(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetTextEntry(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
	virtual GameWindow *gogoGadgetComboBox(GadgetCreateView *view, void *data, void *font, Bool assignVisual);
};

extern GameWindowManager *TheWindowManager;

struct WinDrawData;
extern WinDrawData enabledSliderThumbDrawData[];
extern WinDrawData disabledSliderThumbDrawData[];
extern WinDrawData hiliteSliderThumbDrawData[];
extern WinDrawData enabledSliderDrawData[];
extern WinDrawData disabledSliderDrawData[];
extern WinDrawData hiliteSliderDrawData[];
extern WinDrawData enabledDownButtonDrawData[];
extern WinDrawData disabledDownButtonDrawData[];
extern WinDrawData hiliteDownButtonDrawData[];
extern WinDrawData enabledUpButtonDrawData[];
extern WinDrawData disabledUpButtonDrawData[];
extern WinDrawData hiliteUpButtonDrawData[];
extern WinDrawData enabledListBoxDrawData[];
extern WinDrawData disabledListBoxDrawData[];
extern WinDrawData hiliteListBoxDrawData[];
extern WinDrawData enabledEditBoxDrawData[];
extern WinDrawData disabledEditBoxDrawData[];
extern WinDrawData hiliteEditBoxDrawData[];
extern WinDrawData enabledDropDownButtonDrawData[];
extern WinDrawData disabledDropDownButtonDrawData[];
extern WinDrawData hiliteDropDownButtonDrawData[];

void copyGadgetDrawData_Rva003157BE(GameWindow *dst, GameWindow *src, void *enabled, void *disabled, void *hilite);
GameWindow *GadgetListBoxGetDownButton(GameWindow *w);
GameWindow *GadgetListBoxGetSlider(GameWindow *w);
GameWindow *GadgetComboBoxGetEditBox(GameWindow *w);
GameWindow *GadgetComboBoxGetListBox(GameWindow *w);
class BfmeKeyLC;
void *bfmeGo925A(BfmeKeyLC *w);
class BfmeObjENK;
void bfmeGoENK(BfmeObjENK *w, char v);
void Rva0032857F(GameWindow *w, int v);

// Field names follow Zero Hour's ListboxData where offset and initial value agree.
struct ListboxData
{
	Short listLength;
	Short columns;
	Int *columnWidthPercentage;
	Bool autoScroll;
	Bool autoPurge;
	Bool scrollBar;
	Bool multiSelect;
	Bool forceSelect;
	Bool scrollIfAtEnd;
	char m_pad0E[6];
	Int *columnWidth;
	char m_tail[0x4c - 0x18];
};

struct EntryData
{
	char m_pad00[12];
	UnsignedInt m_dword0C;
	Short maxTextLen;
	char m_tail[22];
};

struct ComboBoxData
{
	char m_pad00[8];
	Short maxChars;
	Short m_pad0A;
	UnsignedInt m_dword0C;
	ListboxData *listboxData;
	EntryData *entryData;
	char m_pad18[8];
	Int entryCount;
};

// createGadget ===============================================================
/** Create a gadget based on the 'type' parm */
//=============================================================================
GameWindow *createGadget(char *type, void *data, GadgetCreateView *record, GameWindow *source)
{
	GameWindow *window = 0;

	record->instance->m_owner = record->parent;

	if (!strcmp(type, "PUSHBUTTON"))
	{
		record->instance->m_style |= 1;
		window = TheWindowManager->gogoGadgetPushButton(record, record->instance->m_font, false);
	}
	else if (!strcmp(type, "COMMANDBUTTON"))
	{
		record->instance->m_style |= 1;
		window = TheWindowManager->gogoGadgetCommandButton(record, record->instance->m_font, false);
	}
	else if (!strcmp(type, "RADIOBUTTON"))
	{
		char filename[64];
		char *c;

		//
		// assign a screen identifier to the radio button based on the
		// filename the radio button was saved in
		//

		strcpy(filename, record->instance->m_decoratedNameString.str());
		c = strchr(filename, ':');
		if (c)
			*c = 0;  // terminate after filename (format is filename:gadgetname)
		if (TheNameKeyGenerator)
			*(Int *)data = (Int)(TheNameKeyGenerator->nameToKey(AsciiString(filename)));

		record->instance->m_style |= 2;
		window = TheWindowManager->gogoGadgetRadioButton(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(type, "CHECKBOX"))
	{
		record->instance->m_style |= 4;
		window = TheWindowManager->gogoGadgetCheckbox(record, record->instance->m_font, false);
	}
	else if (!strcmp(type, "TABCONTROL"))
	{
		record->instance->m_style |= 0x2000;
		window = TheWindowManager->gogoGadgetTabControl(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(type, "VERTSLIDER"))
	{
		record->instance->m_style |= 8;
		window = TheWindowManager->gogoGadgetSlider(record, data, record->instance->m_font, false);

		//
		// we know we've read in the slider thumb data in the definition file
		// (it's guaranteed to be generated by the editor) so place that
		// draw data into the thumb of the slider
		//
		GameWindow *thumb = window->winGetChild();
		if (thumb)
		{
			copyGadgetDrawData_Rva003157BE(thumb, source ? source->winGetChild() : 0, enabledSliderThumbDrawData, disabledSliderThumbDrawData, hiliteSliderThumbDrawData);
			if (thumb->m_field6C)
				Rva0032857F(thumb, 1);
		}  //end if
	}
	else if (!strcmp(type, "HORZSLIDER"))
	{
		record->instance->m_style |= 0x10;
		window = TheWindowManager->gogoGadgetSlider(record, data, record->instance->m_font, false);

		//
		// we know we've read in the slider thumb data in the definition file
		// (it's guaranteed to be generated by the editor) so place that
		// draw data into the thumb of the slider
		//
		GameWindow *thumb = window->winGetChild();
		if (thumb)
			copyGadgetDrawData_Rva003157BE(thumb, source ? source->winGetChild() : 0, enabledSliderThumbDrawData, disabledSliderThumbDrawData, hiliteSliderThumbDrawData);
	}
	else if (!strcmp(type, "SCROLLLISTBOX"))
	{
		record->instance->m_style |= 0x20;
		window = TheWindowManager->gogoGadgetListBox(record, data, record->instance->m_font, false);

		//
		// we know that in the file we have read the draw data for the listbox
		// parts (up button, down button, and slider), now that we have those
		// parts actually created we must assign that data to them
		//
		GameWindow *upButton = GadgetListBoxGetDownButton(window);
		copyGadgetDrawData_Rva003157BE(upButton, source ? GadgetListBoxGetDownButton(source) : 0, enabledUpButtonDrawData, disabledUpButtonDrawData, hiliteUpButtonDrawData);

		GameWindow *downButton = GadgetListBoxGetSlider(window);
		copyGadgetDrawData_Rva003157BE(downButton, source ? GadgetListBoxGetSlider(source) : 0, enabledDownButtonDrawData, disabledDownButtonDrawData, hiliteDownButtonDrawData);

		GameWindow *slider = GadgetComboBoxGetEditBox(window);
		if (slider)
		{
			GameWindow *sourceSlider = source ? GadgetComboBoxGetEditBox(source) : 0;
			copyGadgetDrawData_Rva003157BE(slider, sourceSlider, enabledSliderDrawData, disabledSliderDrawData, hiliteSliderDrawData);

			// do the slider thumb
			GameWindow *thumb = slider->winGetChild();
			if (thumb)
			{
				copyGadgetDrawData_Rva003157BE(thumb, sourceSlider ? sourceSlider->winGetChild() : 0, enabledSliderThumbDrawData, disabledSliderThumbDrawData, hiliteSliderThumbDrawData);
				if (thumb->m_field6C)
				{
					Rva0032857F(thumb, 1);
					bfmeGoENK((BfmeObjENK *)window, 1);
				}
			}  //end if
		}  // end if
	}
	else if (!strcmp(type, "COMBOBOX"))
	{
		ComboBoxData *cData = (ComboBoxData *)data;
		cData->entryData = new EntryData;
		memset(cData->entryData, 0, sizeof(EntryData));
		cData->listboxData = new ListboxData;
		memset(cData->listboxData, 0, sizeof(ListboxData));

		//initialize combo box data
		//cData->isEditable = TRUE;
		//cData->maxChars = 16;
		//cData->maxDisplay = 5;
		cData->entryCount = 0;
		//initialize entry data
		cData->entryData->m_dword0C = cData->m_dword0C;
		cData->entryData->maxTextLen = cData->maxChars;

		//initialize listbox data
		cData->listboxData->listLength = 10;
		cData->listboxData->autoScroll = 0;
		cData->listboxData->scrollIfAtEnd = false;
		cData->listboxData->autoPurge = 0;
		cData->listboxData->scrollBar = 1;
		cData->listboxData->multiSelect = 0;
		cData->listboxData->forceSelect = 1;
		cData->listboxData->columns = 1;
		cData->listboxData->columnWidth = 0;
		cData->listboxData->columnWidthPercentage = 0;

		record->instance->m_style |= 0x8000;
		window = TheWindowManager->gogoGadgetComboBox(record, data, record->instance->m_font, false);

		GameWindow *dropDownButton = GadgetComboBoxGetEditBox(window);
		copyGadgetDrawData_Rva003157BE(dropDownButton, source ? GadgetComboBoxGetEditBox(source) : 0, enabledDropDownButtonDrawData, disabledDropDownButtonDrawData, hiliteDropDownButtonDrawData);

		GameWindow *editBox = GadgetComboBoxGetListBox(window);
		copyGadgetDrawData_Rva003157BE(editBox, source ? GadgetComboBoxGetListBox(source) : 0, enabledEditBoxDrawData, disabledEditBoxDrawData, hiliteEditBoxDrawData);

		GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
		if (listBox)
		{
			GameWindow *sourceList = source ? (GameWindow *)bfmeGo925A((BfmeKeyLC *)source) : 0;
			copyGadgetDrawData_Rva003157BE(listBox, sourceList, enabledListBoxDrawData, disabledListBoxDrawData, hiliteListBoxDrawData);

			GameWindow *upButton = GadgetListBoxGetDownButton(listBox);
			copyGadgetDrawData_Rva003157BE(upButton, source ? GadgetListBoxGetDownButton(source) : 0, enabledUpButtonDrawData, disabledUpButtonDrawData, hiliteUpButtonDrawData);

			GameWindow *downButton = GadgetListBoxGetSlider(listBox);
			copyGadgetDrawData_Rva003157BE(downButton, source ? GadgetListBoxGetSlider(source) : 0, enabledDownButtonDrawData, disabledDownButtonDrawData, hiliteDownButtonDrawData);

			GameWindow *slider = GadgetComboBoxGetEditBox(listBox);
			if (slider)
			{
				GameWindow *sourceSlider = sourceList ? GadgetComboBoxGetEditBox(sourceList) : 0;
				copyGadgetDrawData_Rva003157BE(slider, sourceSlider, enabledSliderDrawData, disabledSliderDrawData, hiliteSliderDrawData);

				// do the slider thumb
				GameWindow *thumb = slider->winGetChild();
				if (thumb)
				{
					copyGadgetDrawData_Rva003157BE(thumb, sourceSlider ? sourceSlider->winGetChild() : 0, enabledSliderThumbDrawData, disabledSliderThumbDrawData, hiliteSliderThumbDrawData);
					if (thumb->m_field6C)
						Rva0032857F(thumb, 1);
				}  //end if
			}  // end if
		}
	}
	else if (!strcmp(type, "ENTRYFIELD"))
	{
		record->instance->m_style |= 0x40;
		window = TheWindowManager->gogoGadgetTextEntry(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(type, "STATICTEXT"))
	{
		record->instance->m_style |= 0x80;
		window = TheWindowManager->gogoGadgetStaticText(record, data, record->instance->m_font, false);
	}
	else if (!strcmp(type, "PROGRESSBAR"))
	{
		record->instance->m_style |= 0x100;
		window = TheWindowManager->gogoGadgetProgressBar(record, record->instance->m_font, false);
	}

	return window;

}  // end createGadget
