// cl: /O1 /MD
// ?rva0033A632@Rva0033A632@@QAEHXZ @0x0033A632 44B.
// Framed __thiscall returning int: if TheGameLogic present and rowed
// GameLogic::rva00245EDF(this,&out) true return out else sign-extended
// byte at +0x5F2. Evidence: TheGameLogic extern plus rowed 0x00245EDF
// plus movsx fallback plus 7 callers.
class GameLogic
{
public:
	bool rva00245EDF(void *arg1, int *out);
};

extern GameLogic *TheGameLogic;

class Rva0033A632
{
public:
	int rva0033A632();

private:
	char m_pad[0x5F2];
	signed char m_5F2;
};

int Rva0033A632::rva0033A632()
{
	int out;
	if (TheGameLogic && TheGameLogic->rva00245EDF(this, &out))
		return out;
	return m_5F2;
}
