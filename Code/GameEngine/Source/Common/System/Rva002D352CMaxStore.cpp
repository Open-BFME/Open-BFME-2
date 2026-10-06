// cl: /Oy- /MD
//
// ?rva002D352C@Rva002D352C@@QAEXHH@Z retail 0x002D352C (42B).
// Max-store of a FramesPerSecond-scaled timeout into an 8-byte-stride slot
// at this+0x12C. Callers 0x002D381D 0x002D382E 0x002D383F each do
// mov ecx [ecx+0x10] then push 0/1/2 proving thiscall on the inner object at
// outer+0x10 with index 0..2 and seconds arg. Retail loads global
// FramesPerSecond at 0x00DBA4E8 (same as GameEngineFrameTiming) and keeps the
// maximum via pointer-select ternary. Owner unproven so honest-address class
// Rva002D352C. Flags /O1 /Oy- keep the ebp frame; /O1 alone goes frameless.
extern int g_009BA4E8;

#define FramesPerSecond g_009BA4E8
class Rva002D352C
{
public:
	void rva002D352C(int index, int seconds);
private:
	char m_pad[0x12C];
	struct Elem
	{
		int value;
		int pad;
	};
	Elem m_elems[4];
};
void Rva002D352C::rva002D352C(int index, int seconds)
{
	int *p = &m_elems[index].value;
	int v = FramesPerSecond * seconds;
	*p = *(v < *p ? p : &v);
}
