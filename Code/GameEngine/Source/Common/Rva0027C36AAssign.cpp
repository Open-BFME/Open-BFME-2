// cl: /MD
// Fix over the banked 0.94 attempt: the four 12-byte {int, float, int}
// records at +0x6C are copied through the record's own member-wise operator=
// (defined inline), not field by field in the loop; that is what makes cl copy
// the float through fld/fstp and walk the two arrays with retail's pointers.
// ??4Rva0027C36A@@QAEAAV0@ABV0@@Z @0x00085420 175B via Rva0027C36A assign group F12 plus int-float-int loop; callers pair ctor 0x27C36A with assign (0x281FC7 plus 0x281FD6)
// Evidence: stack temp 0xa8 at 0x00281FC1 ctor then assign from esi plus 0xc; 19 floats as 6 F12 plus 1; int[4] plus byte plus I12[4] plus S6[2] all match except middle float uses integer mov vs retail fld-fstp
struct F12 { float a; float b; float c; };
struct I12 { int a; float b; int c; I12 &operator=(const I12 &o) { a = o.a; b = o.b; c = o.c; return *this; } };
struct S6 { char d[6]; };
class Rva0027C36A
{
public:
	Rva0027C36A &operator=(const Rva0027C36A &other);
	F12 m_00;
	F12 m_0c;
	float m_18;
	F12 m_1c;
	F12 m_28;
	F12 m_34;
	F12 m_40;
	int m_4c;
	int m_50;
	int m_54;
	int m_58[4];
	unsigned char m_68;
	char m_pad69[3];
	I12 m_6c[4];
	S6 m_9c[2];
};
Rva0027C36A &Rva0027C36A::operator=(const Rva0027C36A &other)
{
	m_00 = other.m_00;
	m_0c = other.m_0c;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_28 = other.m_28;
	m_34 = other.m_34;
	m_40 = other.m_40;
	m_4c = other.m_4c;
	m_50 = other.m_50;
	m_54 = other.m_54;
	for (int i = 0; i < 4; i++)
		m_58[i] = other.m_58[i];
	m_68 = other.m_68;
	for (int i = 0; i < 4; i++)
		m_6c[i] = other.m_6c[i];
	for (int i = 0; i < 2; i++)
		m_9c[i] = other.m_9c[i];
	return *this;
}
