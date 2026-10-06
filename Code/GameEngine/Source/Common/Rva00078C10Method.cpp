// cl: /Ob0
// ?rva00078C10@Rva00078C10@@QAE_NPBV1@PAH1@Z @0x00078C10 114B
//
// Guarded LOD-index query: zero both out params, require the +0x18 handles to
// match and the +0x18 finish flag, then either keep zeros when
// TheGameLODManager+0x1788 is clear or fill them with (field at +8)%3.
// Identity: callees rowed ?rva000B49F9 (unsigned char) and
// ?get@Rva0055A88BDwordField (int); TheGameLODManager extern in use;
// three stack args (ret 0xC) with two int outs; honest-address class.
class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva000B49F9
{
public:
	unsigned char rva000B49F9();
};

class GameLODManager
{
public:
	char m_pad00[0x1788];
	int m_1788;
};

extern GameLODManager *TheGameLODManager;

class Rva00078C10
{
public:
	bool rva00078C10(Rva00078C10 const *other, int *out2, int *out3);
private:
	char m_pad00[8];
	Rva0055A88BDwordField *m_08;
	char m_pad0C[0x0C];
	Rva000B49F9 *m_18;
};

bool Rva00078C10::rva00078C10(Rva00078C10 const *other, int *out2, int *out3)
{
	*out3 = 0;
	*out2 = 0;
	if (m_18 != 0 && m_18 == other->m_18 && m_18->rva000B49F9())
	{
		if (TheGameLODManager->m_1788 == 0)
		{
			*out3 = 0;
			*out2 = 0;
			return true;
		}
		*out2 = m_08->get() % 3;
		*out3 = other->m_08->get() % 3;
		return true;
	}
	return false;
}
