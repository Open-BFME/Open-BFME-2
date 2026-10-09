// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// ?rva00423D2F@Rva00423D2FOwner@@QAEXVRva00421A16@@@Z @0x00423D2F (54B): thunk of the list sort 0x004236F5 (the
// STLport _S_sort over MiniList00421E1C with the nearer-point comparator Rva00421A16, merge rowed as
// Rva00421E1CMerge): the owner is the list, the comparator (three floats) is forwarded by value. Same shape as
// Rva004CED15Owner::rva004CED15 over Rva004CEB76 in Rva004CEB76ListSort.cpp. Target evidence: retail body and the
// sort's REL32 read byte for byte; names are address-derived.
struct MiniList00421E1C { void *head; };

class Rva00421A16
{
public:
	__forceinline ~Rva00421A16() {}
	__forceinline Rva00421A16(const Rva00421A16 &r) : x(r.x), y(r.y), z(r.z) {}
	float x;
	float y;
	float z;
};

void __cdecl Rva004236F5(MiniList00421E1C &list, Rva00421A16 comp);

class Rva00423D2FOwner
{
public:
	void rva00423D2F(Rva00421A16 comp);
};

void Rva00423D2FOwner::rva00423D2F(Rva00421A16 comp)
{
	Rva004236F5(*(MiniList00421E1C *)this, comp);
}
