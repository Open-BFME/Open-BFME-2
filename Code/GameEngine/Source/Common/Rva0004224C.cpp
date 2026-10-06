// cl: /MD

// ?rva0004224C@Rva0004224C@@QAEPAV1@XZ @0x0004224C 22B
// Chain: calls 0x000421FD just landed; global 0x00DFE78C is TheGameLogic.
// Returns this after ensuring FPMode counter. Callers 12 unclaimed.

extern class GameLogic *TheGameLogic;

class Rva000421FD
{
public:
	void rva000421FD();
};

#define TheRva421FD (*(Rva000421FD **)&TheGameLogic)

class Rva0004224C
{
public:
	Rva0004224C *rva0004224C();
};

Rva0004224C *Rva0004224C::rva0004224C()
{
	if (TheRva421FD)
		TheRva421FD->rva000421FD();
	return this;
}
