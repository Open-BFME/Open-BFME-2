// cl: /O1 /DNDEBUG /MD
// ?Rva0032BF39Equal@@YA_NHH@Z @0x0032BF39 21B chain via 0x0032B610
// Evidence: caller 0x0032FB9E in 617B body; retail pushes two args calls rowed Compare wrapper neg-sbb-inc booleanizes ==0 with pop-ecx stack cleaning per Rva000B3EECNotEqual.
int __cdecl Rva0032B610Compare(int a, int b);
bool __cdecl Rva0032BF39Equal(int a, int b)
{
	return Rva0032B610Compare(a, b) == 0;
}
