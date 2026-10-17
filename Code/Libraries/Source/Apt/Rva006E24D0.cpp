// cl: /MD
// ?rva006E24D0@AptCIH@@QAEHXZ @0x006E24D0 11B
// The tail jump preserves the full-width EAX result; the input dispatcher tests EAX.
// Evidence: leaf AptCIH forward with constant 0x9FC38 to rowed rva006E1F90; caller 0x006FB1D8; neighbours share flags.
class AptCIH
{
public:
	int rva006E1F90(int v);
	int rva006E24D0();
};

int AptCIH::rva006E24D0()
{
	return rva006E1F90(0x9fc38);
}
