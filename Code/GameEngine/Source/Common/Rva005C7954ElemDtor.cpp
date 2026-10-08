// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??1Rva005C7954Elem@@QAE@XZ @0x005C7954 213B: non-virtual dtor with twin AptCall hides plus 5 member dtors.
// Evidence: callers 0x005C7C88 deleting dtor plus 0x005C7CAD clear in OpaqueScalarDeletingDtors.cpp; callees rowed 0x005FB5E6 AptCall plus 0x005C3209 plus 4 vector dtors plus releaseBuffer 0x00036410; strings SetAutoAbilityOverlayState SetFlashEffectState _hide plus g_Rva0107301CEmptyString plus TheRva00222A8BTarget; neighbour Rva005C7A29Overlay.cpp layout +08 +0C +4C +54 +55.
#include "ascii_string.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

class Rva005C31FB
{
public:
	void rva005C3209();
};

// Owner vtable installed by the factory at 0x005C802B. Callback bodies
// 0x005C78D0 and 0x005C790D prove the seven-slot prefix used here.
class Rva005C802B
{
public:
	virtual ~Rva005C802B();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct CommandButtonMouseState
{
	char m_pad[0x318];
	int m_button;
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0xC];
};

class Rva00524436
{
public:
	~Rva00524436();
private:
	char m_pad[0x18];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[0xC];
};

class Rva00524349
{
public:
	~Rva00524349();
private:
	char m_pad[0xC];
};

class Rva005C7954Elem
{
public:
	~Rva005C7954Elem();
	void OnInitialized(const char *path);
	void OnOverButton(const char *path);
	void OnPress(const char *path);
private:
	Rva005C802B *m_00;
	Rva005C31FB *m_04;
	void *m_08;
	AsciiString m_0C;
	Rva0052413E m_10;
	Rva00524436 m_1C;
	Rva005242D7 m_34;
	Rva00524349 m_40;
	bool m_4C;
	char _pad4D[3];
	int m_50;
	bool m_54;
	bool m_55;
};

// Constructor 0x005C7D4A binds this callback to "_OnInitialized";
// retail 0x005C78C9..0x005C78D0 writes the initialized flag and returns 4.
void Rva005C7954Elem::OnInitialized(const char *path)
{
	m_4C = true;
}

// Bound by the constructor to the over-button handler. The body ends at
// 0x005C7917; the following getter is a separate, already-owned body.
void Rva005C7954Elem::OnOverButton(const char *path)
{
	m_00->vslot2();
}

// Constructor binds "_OnPress" at 0x005C7E90. Retail reads the player's
// mouse-button word at +0x318 and dispatches mode 6 through slots 3/5,
// other modes through slots 4/6. Other mouse buttons do nothing.
void Rva005C7954Elem::OnPress(const char *path)
{
	int button = reinterpret_cast<CommandButtonMouseState *>(g_bfmeAptWindowManager)->m_button;
	if (button == 0) {
		if (m_50 == 6)
			m_00->vslot3();
		else
			m_00->vslot4();
	} else if (button == 2) {
		if (m_50 == 6)
			m_00->vslot5();
		else
			m_00->vslot6();
	}
}

Rva005C7954Elem::~Rva005C7954Elem()
{
	if (m_4C) {
		if (m_54) {
			char *t = *(char **)(void *)&m_0C;
			const char *s = t ? t + 8 : "";
			Rva005FB5E6AptCall(TheRva00222A8BTarget, m_08, s, "SetAutoAbilityOverlayState", "_hide");
		}
		if (m_55) {
			char *t = *(char **)(void *)&m_0C;
			const char *s = t ? t + 8 : "";
			Rva005FB5E6AptCall(TheRva00222A8BTarget, m_08, s, "SetFlashEffectState", "_hide");
		}
	}
	m_04->rva005C3209();
}
