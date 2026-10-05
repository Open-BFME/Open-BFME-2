// 0x007B6890 (11B): mov ecx, [0x00DA6214], mov eax, [ecx],
// jmp [eax+8]. Reads as a singleton virtual forward through the global
// pointer at 0x00DA6214 to its 3rd slot. Singleton/global/slot identities
// unproven; names are address-derived.

class Rva007B6890Singleton
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

extern Rva007B6890Singleton *g_pRva007B6890;

void Rva007B6890()
{
	g_pRva007B6890->slot2();
}
