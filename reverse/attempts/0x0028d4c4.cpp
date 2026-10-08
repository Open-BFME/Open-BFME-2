// ?rva0028D4C4@Object@@QBE_NXZ
// partial score=0.9 date=2026-10-08
// cl: /MD
//
// ?rva0028D481@Object@@QBEHXZ @0x0028D481 (16B).
// Leaf Object reader: returns bit 7 of the dword at template+0x108
// ((template->field108 >> 7) & 1). Layout from retail: this+0x4 is the
// template pointer (same slot Object_isAbleToAttack.cpp documents),
// field at +0x108 is an unsigned dword so retail emits logical shr.
// Callers at 0x00261250 + 0x002612D5 + 0x005399F1. No donor name claimed,
// so the name keeps the address token with the proven Object owner.
//
// ?rva0028D282@Object@@QAEXPAX@Z @0x0028D282 (32B).
// Guarded forward to the helper at this+0x4C4: forwards the single void*
// arg to Gen_008F7B50::bfmeForward when the helper is present and the
// template byte at +0x10E lacks 0x20. Retail shape is mov eax,ecx plus
// helper null test plus template flag test plus tail jmp. Caller at
// 0x003958D5. Same honest Object naming as its file sibling.

struct Rva0028D481Template
{
	unsigned char m_pad[0x108];
	unsigned int m_field108;
	unsigned char m_pad10C[2];
	unsigned char m_byte10E;
};

class Gen_008F7B50
{
public:
	void bfmeForward(void *a0);
};

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);

	char m_data[0x4C];
};

class Rva00271C8A
{
public:
	void rva00271C8A(const int *a, const int *b);
};

bool __cdecl Rva00045473Equal(const void *a, const void *b);

class ModelConditionFlags
{
	int m_words[19];
};

class Drawable
{
public:
	void rva002791E7(const ModelConditionFlags &flags, unsigned int forceReplace, unsigned int b);
};

class Object
{
public:
	int rva0028D481() const;
	bool rva0028D491() const;
	bool rva0028D4C4() const;
	void rva0028D282(void *a0);
	void rva0028AE6D();
	void rva0028CFB2(const int *a, const int *b);
	void rva0028CFF5(const int *flags, bool forceReplace);

private:
	char m_pad00[4];
	Rva0028D481Template *m_template;
	char m_pad08[0x84 - 8];
	Drawable *m_drawable; // +0x84
	char m_pad88[0x10C - 0x88];
	char m_10C[0x4C];
	char m_pad158[0x4C4 - 0x10C - 0x4C];
	Gen_008F7B50 *m_helper;
};

int Object::rva0028D481() const
{
	return (m_template->m_field108 >> 7) & 1;
}

void Object::rva0028D282(void *a0)
{
	Gen_008F7B50 *helper = m_helper;
	if (helper != 0 && ((m_template->m_byte10E & 0x20) == 0))
		helper->bfmeForward(a0);
}

// ?rva0028CFB2@Object@@QAEXPBH0@Z @0x0028CFB2 (67B).
// Unlock callee for 25 free functions (6 ready). Evidence: rowed
// WeaponTemplateSetHead copy 0x00045455 plus rowed Rva00271C8A 0x00271C8A
// over this+0x10c plus rowed Equal 0x00045473 plus pinned Object
// notifier 0x0028AE6D with this; neighbours share /O1 /MD.

void Object::rva0028CFB2(const int *a, const int *b)
{
	WeaponTemplateSetHead tmp(*(const WeaponTemplateSetHead *)m_10C);
	((Rva00271C8A *)m_10C)->rva00271C8A(a, b);
	if (!Rva00045473Equal(&tmp, m_10C))
		rva0028AE6D();
}

// ?rva0028CFF5@Object@@QAEXPBH_N@Z @0x0028CFF5 (92B).
// Zero Hour's Object::replaceModelConditionFlags: snapshot the 19-word mask,
// replace it, and hand it to the Drawable (rowed 0x002791E7) when it changed
// or the caller forces a refresh.
void Object::rva0028CFF5(const int *flags, bool forceReplace)
{
	WeaponTemplateSetHead old(*(const WeaponTemplateSetHead *)m_10C);
	*(ModelConditionFlags *)m_10C = *(const ModelConditionFlags *)flags;
	if (!Rva00045473Equal(&old, m_10C) || forceReplace)
	{
		if (m_drawable)
			m_drawable->rva002791E7(*(const ModelConditionFlags *)m_10C, *(const unsigned int *)&forceReplace, 0);
	}
}

// Complete native query 0028D4C4..0028D4E0. The former 0028D4DD
// standalone zero returner was its local false-return block.
bool Object::rva0028D4C4() const
{
	if ((m_template->m_field108 & 0x80) && !rva0028D491())
		return true;
	return false;
}
