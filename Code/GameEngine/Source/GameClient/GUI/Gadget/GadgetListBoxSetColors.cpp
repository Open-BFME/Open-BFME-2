// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Clean C++ donor: open-bfme-1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c,
// game/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBoxSetColors.cpp.
// BFME 2 RVA 0x003240A6..0x0032431F, 633 bytes. Direct callers are the
// recovered gadget appearance initializer and GadgetComboBoxSetColors.
// Retail uses six out-of-line selected-thumb color getters; retain their
// existing owners even where older names confuse color with border color.
// The donor supplies color propagation semantics. Target loads independently
// prove the child offsets and draw-array layout below. No new pins are needed.
// BFME's ListboxData child slots are at +0x1c/+0x20/+0x24, four bytes after
// the vendored ZH declaration.  The retail body reads GameWindow's draw-data
// arrays at +0x48/+0xb4/+0x120 inline, through the canonical m_instData.
// The list-box child-slot view stays TU-local: the shared ZH ListboxData
// declaration would move already matched GadgetListBox bodies.

typedef int Color;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

struct BFMEListboxDataView
{
	// Retail xrefs and the matched BFME list-box helpers establish the child
	// slots below; the preceding BFME-only portion is not used by this body.
	unsigned char m_unreconstructed_00[0x1c];
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
};

class GameWindow;
int GadgetSliderGetEnabledSelectedThumbBorderColor(GameWindow *);
class BfmeThingDEA;
unsigned int bfmeGoDEA(BfmeThingDEA *);
class GameWindow;
int GadgetSliderGetDisabledSelectedThumbBorderColor(GameWindow *);
class BfmeThingDEB;
unsigned int getColor(BfmeThingDEB *);
class GameWindow;
int GadgetSliderGetHiliteSelectedThumbBorderColor(GameWindow *);
class BfmeThingDEC;
unsigned int bfmeGoDEC(BfmeThingDEC *);

void GadgetListBoxSetColors(GameWindow *listbox,
	Color enabledColor,
	Color enabledBorderColor,
	Color enabledSelectedItemColor,
	Color enabledSelectedItemBorderColor,
	Color disabledColor,
	Color disabledBorderColor,
	Color disabledSelectedItemColor,
	Color disabledSelectedItemBorderColor,
	Color hiliteColor,
	Color hiliteBorderColor,
	Color hiliteSelectedItemColor,
	Color hiliteSelectedItemBorderColor)
{
	BFMEListboxDataView *listboxData =
		(BFMEListboxDataView *)listbox->winGetUserData();

	listbox->winSetEnabledColor(0, enabledColor);
	listbox->winSetEnabledBorderColor(0, enabledBorderColor);
	listbox->winSetEnabledColor(1, enabledSelectedItemColor);
	listbox->winSetEnabledBorderColor(1, enabledSelectedItemBorderColor);
	listbox->winSetDisabledColor(0, disabledColor);
	listbox->winSetDisabledBorderColor(0, disabledBorderColor);
	listbox->winSetDisabledColor(1, disabledSelectedItemColor);
	listbox->winSetDisabledBorderColor(1, disabledSelectedItemBorderColor);
	listbox->winSetHiliteColor(0, hiliteColor);
	listbox->winSetHiliteBorderColor(0, hiliteBorderColor);
	listbox->winSetHiliteColor(1, hiliteSelectedItemColor);
	listbox->winSetHiliteBorderColor(1, hiliteSelectedItemBorderColor);

	GameWindow *slider = listboxData->slider;
	if (slider)
	{
		GameWindow *upButton = listboxData->upButton;
		GameWindow *downButton = listboxData->downButton;

		slider->winSetEnabledColor(0, listbox->m_instData.m_enabledDrawData[0].color);
		slider->winSetEnabledBorderColor(0, listbox->m_instData.m_enabledDrawData[0].borderColor);
		slider->winSetDisabledColor(0, listbox->m_instData.m_disabledDrawData[0].color);
		slider->winSetDisabledBorderColor(0, listbox->m_instData.m_disabledDrawData[0].borderColor);
		slider->winSetHiliteColor(0, listbox->m_instData.m_hiliteDrawData[0].color);
		slider->winSetHiliteBorderColor(0, listbox->m_instData.m_hiliteDrawData[0].borderColor);

		upButton->winSetEnabledColor(0, slider->m_instData.m_enabledDrawData[0].color);
		upButton->winSetEnabledBorderColor(0, slider->m_instData.m_enabledDrawData[0].borderColor);
		upButton->winSetEnabledColor(1, GadgetSliderGetEnabledSelectedThumbBorderColor(slider));
		upButton->winSetEnabledBorderColor(1, bfmeGoDEA(reinterpret_cast<BfmeThingDEA *>(slider)));
		upButton->winSetDisabledColor(0, slider->m_instData.m_disabledDrawData[0].color);
		upButton->winSetDisabledBorderColor(0, slider->m_instData.m_disabledDrawData[0].borderColor);
		upButton->winSetDisabledColor(1, GadgetSliderGetDisabledSelectedThumbBorderColor(slider));
		upButton->winSetDisabledBorderColor(1, getColor(reinterpret_cast<BfmeThingDEB *>(slider)));
		upButton->winSetHiliteColor(0, slider->m_instData.m_hiliteDrawData[0].color);
		upButton->winSetHiliteBorderColor(0, slider->m_instData.m_hiliteDrawData[0].borderColor);
		upButton->winSetHiliteColor(1, GadgetSliderGetHiliteSelectedThumbBorderColor(slider));
		upButton->winSetHiliteBorderColor(1, bfmeGoDEC(reinterpret_cast<BfmeThingDEC *>(slider)));

		downButton->winSetEnabledColor(0, slider->m_instData.m_enabledDrawData[0].color);
		downButton->winSetEnabledBorderColor(0, slider->m_instData.m_enabledDrawData[0].borderColor);
		downButton->winSetEnabledColor(1, GadgetSliderGetEnabledSelectedThumbBorderColor(slider));
		downButton->winSetEnabledBorderColor(1, bfmeGoDEA(reinterpret_cast<BfmeThingDEA *>(slider)));
		downButton->winSetDisabledColor(0, slider->m_instData.m_disabledDrawData[0].color);
		downButton->winSetDisabledBorderColor(0, slider->m_instData.m_disabledDrawData[0].borderColor);
		downButton->winSetDisabledColor(1, GadgetSliderGetDisabledSelectedThumbBorderColor(slider));
		downButton->winSetDisabledBorderColor(1, getColor(reinterpret_cast<BfmeThingDEB *>(slider)));
		downButton->winSetHiliteColor(0, slider->m_instData.m_hiliteDrawData[0].color);
		downButton->winSetHiliteBorderColor(0, slider->m_instData.m_hiliteDrawData[0].borderColor);
		downButton->winSetHiliteColor(1, GadgetSliderGetHiliteSelectedThumbBorderColor(slider));
		downButton->winSetHiliteBorderColor(1, bfmeGoDEC(reinterpret_cast<BfmeThingDEC *>(slider)));
	}
}
