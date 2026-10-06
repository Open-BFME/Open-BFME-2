// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Address-derived box predicate next to MinMaxAABoxClass::Init_Empty (0x7197D0,
// aabox.cpp) and CollisionMath::Overlap_Test (0x719830). Compares two packed
// Vector3 triples element-wise: returns 1 as soon as a lower bound reaches its
// matching upper bound. No callee and no relocation, so the body is the only
// evidence; identity is unproven and the name is this image's address.

class Rva00719800
{
public:
	int rva00719800(void) const;

	float m_rvaMin[3];		// +0x00
	float m_rvaMax[3];		// +0x0C
};

int Rva00719800::rva00719800(void) const
{
	// One short-circuit expression, not three guarded returns: retail puts the
	// return-1 block out of line and falls through to return 0.
	return (m_rvaMin[0] >= m_rvaMax[0]) ||
	       (m_rvaMin[1] >= m_rvaMax[1]) ||
	       (m_rvaMin[2] >= m_rvaMax[2]);
}
