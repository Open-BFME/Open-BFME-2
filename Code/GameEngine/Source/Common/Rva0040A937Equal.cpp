// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0040A937Equal@@YA_NPBVRva0040A7D5@@0@Z @0x0040A937 99B
// Evidence: chain lane; equal-size non-empty element-wise compare via 0x0040A7D5 row; callers at 0x0040ABBF 0x0040ABD4 0x0040ABE5 0x0040ABF6.
#include "../../Include/Common/Rva0040A7D5.h"

bool Rva0040A937Equal(const Rva0040A7D5 *lhs, const Rva0040A7D5 *rhs)
{
	unsigned int na = (unsigned int)(lhs->m_end - lhs->m_begin);
	unsigned int nb = (unsigned int)(rhs->m_end - rhs->m_begin);
	if (na != nb)
		return false;
	if (na == 0)
		return false;
	for (unsigned int i = 0; i < na; ++i) {
		if (lhs->GetStatNameKey((int)i) != rhs->GetStatNameKey((int)i))
			return false;
	}
	return true;
}
