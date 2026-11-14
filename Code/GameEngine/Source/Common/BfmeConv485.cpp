// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv485.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBLD@@YGXPAX@Z 0x0029ACE3 (24B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
#include "../../Include/Common/BfmeSinkBLD.h"

class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

void __stdcall bfmeGoBLD(void *what)
{
	BfmeSinkBLD *sink = (BfmeSinkBLD *)theRadarWindowOverrideSource;
	if (sink != 0)
		sink->bfmeDoBLD(what, 0);
}
