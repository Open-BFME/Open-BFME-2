// cl: /DNDEBUG /MD
// ?Rva005F88D6Get@@YAHH@Z @0x005F88D6 30B evidence: arg null check plus
// global g_009FEF10 null check plus pinned thiscall lookup
// ?rva002B2579@Rva002BA8F1Logic@@QAEPAURva002B2579Result@@H@Z @0x002B2579
// whose pointer result is returned directly; sibling head of 0x005F88F4.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002B2579Result;

class Rva002BA8F1Logic
{
public:
	Rva002B2579Result *rva002B2579(int arg);
};

int __cdecl Rva005F88D6Get(int arg)
{
	Rva002BA8F1Logic *logic;
	if (arg == 0 || (logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)) == 0)
		return 0;
	return (int)logic->rva002B2579(arg);
}
