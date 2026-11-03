// cl: /O1 /arch:SSE /G7 /MD
// ?rva0052633A@Impl@InGameHeroSelectInterface@@QAEXPBD@Z, retail 0x0052633A
// (8 bytes, RET 4): a one-argument callback on the hero-select interface's
// Impl that ignores its text argument and runs the rowed
// Impl::SelectAllHeroes 0x00525E55, the shape of the rowed Apt callback
// AptSkirmish::rva0052174E. The callback's original name is not established.
#include "../../../../../Include/GameClient/InGameHeroSelectInterface.h"

void InGameHeroSelectInterface::Impl::rva0052633A(const char *)
{
	SelectAllHeroes();
}
