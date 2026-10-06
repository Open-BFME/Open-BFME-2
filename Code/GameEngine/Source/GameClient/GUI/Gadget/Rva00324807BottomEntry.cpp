// cl: /DNDEBUG /MD
// Retail RVA 0x00324807, 27 bytes.
// Rva00324807, the null-guarded bottom-entry delegate for a listbox window:
// null window or null user data yields 0, else the reg-arg worker computes the
// entry with a tail jump. Called by GadgetListBoxAddEntryText. The true name
// is unknown (B1 keeps the equivalent as a static with no mangling), so the
// address-derived opaque name stands; the pin coexists with this row. The TU
// defines only this body.

class GameWindow
{
public:
	void *winGetUserData();
};

struct _ListboxData;
typedef struct _ListboxData ListboxData;

int __fastcall Rva00323F9C(ListboxData *list);

int Rva00324807(GameWindow *listbox)
{
	if (!listbox)
		return 0;
	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	if (!listData)
		return 0;
	return Rva00323F9C(listData);
}
