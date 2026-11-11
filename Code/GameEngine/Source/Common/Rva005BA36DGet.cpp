// cl: /MD
// ?rva005BA36D@AptOnlineQuickMatch@@QAEPAVRva0054D8D8@@XZ @0x005BA36D 50B. ComboBox
// selected-pos to item-data to Rva0054D974 finder. Evidence: rowed Gadget
// GetSelectedPos 0x003228EB and GetItemData 0x00322981; rowed finder
// 0x0054D6C8 via global 0x00A05FB0; member GameWindow at +0x90; unblocks
// 0x005BB3A1.
class GameWindow;
void __cdecl GadgetComboBoxGetSelectedPos(GameWindow *gw, int *pos);
void *__cdecl GadgetComboBoxGetItemData(GameWindow *gw, int pos);

class Rva0054D8D8;
#include "../../Include/Common/Rva0054D974.h"
extern Rva0054D974 *TheLadderList;
// TheLadderList (formerly the address-named G00A05FB0): matched references place it at VA 0xe05fb0 (zero-filled .bss);
// PeerDefs.cpp creates and deletes it under this name.
Rva0054D974 * TheLadderList;

class AptOnlineQuickMatch
{
public:
	Rva0054D8D8 *rva005BA36D();
private:
	char m_pad00[0x90];
	GameWindow *m90;
};

Rva0054D8D8 *AptOnlineQuickMatch::rva005BA36D()
{
	int sel;
	GameWindow **pp = &m90;
	GadgetComboBoxGetSelectedPos(*pp, &sel);
	void *data = GadgetComboBoxGetItemData(*pp, sel);
	return TheLadderList->rva0054D6C8((int)data);
}
