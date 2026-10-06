// cl: /MD
// ?rva004E38B9@Rva000C0513@@QAEXI@Z @0x004E38B9 33B
// Shrink wrapper over Rva000C0513::rva000C0513 at 0x000C0513: forwards this in
// ecx plus uint arg at +8 plus an uninitialized 12B Coord3D temp copied via
// movsd x3 for the by-value fill. Evidence: ecx passthrough to rowed callee
// of same class, ret 4 single uint, caller at 0x004E3B13, prev/next flags.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva000C0513
{
public:
	void rva004E38B9(unsigned int n);
	void rva000C0513(unsigned int n, Coord3D val);
};

void Rva000C0513::rva004E38B9(unsigned int n)
{
	Coord3D val;
	rva000C0513(n, val);
}
