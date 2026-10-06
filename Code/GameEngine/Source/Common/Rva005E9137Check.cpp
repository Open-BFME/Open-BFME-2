// cl: /O1 /MD
// ?Rva005E9137Check@@YAEPAVRva00318F42@@@Z @0x005E9137 44B
// Evidence: retail checks g_009FEF10 null then +0xF4 then Rva002B280C::check then tail to 0x00318F42.
// Callers at 0x005E9169 0x005E9180 test al as bool.
extern class Rva002BA8F1Logic *g_009FEF10;

struct Arg54;
class Rva00318F42;
class Mbr002E0B30
{
public:
	unsigned char pred();
};
class Rva002B280C
{
public:
	bool rva002B280C(struct Arg54 *a);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0xF4];
	int m_0F4;
};
unsigned char __cdecl Rva005E9137Check(class Rva00318F42 *a)
{
	class Rva002BA8F1Logic *logic = g_009FEF10;
	if (logic == 0)
		return 0;
	if (logic->m_0F4 != 0)
		return 0;
	if (((class Rva002B280C *)logic)->rva002B280C((struct Arg54 *)a))
		return ((class Mbr002E0B30 *)a)->pred();
	return 0;
}
