#pragma once

// Accessed views shared by the rowed Squad visitor and compact bodies.
// Gen_0018BC70 remains an address-derived owner; this does not identify its
// pointer element or recover the complete Squad class.
#include <vector>

class BfmeItemBF;
class BfmeVisitorBF;

class BfmeVecAK
{
public:
	BfmeItemBF **m_start;
	BfmeItemBF **m_finish;
	BfmeItemBF **m_end;
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
	void bfmeVisitAll(BfmeVisitorBF *visitor);

private:
	int m_head[4];
	BfmeVecAK m_vector;
};
