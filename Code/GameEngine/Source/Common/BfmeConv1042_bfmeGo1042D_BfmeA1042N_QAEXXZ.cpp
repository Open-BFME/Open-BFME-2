// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
//
// ?bfmeGo1042D@BfmeA1042N@@QAEXXZ, retail 0x0044BD79, 41 bytes. Both callee pins
// read off retail's REL32 displacements: 0x002035E2 is the local construction of
// the 0xC-byte error object (already rowed as ??0FunctorNotSet@@QAE@XZ), and
// 0x00629094 is retail's _CxxThrowException, already pinned for the CRT throw.

class BfmeErr1042
{
public:
	BfmeErr1042();

	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1042[];
__declspec(noreturn) void __stdcall bfmeFatal1042(BfmeErr1042 *e, char *m);

class BfmeB1042N
{
public:
	virtual void bfmeV01042N();
	virtual void bfmeDoN1042();
};

class BfmeA1042N
{
public:
	void bfmeGo1042D(void);

	BfmeB1042N *m_bfmeP;
};

void BfmeA1042N::bfmeGo1042D(void)
{
	BfmeB1042N *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1042 e;

		bfmeFatal1042(&e, g_bfmeMsg1042);
	}

	p->bfmeDoN1042();
}

