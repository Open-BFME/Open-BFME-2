// cl: /O1 /DNDEBUG /MD
// ?rva0028FC8F@Object@@QAEXXZ @0x0028FC8F 74B. Object method guarded on
// drawable at +0x84: builds two 0x4C WeaponTemplateSetHead masks on the stack
// through rowed builders 0x002C76B2 (out, kind at +0x350, 1) and 0x002C777E
// (out, kind), then forwards both to rowed Object::rva0028CFB2 0x0028CFB2.
// Evidence: callees all rowed; neighbours ObjectRva0028FC7F and
// Object_attemptHealing share /O1 /DNDEBUG /MD; +0x84 drawable slot matches
// ObjectRva0028D481 TU; 5 unclaimed callers wait on this body.
class WeaponTemplateSetHead
{
	char m_data[0x4C];
};

WeaponTemplateSetHead *__cdecl Rva002C76B2Build(WeaponTemplateSetHead *out, int a, int b);
WeaponTemplateSetHead *__cdecl rva002C777E(WeaponTemplateSetHead *out, int idx);

class Object
{
public:
	void rva0028FC8F();
	void rva0028CFB2(const int *a, const int *b);

private:
	char m_pad00[0x84];
	void *m_drawable; // +0x84
	char m_pad88[0x350 - 0x88];
	int m_kind; // +0x350
};

void Object::rva0028FC8F()
{
	if (m_drawable != 0) {
		int kind = m_kind;
		WeaponTemplateSetHead tmp1;
		Rva002C76B2Build(&tmp1, kind, 1);
		WeaponTemplateSetHead tmp2;
		rva0028CFB2((const int *)rva002C777E(&tmp2, kind), (const int *)&tmp1);
	}
}
