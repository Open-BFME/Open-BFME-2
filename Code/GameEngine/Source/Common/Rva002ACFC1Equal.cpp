// cl: /DNDEBUG /MD
// ?Rva002ACFC1Equal@@YA_NHH@Z @0x002ACFC1 21B chain via 0x002AC271
// Evidence: calls rowed Rva002AC271Compare with two args and returns result ==0 via neg/sbb/inc; callers at 0x002AD3CB 0x002B0158 0x002B0442.
int __cdecl Rva002AC271Compare(int a, int b);
bool __cdecl Rva002ACFC1Equal(int a, int b)
{
	return Rva002AC271Compare(a, b) == 0;
}
