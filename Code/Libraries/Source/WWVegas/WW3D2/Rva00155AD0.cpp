// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// ?rva00155AD0@Rva00155AD0@@QAEXXZ at 0x00155AD0 47B: thiscall method with array at +0x38 count at +0x44.
// Donor: none. Evidence: callers UNCLAIMED FUN_00505216 and FUN_00506405; callees pin 0x00154FD0 row 0x00118810 pin 0x00118F50 row 0x001188A0.

class Rva00154FD0
{
public:
	void rva00154FD0();
};

class Rva00118F50
{
public:
	void rva00118F50();
};

void __cdecl Rva00118810();
void __cdecl Rva001188A0();

struct Rva00155AD0Entry
{
	Rva00118F50 *obj;
	void *second;
};

class Rva00155AD0
{
public:
	void rva00155AD0();
private:
	char m_pad[0x38];
	Rva00155AD0Entry *m_array; // +0x38
	char m_pad2[8]; // +0x3C
	int m_count; // +0x44
};

void Rva00155AD0::rva00155AD0()
{
	((Rva00154FD0 *)this)->rva00154FD0();
	Rva00118810();
	for (int i = 0; i < m_count; ++i) {
		m_array[i].obj->rva00118F50();
	}
	Rva001188A0();
}
