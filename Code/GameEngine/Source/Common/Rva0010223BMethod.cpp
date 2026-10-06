// cl: /MD /EHs-c-
//
// ?rva0010223B@Rva0010223B@@QAEXXZ @0x0010223B 36B.
// Chain via just-landed 0x00102087; null-check m_00 then m_00->rva00116496
// then this->rva00102026 via cast then clear vector at +4 via rva00102087.
// Evidence: packet disassembly je on [esi] then calls 0x00116496 0x00102026
// 0x00102087 with lea ecx [esi+4] pushes [esi+8] [esi+4]; callees all rowed;
// callers 0x000B0743 0x001022CE 0x001022F8; unblocks 0x001022F5 0x000B071D;
// prev Rva00102215Singleton next Rva0010225FMethod same flags.
struct EvaMessageInfo
{
	char m_unported[28];
};

class Rva00116496
{
public:
	void rva00116496();
};

class Rva00102026
{
public:
	void rva00102026();
};

class Rva00102087
{
public:
	EvaMessageInfo *rva00102087(EvaMessageInfo *a, EvaMessageInfo *b);
	EvaMessageInfo *m_00;
	EvaMessageInfo *m_04;
};

class Rva0010223B
{
public:
	void rva0010223B();
private:
	Rva00116496 *m_00;
	EvaMessageInfo *m_04;
	EvaMessageInfo *m_08;
};

void Rva0010223B::rva0010223B()
{
	if (!m_00)
		return;
	m_00->rva00116496();
	((Rva00102026 *)this)->rva00102026();
	Rva00102087 *slot = (Rva00102087 *)&m_04;
	slot->rva00102087(slot->m_00, slot->m_04);
}
