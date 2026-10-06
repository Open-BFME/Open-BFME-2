// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva00372BA0ConditionalDispatcher.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva00372BA0ConditionalDispatcher@@YAXPAX0_N@Z 0x00397CEB (31B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

void j_00045c7d();
void j_00041eca();

typedef void (__stdcall *Rva00372BA0TrueHandler)(void *);

class Rva00371090Owner
{
public:
	void remove(void *value);
};

typedef void (Rva00371090Owner::*Rva00372BA0FalseHandler)(void *);

void Rva00372BA0ConditionalDispatcher(void *first, void *second, bool enabled)
{
	void *firstValue = first;
	Rva00371090Owner *secondValue = (Rva00371090Owner *)second;
	if (secondValue)
	{
		if (enabled)
		{
			void *value = firstValue;
			((Rva00372BA0TrueHandler)j_00045c7d)(value);
			return;
		}

		union { void *asVoid; Rva00372BA0FalseHandler asMember; } removeCast;
		removeCast.asVoid = (void *)j_00041eca;
		(secondValue->*removeCast.asMember)(firstValue);
	}
}
