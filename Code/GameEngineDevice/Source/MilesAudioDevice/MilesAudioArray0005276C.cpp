// cl: /O1 /arch:SSE /G7 /EHsc /DNDEBUG /MD
// Native52751..5276C and5276C..5277C call the matched MSVC71 vector
// ctor/dtor iterators with count5 and stride16. Constructor callback VA
// 451CA2 is a 24B float3-zero/byte-zero constructor ending at451CBA;
// destructor callback is the shared empty RET at4B3FD0. Target callbacks,
// stride, count and measured fields establish this opaque array view.
// Original element/array owner names remain unknown; no Miles type claim.
#include "../../Include/Rva00051CA2.h"
class ScreenToTerrainSet {
public:
    ScreenToTerrainSet();
    ~ScreenToTerrainSet();
private:
    Rva00051CA2 slots[5];
};
Rva00051CA2::Rva00051CA2() : x(0.0f), y(0.0f), z(0.0f), active(false) {}
ScreenToTerrainSet::ScreenToTerrainSet() {}
// Select-any like the consumer copy in MilesAudioManager.cpp so the two
// identical 16B bodies fold instead of duplicating at link time.
inline ScreenToTerrainSet::~ScreenToTerrainSet() {}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitScreenToTerrainSetDtor@@YAXPAVScreenToTerrainSet@@@Z absent-from-retail
void bfmeEmitScreenToTerrainSetDtor(ScreenToTerrainSet *p)
{
	p->ScreenToTerrainSet::~ScreenToTerrainSet();
}
