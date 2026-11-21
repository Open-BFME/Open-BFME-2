// cl: /Oy- /DNDEBUG /MD /Oi-

// AptMpGameSetup gadget initialization callback, retail 0x0043EB1D (420B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/MpGameSetupOnInitGadget.cpp
// (donor name AptMpGameSetup::_bfme_onInitGadget, BFME1 0x00525AB0; BFME2 name
// InitGadgets from WorldBuilder AptMpGameSetup.cpp:1396-1449 and the retail
// "MpGameSetup::InitGadgets" string). BFME2 target evidence
// (all retail-measured): no GameType/MapType branches and no mapListReady
// gate; the MapList branch stores the window at +0x394 and applies five
// column widths {8, 2, 0x46, 10, 10}; the name parses via the msvcr71 sscanf
// import with "%d" into an unsigned index (rejected when != 1 or > 8); the
// leaf after the last marker selects Player (+0x2D4, plus listbox tooltip
// 0x83DF71), PlayerTemplate (+0x334), Team (+0x314), Color (+0x2F4 via the
// rowed list<int> const_iterator ctor), Handicap (+0x354) or Hero (+0x374);
// every taken branch falls into the hide tail (index >= 6 with the +0x7C
// flag set hides the window). The AptMpGameSetup screen exists in BFME2
// (AptMpGameSetup::InitGadgets dispatch names in .rdata); the method name is
// the BFME1 donor identity for this same role and gadget-name set.

#include <string.h>
#include <stdio.h>

class WinInstanceData;

#include "../../../Include/GameClient/Bfme2GameWindow.h"

typedef void (*GameWinTooltipFunc)(GameWindow *window, WinInstanceData *data, unsigned int flags);

void __cdecl GadgetComboBoxReset(GameWindow *window);
GameWindow *__cdecl GadgetComboBoxGetListBox(GameWindow *window);
void __cdecl GadgetListBoxSetColumnWidths(GameWindow *window, int count, int *widths);
const char *__cdecl bfmePathLeafAfterMarker(const char *path);

namespace _STL
{
	template <class _Tp> struct _List_node;
	template <class _Tp> struct _Const_traits;
	template <class _Tp, class _Traits> struct _List_iterator
	{
		_List_iterator(_List_node<_Tp> *node);

	private:
		void *m_node;
	};
	typedef _List_iterator<int, _Const_traits<int> > ListIntConstIterator;
}

#include "../../../Include/GameClient/AptMpGameSetup.h"

// ?InitGadgets@AptMpGameSetup@@QAEXPBDPAXPAVGameWindow@@@Z
void AptMpGameSetup::InitGadgets(const char *name, void *, GameWindow *window)
{
	if (window == 0)
		return;

	if (strcmp(name, "MapList") == 0)
	{
		field394 = window;
		int widths[5] = { 8, 2, 0x46, 10, 10 };
		GadgetListBoxSetColumnWidths(window, 5, widths);
		return;
	}

	unsigned int index;
	if (sscanf(name, "%d", &index) != 1 || index > 8)
		return;

	const char *leaf = bfmePathLeafAfterMarker(name);
	if (strcmp(leaf, "Player") == 0)
	{
		GadgetComboBoxReset(window);
		field2d4[index] = window;
		GadgetComboBoxGetListBox(window)->winSetTooltipFunc(&AptMpGameSetup::PlayerTooltip);
	}
	else if (strcmp(leaf, "PlayerTemplate") == 0)
	{
		GadgetComboBoxReset(window);
		field334[index] = window;
	}
	else if (strcmp(leaf, "Team") == 0)
	{
		GadgetComboBoxReset(window);
		field314[index] = window;
	}
	else if (strcmp(leaf, "Color") == 0)
	{
		GadgetComboBoxReset(window);
		// Explicit constructor call (MSVC extension): placement new via
		// operator new always emits a null check under MSVC 7.1 (retail's
		// own stlport _Construct at 0x3FA3D3 keeps its test/je), while
		// retail here calls the iterator ctor directly with no check, so
		// the body reconstructs the color slot in place this way.
		((_STL::ListIntConstIterator *)field2f4)[index]._STL::ListIntConstIterator::ListIntConstIterator(
			(_STL::_List_node<int> *)window);
	}
	else if (strcmp(leaf, "Handicap") == 0)
	{
		GadgetComboBoxReset(window);
		field354[index] = window;
	}
	else if (strcmp(leaf, "Hero") == 0)
	{
		GadgetComboBoxReset(window);
		field374[index] = window;
	}
	else
		return;

	if (index >= 6 && field7c == 1)
		window->winHide(true);
}
