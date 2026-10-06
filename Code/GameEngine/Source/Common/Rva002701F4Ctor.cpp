// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva002701F4@@QAE@XZ @0x002701F4 45B
// Honest ctor for 0x90-byte member at +0x3AC in 0x2797BD holder.
// Evidence: 2x Matrix3D 0x30 via 0x000423C5 plus 4x Coord3D 0x0C via ehvec 0x00629512;
// rowed Coord3D ctor dtor ICF folds at 0x0047A6A9 0x000B3FD0; caller 0x00279ADB with next field at +0x43C.
class Matrix3D
{
public:
	Matrix3D();
private:
	unsigned char m_bytes[0x30];
};

struct Coord3D
{
	Coord3D();
	~Coord3D();
	float x;
	float y;
	float z;
};

class Rva002701F4
{
public:
	Rva002701F4();
private:
	Matrix3D m_00[2];
	Coord3D m_60[4];
};

Rva002701F4::Rva002701F4()
{
}
