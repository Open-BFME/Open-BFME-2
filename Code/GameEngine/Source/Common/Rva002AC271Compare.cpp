// cl: /O1 /Oi /EHsc /MD
// ?Rva002AC271Compare@@YAHHH@Z @0x002AC271 31B chain via 0x002ABC22
// Evidence: caller 0x002ACFC1 pushes two args and tests result ==0; callee rowed Rva002ABC22Compare takes (int int int) with third unused by 0x002AADB6; retail inlines memset 1 to xor+lea+stosb with /Oi and passes dword with garbage high bytes ignored by callee.
#include <string.h>
int __cdecl Rva002ABC22Compare(int a, int b, int c);
int __cdecl Rva002AC271Compare(int a, int b)
{
	int c;
	memset(&c, 0, 1);
	return Rva002ABC22Compare(a, b, c);
}
