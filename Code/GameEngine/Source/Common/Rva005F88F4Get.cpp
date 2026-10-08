// cl: /DNDEBUG /MD
// ?Rva005F88F4Get@@YAHH@Z @0x005F88F4 44B evidence: same null-guard head as
// 0x005F88D6 (arg plus g_009FEF10 via pinned thiscall lookup
// ?rva002B2579@Rva002BA8F1Logic@@QAEPAURva002B2579Result@@H@Z @0x002B2579),
// then null-tested result tail-jmps to rowed getter
// ?rva004E0625@Rva004E0625@@QBEHXZ @0x004E0625. Resumed from banked partial
// (score 0.91): the ||-converged res=0 reproduces retail's jmp-over-xor
// with the early xor falling through into the result null test.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002B2579Result;

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

int __cdecl Rva005F88F4Get(int arg)
{
	Rva002BA8F1Logic *logic;
	Rva002B2579Result *res;
	if (arg == 0 || (logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)) == 0)
		res = 0;
	else
		res = logic->rva002B2579(arg);
	if (res)
		return ((Rva004E0625 *)res)->rva004E0625();
	return 0;
}
