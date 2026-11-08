// cl: /DNDEBUG /MD /EHsc
//
// ?duplicateGadget@GameWindowManager@@QAEPAVGameWindow@@PAV2@H@Z
// retail 0x003174CB, 262 bytes. Dedicated TU.
//
// Rebuilds a gadget from a live window. Target facts:
// - sole caller 0x00411755 loads ecx from the window-manager global
//   (0x00DFEF1C) before the call; ecx is never read, ret 8 -> a
//   GameWindowManager member taking (GameWindow *source, Int id).
// - the gadget type name is picked from the instance style word (+0x0C of
//   winGetInstanceData 0x00314046) in the bit order below; no bit -> NULL.
// - a zeroed 0x34-byte create view (ctor 0x0022239C) is filled by
//   GameWindow::snapshotCreateView (0x003146DC, clear=true), its first word
//   set to id; the user data (winGetUserData 0x005C4ACD) is copied over the
//   type's template static (getDataTemplate 0x00315445, size out-param);
//   then createGadget 0x00316518 builds the window.
// Donor: none (BFME2-only; the gadget names are the Zero Hour
// GameWindowManagerScript.cpp set). The method name is address-derived.

#include <windows.h>
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;

void *getDataTemplate(char *type, Int *sizeOut);

class GadgetCreateView
{
public:
	GadgetCreateView();

	Int m_idOrUser;		// +0x00
	unsigned char m_rest[0x34 - 4];
};

#include "../../../Include/GameClient/Bfme2GameWindow.h"

GameWindow *createGadget(char *type, void *data, GadgetCreateView *view, GameWindow *source);

#include "../../../Include/GameClient/GameWindowManager.h"

GameWindow *GameWindowManager::duplicateGadget(GameWindow *source, Int id)
{
	if (source == NULL)
		return NULL;
	WinInstanceData *instData = source->winGetInstanceData();
	if (instData == NULL)
		return NULL;

	UnsignedInt style = instData->m_style;
	char *type;
	if (style & 0x0001)
		type = "PUSHBUTTON";
	else if (style & 0x0004)
		type = "CHECKBOX";
	else if (style & 0x2000)
		type = "TABCONTROL";
	else if (style & 0x0002)
		type = "RADIOBUTTON";
	else if (style & 0x0010)
		type = "HORZSLIDER";
	else if (style & 0x0008)
		type = "VERTSLIDER";
	else if (style & 0x0020)
		type = "SCROLLLISTBOX";
	else if (style & 0x8000)
		type = "COMBOBOX";
	else if (style & 0x0100)
		type = "PROGRESSBAR";
	else if (style & 0x0080)
		type = "STATICTEXT";
	else if (style & 0x0040)
		type = "ENTRYFIELD";
	else
		return NULL;

	GadgetCreateView view;
	source->snapshotCreateView(&view, true);
	view.m_idOrUser = id;

	void *userData = source->winGetUserData();
	void *data = NULL;
	if (userData)
	{
		Int size = 0;
		data = getDataTemplate(type, &size);
		if (data == NULL)
			return NULL;
		memcpy(data, userData, size);
	}
	return createGadget(type, data, &view, source);
}
