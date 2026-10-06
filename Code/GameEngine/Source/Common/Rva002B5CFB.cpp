// cl: /MD
// LivingWorldLogic::WillPlayerBeEliminatedIfHeOrSheLosesThisRegion (WorldBuilder name, LivingWorldLogic.cpp line 3837).
// was ?rva002B5CFB@Rva002B5CFB@@QAE_NHH@Z @0x002B5CFB 59B: __thiscall bool probe.
// Resolves id through the rowed 0x2B51F8 find, runs the rowed 0x2104B6
// check on the +0x2C-adjusted hit through +0xB0, and compares its +0x12C
// field against want. Evidence: retail
//   push esi; push 0; push [esp+0xC]; mov esi,ecx; call 0x2B51F8
//   test eax,eax; je FAIL
//   mov ecx,[esi+0xB0]; add eax,0x2C; push eax; call 0x2104B6
//   test eax,eax; je FAIL
//   mov eax,[eax+0x12C]; cmp eax,[esp+0xC]; jne FAIL
//   mov al,1; ret; FAIL: xor al,al; ret ... pop esi; ret 8
// (esp-relative slot names above are entry-relative.) Boundary:
// range-table 59B ending at 0x2B5D36 (mov eax,imm32). Names are
// address-derived except rowed callees.
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class Rva002104B6
{
public:
	void *rva002104B6(void *arg);
};

class Rva002B5CFBField
{
public:
	char m_pad[0x12C];
	int m_12C;
};

class LivingWorldLogic
{
public:
	bool WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(int id, int want);
private:
	char m_pad[0xB0];
	Rva002104B6 *m_b0;
};

bool LivingWorldLogic::WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(int id, int want)
{
	Rva002E2903Player *p = ((Rva002BA8F1Logic *)this)->find(id, 0);
	if (p != 0) {
		Rva002B5CFBField *t = (Rva002B5CFBField *)m_b0->rva002104B6((void *)((char *)p + 0x2C));
		if (t != 0) {
			if (t->m_12C == want)
				return true;
		}
	}
	return false;
}
