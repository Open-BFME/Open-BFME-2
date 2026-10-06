// cl: /MD
// ?Rva0070B5D0Check@@YA_NXZ retail 0x0070B5D0 (72B). Validates the Apt string
// pool's saConstant table at 0x00E18388..0x00E18650 (178 EAStringC entries):
// every entry non-empty and strictly ascending by the rowed
// ?compare008B4260@Rva008B4260StringRef@@QBEHABU1@@Z body at 0x006D36C0, with
// the last entry's comparison skipped. The table and its end global are already
// recovered in Rva0070D9F0Shutdown.cpp; this body is address-derived.

class EAStringC
{
public:
	void *m_pData;
	bool IsEmpty() const;
};

struct Rva008B4260StringRef
{
	int compare008B4260(const Rva008B4260StringRef &other) const;
};

extern EAStringC saConstantAtE18388[];
extern EAStringC g_00E18650;

bool Rva0070B5D0Check()
{
	int i = 0;
	EAStringC *p = saConstantAtE18388;
	do
	{
		if (p->IsEmpty())
			return false;
		++i;
		if (i < 0xb2)
		{
			if (((Rva008B4260StringRef *)p)->compare008B4260(*(Rva008B4260StringRef *)(p + 1)) >= 0)
				return false;
		}
		++p;
	} while ((int)p < (int)&g_00E18650);
	return true;
}
