// cl: /MD

// ?rva00395561@Rva00395561@@QAEXXZ @0x00395561 34B
// Chain: calls 0x000421FD; drains int at +0 while calling global counter.
// Global 0x00DFE78C is TheGameLogic counter owner. Prev stlport list, next disp8.

extern class GameLogic *TheGameLogic;

class Rva000421FD
{
public:
	void rva000421FD();
};

#define TheCounter (*(Rva000421FD **)&TheGameLogic)

class Rva00395561
{
	int m_00;
public:
	void rva00395561();
};

void Rva00395561::rva00395561()
{
	if (TheCounter)
	{
		while (m_00 > 0)
		{
			--m_00;
			TheCounter->rva000421FD();
		}
	}
}
