// cl: /O2 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0046247D@Rva0046247D@@QAEXAAURva0046247DPair@@@Z @0x0046247D 26B.
// Conditional pair out-copy: first = this ? this+0x20 : 0 via mov/neg/lea/sbb/and,
// second = this+0x54 via in-place add. Writes both to the caller's out Pair, ret 4.
// Evidence: callers at 0x004631FA (SlaughterHordeContain slot 96) and 0x0046333B both
// do lea ecx,[esi-0x20] then call and consume the second dword as a list head;
// 0x00464286 (OpenContain slot 18) calls it for two outs. Prev/next are Disp frameless
// getters with the same defaults. No donor; identity is honest-address Rva.
// No // cl: line (defaults /O2 match the frameless 26-byte shape).
struct Rva0046247DPair
{
	void *first;
	void *second;
};
class Rva0046247D
{
public:
	void rva0046247D(Rva0046247DPair &result);
};
void Rva0046247D::rva0046247D(Rva0046247DPair &result)
{
	void *base = this;
	char *field = (char *)base + 0x20;
	result.first = base ? field : 0;
	result.second = (char *)base + 0x54;
}

#include "../../Include/GameLogic/ContainmentListView.h"
// Return-aware ABI view: native47778B first reserves the one-word list
// result then supplies an eight-byte descriptor buffer to46247D. EAX from
// the complete helper names that descriptor and feeds the owned36AE51
// member. The hidden return buffer and two writes are target evidence;
// original class/method names and declaration syntax remain unknown.
// This view is a complete byte-and-relocation twin of the existing out-copy
// owner, retained for its existing consumers. Neither adds unique bytes.
class Rva0046247DDescriptor {
public:
    Rva0036AE51ListView rva0046247D();
};
Rva0036AE51ListView Rva0046247DDescriptor::rva0046247D()
{
    Rva0036AE51ListView result;
    Rva0036AE51ListView &out=result;
    void *base=this;
    char *field=(char *)base+0x20;
    out.a=base ? field : 0;
    out.b=(ContainmentList *)((char *)base+0x54);
    return result;
}
