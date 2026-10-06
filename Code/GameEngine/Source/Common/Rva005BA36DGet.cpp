// cl: /MD
// ?rva005BA36D@Rva005BA36D@@QAEPAVRva0054D8D8@@XZ @0x005BA36D 50B. ComboBox
// selected-pos to item-data to Rva0054D974 finder. Evidence: rowed Gadget
// GetSelectedPos 0x003228EB and GetItemData 0x00322981; rowed finder
// 0x0054D6C8 via global 0x00A05FB0; member GameWindow at +0x90; unblocks
// 0x005BB3A1.
class GameWindow;
void __cdecl GadgetComboBoxGetSelectedPos(GameWindow *gw, int *pos);
void *__cdecl GadgetComboBoxGetItemData(GameWindow *gw, int pos);

class Rva0054D8D8;
class Rva0054D974
{
public:
	Rva0054D8D8 *rva0054D6C8(int id);
};
extern Rva0054D974 *G00A05FB0;
// G00A05FB0: matched references place it at VA 0xe05fb0 (zero-filled .bss).
Rva0054D974 * G00A05FB0;

class Rva005BA36D
{
public:
	Rva0054D8D8 *rva005BA36D();
private:
	char m_pad00[0x90];
	GameWindow *m90;
};

Rva0054D8D8 *Rva005BA36D::rva005BA36D()
{
	int sel;
	GameWindow **pp = &m90;
	GadgetComboBoxGetSelectedPos(*pp, &sel);
	void *data = GadgetComboBoxGetItemData(*pp, sel);
	return G00A05FB0->rva0054D6C8((int)data);
}
