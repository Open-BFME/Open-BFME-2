#pragma once
// Target-owned views from native store351570 and reconstruction35164E.
// Field offsets and accessed extents are retail facts; original type names
// and unobserved behavior remain unasserted. BFME1 6c1e0b51 supplies the
// AICommandParmsStorage semantic guide, not target identity proof.
#include "BfmeAICommandParameterView.h"

class Rva00351570
{
public:
	int m_00;
	int m_04;
	BfmeVec12 m_08;
	int m_14;
	int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	Rva0035149F m_24;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	Rva003427DD m_40;
	int m_BC;
	int m_C0;
	void rva00351570(const Rva00351570Src &src);
	void rva0035164E(Rva00351570Src &dest) const;
};
