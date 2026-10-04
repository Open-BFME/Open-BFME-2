// cl: /O2 /MD
// ?rva006E24D0@AptCIH@@QAE_NXZ @0x006E24D0 11B
// Evidence: leaf AptCIH forward with constant 0x9FC38 to rowed rva006E1F90; caller 0x006FB1D8; neighbours share flags.
class AptCIH
{
public:
	bool rva006E1F90(int v);
	bool rva006E24D0();
};

bool AptCIH::rva006E24D0()
{
	return rva006E1F90(0x9fc38);
}
