// ?Rva005F88F4Get@@YAHH@Z
// partial score=0.91 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?Rva005F88F4Get@@YAHH@Z @0x005F88F4 44B evidence: arg null check plus global g_009FEF10 null check plus pinned Pathfinder-like lookup ?rva002B2579@Rva002BA8F1Logic@@QAEPAURva002B2579Result@@H@Z @0x002B2579 plus null check plus tail-jmp to rowed getter ?rva004E0625@Rva004E0625@@QBEHXZ @0x004E0625; callers unclaimed; unblocks 0x005F8920 0x005F8A0C 0x005F8A7E
class Rva002BA8F1Logic;
struct Rva002B2579Result;
class Rva004E0625;

class Rva002BA8F1Logic
{
public:
	Rva002B2579Result *rva002B2579(int arg);
};

class Rva004E0625
{
public:
	int rva004E0625() const;
};

extern Rva002BA8F1Logic *g_009FEF10;

// ?Rva005F88F4Get@@YAHH@Z present-unmatched
int __cdecl Rva005F88F4Get(int arg)
{
	Rva002BA8F1Logic *logic = g_009FEF10;
	if (arg == 0 || !logic)
		return 0;
	Rva002B2579Result *res = logic->rva002B2579(arg);
	if (res)
		return ((Rva004E0625 *)res)->rva004E0625();
	return 0;
}
