#ifndef ARMY_PLACER_COPY_RECORD_H
#define ARMY_PLACER_COPY_RECORD_H
#include "ArmyPlacerRecords.h"
// Existing 72-byte bit-copy provider view at 0x0037F551: two 32-byte
// records followed by the raw cost word and validity byte. Rva0037F8AC
// is the same storage passed by the native vector construct at 0x0037F71F.
// Original record class names remain unknown; no new layout is inferred.
class Rva0037F551
{
public:
	Rva0037F551 &rva0037F551(const Rva0037F551 &src);
private:
	Rva0037F51A m_a;
	Rva0037F51A m_b;
	int m_40;
	bool m_44;
};

#endif
