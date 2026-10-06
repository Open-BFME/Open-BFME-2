// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00153425Copy@@YAPAVRva00468520@@PAV1@00ABUTag@@@Z, retail 0x00153425, 38 bytes.
// Copy helper looping first to last calling rowed Init 0x4F6B7B then add 8 returning end.
// Evidence: push esi mov esi [esp+0x10] push edi mov edi [esp+0xC] jmp cmp edi [esp+0x10] jne push edi push esi call 0x4F6B7B pop ecx add 8; same FillN family as Rva0015344B 37B but range; callers 0x1534A7 0x15353B 0x153873 0x153907 0x153952.
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
Rva00468520 *__cdecl Rva00153425Copy(Rva00468520 *first, Rva00468520 *last, Rva00468520 *result, const Tag &tag)
{
	Rva00468520 *cur_result = result;
	Rva00468520 *cur_first = first;
	while (cur_first != last)
	{
		Rva004F6B7BInit(cur_result, cur_first);
		++cur_first;
		++cur_result;
	}
	return cur_result;
}
