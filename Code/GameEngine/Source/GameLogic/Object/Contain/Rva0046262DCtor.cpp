// cl: /DNDEBUG /MD
//
// ??0Rva0046262D@@QAE@PAXABVWeaponTemplateSetHead@@@Z, retail 0x0046262D, 29 bytes.
// Two-arg ctor just after SlaughterHordeContain slot129 (0x004625F0) in the
// 00462xxx page: first member (void* at +0) from *(void**)a plus
// WeaponTemplateSetHead at +0x4 copy-constructed from b via the rowed copy
// ctor 0x00045455. Declaration order (first then head) gives the retail
// store-before-call schedule with no placement-new null check; MSVC ctor
// returns this (mov eax,esi, ret 8). Evidence: address neighbours plus rowed
// callee plus single unclaimed caller at 0x00464962; class identity unproven
// so honest RVA class name, no invented class or method.

class WeaponTemplateSetHead
{
public:
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
};

class Rva0046262D
{
public:
	Rva0046262D(void *a, const WeaponTemplateSetHead &b);

private:
	void *m_first;
	WeaponTemplateSetHead m_head;
};

Rva0046262D::Rva0046262D(void *a, const WeaponTemplateSetHead &b)
	: m_first(*(void **)a), m_head(b)
{
}
