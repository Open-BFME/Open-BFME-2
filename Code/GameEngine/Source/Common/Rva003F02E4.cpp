// cl: /DNDEBUG /MD /GX-
//
// ?rva003F02E4@Rva003F02E4@@QAE_NXZ, retail 0x003F02E4, 82 bytes.
// Unlock lane: predicate on +0x13C==-1 then +0x11C flag then list
// +0x170/+0x174 of structs (+0x20 holder for rowed byte get plus +0x34
// gate); true if any get returns nonzero. Same flags as next ImageGet.
// Evidence: rowed ?get@Rva004E0605ByteChaseField@@QBEEXZ at 0x004E0605,
// callers 0x0020FCA4 0x00319637 0x003F0361 0x003F037E.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva004E0605ByteChaseField
{
public:
	unsigned char get() const;
};

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

class Rva002E2903Player : public Rva002E071E
{
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

struct Rva003F02E4Node
{
	char m_pad[0x20];
	Rva004E0605ByteChaseField *m_holder;
	char m_pad2[0x10];
	unsigned char m_34;
};

class Rva003F02E4
{
public:
	bool rva003F02E4();
	bool rva003F0336(const Rva002E071E *other);
private:
	unsigned char m_pad[0x11C];
	bool m_11C;
	char m_pad2[0x13C - 0x11D];
	int m_13C;
	char m_pad3[0x170 - 0x140];
	Rva003F02E4Node **m_170;
	Rva003F02E4Node **m_174;
};

bool Rva003F02E4::rva003F02E4()
{
	if (m_13C == -1)
		return false;
	if (m_11C != 0)
		return true;
	Rva003F02E4Node **pp = m_170;
	for (; pp != m_174; ++pp) {
		Rva003F02E4Node *n = *pp;
		Rva004E0605ByteChaseField *h = n->m_holder;
		if (h == 0)
			continue;
		if (n->m_34 != 0)
			continue;
		if (h->get() != 0)
			return true;
	}
	return false;
}

// ?rva003F0336@Rva003F02E4@@QAE_NPBVRva002E071E@@@Z, retail 0x003F0336, 56 bytes.
// Chain lane: calls rowed 0x003F02E4 just landed; find 0x002B51F8 via g_009FEF10
// with m_13C and null index, then rowed rva002E071E 0x002E071E compare.
// Evidence: callers 0x0020FF46 0x0020FFDA in 0x0020FDDF; prev 0x003F02E4 same TU flags.
bool Rva003F02E4::rva003F0336(const Rva002E071E *other)
{
	Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(m_13C, 0);
	if (p == 0)
		return false;
	if (!p->rva002E071E(other))
		return rva003F02E4();
	return false;
}
