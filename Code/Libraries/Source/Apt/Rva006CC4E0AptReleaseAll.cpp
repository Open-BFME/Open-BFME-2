// cl: /O1 /G7 /DNDEBUG /MD
//
// ?rva006CC4E0@@YAXXZ, retail 0x006CC4E0 (65 bytes): the Apt runtime's
// global teardown sequence. It releases the native object tables in a fixed
// order (rowed 0x008B8B80-style ReleaseAll/ReleaseGlobals helpers,
// AptDate::CleanNativeFunctions and the bfmeGo/d_ forwarders) and ends with
// a tail call to 0x006E97A0. Address-derived name; every callee is rowed.
class AptArray { public: static void CleanNativeFunctions(void); };
#include "AptDate.h"
void rva008A4630ReleaseGlobals();
void rva008A47B0ReleaseGlobals();
void bfmeGo1062B();
void rva008B2BD0ReleaseGlobals();
void bfmeGo1083A();
void bfmeGo1082C();
void bfmeGo1082B();
void rva008A48D0ReleaseGlobals();
void d_008acac0();
void rva008A98B0ReleaseAll();
void Rva006E97A0();

void rva006CC4E0()
{
	AptArray::CleanNativeFunctions();
	AptDate::CleanNativeFunctions();
	rva008A4630ReleaseGlobals();
	rva008A47B0ReleaseGlobals();
	bfmeGo1062B();
	rva008B2BD0ReleaseGlobals();
	bfmeGo1083A();
	bfmeGo1082C();
	bfmeGo1082B();
	rva008A48D0ReleaseGlobals();
	d_008acac0();
	rva008A98B0ReleaseAll();
	Rva006E97A0();
}
