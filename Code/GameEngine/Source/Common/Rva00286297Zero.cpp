// cl: /O1 /DNDEBUG /MD
// ??0Rva00286297@@QAE@XZ @0x00286297 22B: zeroing ctor for 0x18-byte array element (six dwords). Evidence: called as ctor function pointer from 0x00286EC8 ??_L array construct of 4x0x18 at +0x10; no callees; neighbours share /O1.
class Rva00286297
{
public:
	Rva00286297();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

Rva00286297::Rva00286297() : m_00(0), m_04(0), m_08(0), m_0C(0), m_10(0), m_14(0)
{
}
