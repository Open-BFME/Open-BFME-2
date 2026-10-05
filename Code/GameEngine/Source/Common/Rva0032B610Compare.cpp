// cl: /O1 /Oi /EHsc /MD
// ?Rva0032B610Compare@@YAHHH@Z @0x0032B610 31B chain via 0x0032AF02
// Evidence: caller 0x0032BF41 pushes two args and tests result ==0; callee rowed Rva0032AF02Compare takes (int int int) with third unused by 0x002AADB6; retail inlines memset 1 to xor+lea+stosb with /Oi and passes dword with garbage high bytes ignored by callee.
#include <string.h>
int __cdecl Rva0032AF02Compare(int a, int b, int c);
int __cdecl Rva0032B610Compare(int a, int b)
{
	int c;
	memset(&c, 0, 1);
	return Rva0032AF02Compare(a, b, c);
}
