// Rva00391667: BuildAssistant::isLocationClearOfObjects' castle-range scan filter.
// Ctor 0x00391667 installs vftable 0x00C1A068, copies the point to +0x0C and
// clears the range at +0x08; slot 1 is allow 0x00261F35, rowed in
// Rva00261D2EFilter.cpp. The name is address-derived.
#ifndef CANONICAL_RVA00391667_H
#define CANONICAL_RVA00391667_H

#include "PartitionFilter.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Rva00391667 : public Rva000421C8
{
public:
	Rva00391667(const void *pos);
	virtual bool allow(Object *obj);
	float m_range;				// +0x08
	Coord3D m_pos;				// +0x0C
};

#endif // CANONICAL_RVA00391667_H
