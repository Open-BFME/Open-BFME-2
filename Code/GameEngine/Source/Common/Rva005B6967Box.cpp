// cl: -Oy- -GR- -EHsc-
// ?InitGadgets@Manager@AptCreateAHero@@QAEXPADH0@Z @0x005B6967 158B: two-path validated set.
// Unless the third arg is null, strcmp it (imported) against two runtime
// tables; a first-table miss fills a 3-int buffer (9/0x2E/0x2D) for the
// pinned 3-arg callee, stamps +0x8 and runs the pinned helper, while a
// second-table miss fills (0x50/0x14) for the same callee plus the pinned
// 1-arg callee, stamps +0xC and runs the pinned tail body. The middle arg
// is unused. Targets from retail REL32; strcmp via plain C decl reusing
// the existing thunk pin; the two table names are retail's string literals
// ("SavedHeroList" 0x00C73640, "SavedHeroStats" 0x00C73630).
#include <string.h>
// Retail compares arg1 against two .rdata string cells (VA 0x00C73640 /
// 0x00C73630 = RVA 0x00873640 / 0x00873630, from the decoded push immediates).
extern const char g_rva00873640[];
const char g_rva00873640[16] = "SavedHeroList";
extern const char g_rva00873630[];
const char g_rva00873630[16] = "SavedHeroStats";

struct Rva005B6967Buf
{
	int x;
	int y;
	int z;
};

class GameWindow;

namespace AptCreateAHero {
class Manager;
}

class AptCreateAHero::Manager
{
public:
	char pad[8];
	char *m_8;
	char *m_C;

	void PopulateHeroList();
	void rva005B5F2E();
	void InitGadgets(char *a, int unused, char *c);
};

void GadgetListBoxSetColumnWidths(GameWindow *listbox, int numColumns, int *widths);
void GadgetListBoxAddMultiSelect(GameWindow *listbox);

void AptCreateAHero::Manager::InitGadgets(char *name, int unused, char *gadget)
{
	if (gadget == 0)
		return;
	Rva005B6967Buf buf;
	if (strcmp(name, g_rva00873640) == 0) {
		buf.x = 9;
		buf.y = 0x2e;
		buf.z = 0x2d;
		GadgetListBoxSetColumnWidths((GameWindow *)gadget, 3, &buf.x);
		m_8 = gadget;
		PopulateHeroList();
	} else {
		if (strcmp(name, g_rva00873630) != 0)
			return;
		buf.y = 0x50;
		buf.z = 0x14;
		GadgetListBoxSetColumnWidths((GameWindow *)gadget, 2, &buf.y);

		GadgetListBoxAddMultiSelect((GameWindow *)gadget);
		m_C = gadget;
		rva005B5F2E();
	}
}
