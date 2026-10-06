// cl: -O1 -GR- -EHsc-
// ?Run@Rva005C3427@@QAEXXZ @0x005C3427 44B: getter-gated sound plus tail.
// Run rowed 0x5C792C getter; if result 1/3/5, play rowed PlaySound with
// Gui_PalantirCommandButtonDisabledClick and return; else tailcall pinned
// 0x5C33DD on this. All thiscall 0-arg (PlaySound cdecl 1-arg); switch as
// cmp/je chain per retail.
class Rva00005C792CPtrChaseField
{
public:
	int get() const;
};

void PlaySound(const char *label);

struct Rva005C33DD
{
	void rva005C33DD();
};

struct Rva005C3427
{
	void Run();
};

void Rva005C3427::Run()
{
	int v = ((Rva00005C792CPtrChaseField *)this)->get();
	if (v == 1 || v == 3 || v == 5) {
		PlaySound("Gui_PalantirCommandButtonDisabledClick");
		return;
	}
	((Rva005C33DD *)this)->rva005C33DD();
}
