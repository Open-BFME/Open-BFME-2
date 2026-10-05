// cl: /O1 /MD
// ?rva0021937D@Rva0021937D@@QAEXPAURva0021937DTarget@@@Z @0x0021937D 46B
// ?rva002193AB@Rva0021937D@@QAEXPAURva0021937DTarget@@@Z @0x002193AB 46B
// ?rva002193D9@Rva0021937D@@QAEXPAURva0021937DTarget@@@Z @0x002193D9 46B
// Null-guarded triple-call forwards: when the target is null the body is
// just the pops; else target->rva00407E94(), target->rva004089C7(memb, 1)
// with memb at +0x198/+0x194/+0x1A0, then target->rva004074CF(). All three
// callees are pinned; 0x004074CF already carries a CreateAHeroData file
// writer pin, noted but not adopted here. Owner and target identities are
// unproven; the shared shape and adjacent member slots justify one owner
// class with three methods.
class Rva0021937DTarget
{
public:
	void rva00407E94();
	void rva004089C7(int a, int b);
	void rva004074CF();
};

class Rva0021937D
{
	char m_pad[0x194];
	int m_194;
	int m_198;
	int m_19C;
	int m_1A0;
public:
	void rva0021937D(Rva0021937DTarget *u);
	void rva002193AB(Rva0021937DTarget *u);
	void rva002193D9(Rva0021937DTarget *u);
};

void Rva0021937D::rva0021937D(Rva0021937DTarget *u)
{
	if (!u)
		return;
	u->rva00407E94();
	u->rva004089C7(m_198, 1);
	u->rva004074CF();
}

void Rva0021937D::rva002193AB(Rva0021937DTarget *u)
{
	if (!u)
		return;
	u->rva00407E94();
	u->rva004089C7(m_194, 1);
	u->rva004074CF();
}

void Rva0021937D::rva002193D9(Rva0021937DTarget *u)
{
	if (!u)
		return;
	u->rva00407E94();
	u->rva004089C7(m_1A0, 1);
	u->rva004074CF();
}
