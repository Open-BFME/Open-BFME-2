// cl: /MD /EHsc /DNDEBUG
//
// ?rva000AF1C2@@YAXHHH@Z @0x000AF1C2 27B: three-int forwarder. Passes its
// three arguments plus the address of a 1-byte stack local to the pinned
// cdecl helper 0x000ADF1B (same forwarder family: that body adds a fifth
// trailing zero into 0x000AD8EB). Honest address-derived names; boundary
// verified (frame at 0xAF1C2, add esp + leave + ret at end).

struct Rva000ADF1BInput;
struct Rva000ADF1BOutput;
struct Rva000ADF1BIteratorTag;
Rva000ADF1BOutput *__cdecl Rva000ADF1BRangeForward(Rva000ADF1BInput *a, Rva000ADF1BInput *b, Rva000ADF1BOutput *c, const Rva000ADF1BIteratorTag &tag); // rowed 0x000ADF1B


// ?rva000AF1C2@@YAXHHH@Z
void __cdecl rva000AF1C2(int a, int b, int c)
{
	unsigned char tmp;
	(void)Rva000ADF1BRangeForward((Rva000ADF1BInput*)a, (Rva000ADF1BInput*)b, (Rva000ADF1BOutput*)c, *(const Rva000ADF1BIteratorTag*)&tmp);
}
