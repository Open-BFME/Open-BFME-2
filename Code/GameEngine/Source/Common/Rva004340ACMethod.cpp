// cl: /MD
// ?rva004340AC@AptSaveLoad@@QAEXXZ @ 0x004340AC 134B: Apt save/load button-enable refresh for Load and Delete
// Evidence: rowed Rva00222547Get 0x00222547 and Rva002D3409Invoke 0x002D3409; strings LoadButtonEnable DeleteButtonEnable; manager TheRva00222A8BTarget; pin AptSaveLoad::rva00433F7F 0x00433F7F used as pending pointer (declared int per pin cast to pointer per AptSaveLoadCallbacks precedent); fields +0x294 eq 2 and m_mode +0x2a0 eq 0x10 with pending kind +0x28 eq 6 and flag +0xde4 eq 0 selecting g_00BBFDDC/FDE0; caller jmp 0x00434487 in 0x00434432.
// Pin return type note: pin 0x00433F7F declares int; body dereferences result as AptSaveLoadPending (+0x28 +0xde4) so cast follows the Load() precedent in AptSaveLoadCallbacks.cpp.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameWindow;
GameWindow *Rva00222547Get(GameWindow *w);
int __cdecl Rva002D3409Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *const &a);

struct AptSaveLoadPending
{
	char m_pad00[0x28];
	int m_kind;
	char m_pad2C[0xDE4 - 0x2C];
	unsigned char m_de4;
};

class AptSaveLoad
{
public:
	int rva00433F7F();
	void rva004340AC();
private:
	char m_pad000[0x27C];
	int m_state;
	struct AptSaveLoadPending *m_pending;
	char m_pad284[0x288 - 0x284];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileName;
	int m_294;
	char m_pad298[0x29C - 0x298];
	bool m_29c;
	char m_pad29D[0x2A0 - 0x29D];
	int m_mode;
};

void AptSaveLoad::rva004340AC()
{
	if (m_294 != 2)
		return;
	AptSaveLoadPending *pending = (AptSaveLoadPending *)rva00433F7F();
	const char *zero = "0";
	const char *deleteVal = pending ? "1" : zero;
	const char *loadVal = deleteVal;
	if (m_mode == 0x10 && pending && pending->m_kind == 6 && pending->m_de4 == 0)
		loadVal = zero;
	GameWindow *w = Rva00222547Get((GameWindow *)this);
	Rva002D3409Invoke((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), w, "LoadButtonEnable", loadVal);
	Rva002D3409Invoke((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), w, "DeleteButtonEnable", deleteVal);
}
