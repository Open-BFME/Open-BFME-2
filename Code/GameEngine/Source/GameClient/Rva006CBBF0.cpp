// cl: /O1 /DNDEBUG /MD /EHsc
//
// The 28B target body at 0x006CBBF0 clears eight dwords at offsets 0x00..0x1C.
// deleted_rows.csv retires the old NodeMotionStruct identity here; the BFME1
// EyeTowerHead constructor is only a same-shape lead, so this stays opaque.

struct Rva006CBBF0
{
	Rva006CBBF0();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
};

Rva006CBBF0::Rva006CBBF0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}
