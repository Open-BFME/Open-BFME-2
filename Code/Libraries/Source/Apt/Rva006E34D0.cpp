// cl: /MD
//
// ?rva006E34D0@Rva006E34D0@@QAEXH@Z @0x006E34D0 88B
// Bounded int append with consecutive-dup guard plus data-pointer notify:
// if count>=cap return; if count>0 and arr[count-1]==v return;
// arr[count]=v; ++count; if ready flag set build 8-byte {value, v} record
// on the stack and call the slot function with (&record, 8).
// Evidence: unlock lane, callers 0x006E3530 (packs 3 ints then passes
// through ecx) and 0x006E3580 plus 0x006CEC90 and 0x006E4390; neighbour
// AptAnimationPoolDataBIL clearBIL/appendButtonToBIL; callback slots
// 0x00A17740/44 are .data pointers per Rva00891FA0Diagnostics.
extern int g_rva00891FA0Ready;
extern int g_rva00891FA0Value;
struct Rva00891FA0Record
{
	int value;
	int kind;
};
extern "C" void (__cdecl *Rva00891FA0SendRecord)(Rva00891FA0Record *, int);

#define G_Ready g_rva00891FA0Ready
#define G_Value g_rva00891FA0Value
#define G_Send Rva00891FA0SendRecord

class Rva006E34D0
{
public:
	void rva006E34D0(int v);
	void rva006E3580(int a, int b);
private:
	char m_pad0[0x3C];
	int m_count;
	int *m_arr;
	char m_pad1[0xAC - 0x44];
	int m_cap;
};

void Rva006E34D0::rva006E34D0(int v)
{
	if (m_count >= m_cap)
		return;
	if (m_count > 0 && m_arr[m_count - 1] == v)
		return;
	m_arr[m_count] = v;
	++m_count;
	int ready = G_Ready;
	if (ready) {
		Rva00891FA0Record r;
		r.value = G_Value;
		r.kind = v;
		(*G_Send)(&r, 8);
	}
}

// ?rva006E3580@Rva006E34D0@@QAEXHH@Z @0x006E3580 31B chain lane.
// Two-arg packer into the same bounded buffer: v = ((a << 15) | (b & 0x7FFF))
// << 2, appended via rva006E34D0 with ecx passed through (caller 0x006CC950
// supplies this the same way as for 0x006E3530).
void Rva006E34D0::rva006E3580(int a, int b)
{
	int v = (a << 15) | (b & 0x7FFF);
	v <<= 2;
	rva006E34D0(v);
}
