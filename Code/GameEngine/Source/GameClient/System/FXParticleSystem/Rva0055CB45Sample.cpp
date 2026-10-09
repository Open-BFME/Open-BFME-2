// cl: /MD
// ?rva0055CB45@Rva0055CB45@@QAE?AUCoord3D0055CB45@@IIII@Z @0x0055CB45 24B:
// point emission volume sample. Evidence: slot 7 of the PointEmissionVolumeModule
// vtable 0x0081C730 (also slot 7 of 0x0081CB50 and 0x0081D028), the slot the
// box volume fills with its sample 0x0055D0D5 (Rva0055D0D5Sample.cpp, same
// four-argument hidden-return ABI, RET 0x14). A point volume emits at its
// origin: the returned position is zero. Class and method keep the box
// precedent's address-derived spelling.

struct Coord3D0055CB45
{
	Coord3D0055CB45(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	float x;
	float y;
	float z;
};

class Rva0055CB45
{
public:
	Coord3D0055CB45 rva0055CB45(unsigned int, unsigned int, unsigned int, unsigned int);
};

Coord3D0055CB45 Rva0055CB45::rva0055CB45(unsigned int, unsigned int, unsigned int, unsigned int)
{
	return Coord3D0055CB45(0.0f, 0.0f, 0.0f);
}
