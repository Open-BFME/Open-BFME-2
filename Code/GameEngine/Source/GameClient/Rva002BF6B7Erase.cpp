// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oy-
// ?rva002BF6B7@Rva002BF6B7@@QAEXPAX@Z @0x002BF6B7 31B
// Erase forwarding on the 0x00DFEF18 host: key is the int at obj+0x24, map is
// at +0x98. Evidence: same +0x98/+0x24 pair as Rva002BFA12 on the same
// global; callee 0x0054883B carries the rowed dup_0054883b twin whose
// object-symbol is hash_set<int>::erase plus the pinned
// ?eraseSlot@ObjectLookupMap@@QAEXPAH@Z (void thiscall, int* arg) used here;
// Rva002BFA12 already treats +0x98 as an ObjectLookupMap (findSlot). The
// dead arg slot is reused for the key (mov [ebp+8],eax then lea/push it).
class ObjectLookupMap
{
public:
	void eraseSlot(int *key);
};

class Rva002BF6B7
{
public:
	void rva002BF6B7(void *obj);

private:
	char m_pad[0x98];
	ObjectLookupMap m_map98;
};

void Rva002BF6B7::rva002BF6B7(void *obj)
{
	*(int *)&obj = *(int *)((char *)obj + 0x24);
	m_map98.eraseSlot((int *)&obj);
}
