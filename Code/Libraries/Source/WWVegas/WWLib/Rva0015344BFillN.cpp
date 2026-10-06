// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0015344BFillN@@YAPAVRva00468520@@PAV1@IABV1@ABUTag@@@Z, retail 0x0015344B, 37 bytes.
// FillN helper looping count times calling rowed Init 0x4F6B7B then add 8 dec jne returning end.
// Evidence: push esi mov esi [esp+8] push edi mov edi [esp+0x10] test jbe push [esp+0x14] push esi call 0x4F6B7B pop ecx add esi 8 dec edi pop ecx jne; same shape as Rva0014F5ABFillN 40B; caller 0x153934 with 4 pushes and add esp 0x10.
struct Rva00468520Obj
{
	int m_00;
	int m_04;
};
class Rva00468520
{
	Rva00468520Obj *m_00;
	int m_04;
public:
	Rva00468520 *set(const Rva00468520 *src);
};
void __cdecl Rva004F6B7BInit(Rva00468520 *dst, const Rva00468520 *src);
struct Tag
{
	char x;
};
Rva00468520 *__cdecl Rva0015344BFillN(Rva00468520 *result, unsigned int count, const Rva00468520 &value, const Tag &tag)
{
	Rva00468520 *cur = result;
	for (; count > 0; --count)
	{
		Rva004F6B7BInit(cur, &value);
		cur = (Rva00468520 *)((char *)cur + 8);
	}
	return cur;
}
