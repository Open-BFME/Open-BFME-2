// cl: /DNDEBUG /MD
// ??0Rva00286297@@QAE@XZ @0x00286297 22B: zeroing ctor for 0x18-byte array element (six dwords). Evidence: called as ctor function pointer from 0x00286EC8 ??_L array construct of 4x0x18 at +0x10; no callees; neighbours share /O1.
typedef int Int;
struct Rva00286297
{
	Rva00286297();
	~Rva00286297();
	Int unknown00, unknown04;
	Int fuel;
	unsigned int field18, field00, field10;
};

Rva00286297::Rva00286297() : unknown00(0), unknown04(0), fuel(0), field18(0), field00(0), field10(0)
{
}
