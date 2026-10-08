// ??0ControlBar@@QAE@XZ
// partial score=0.93 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??0ControlBar@@QAE@XZ @ 0x0031E94C 558B: ControlBar constructor.
// Evidence: pinned name; callers ?init@InGameUI@@UAEXXZ 0x0029E5D0 and
// ?recreateControlBar@InGameUI@@UAEXXZ 0x0029F890; vtable data 0x0080CC88;
// donor Zero Hour ControlBar::ControlBar plus BFME1 ControlBarConstructor.
#include <hash_map>
#include <vector>
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
inline UnsignedInt GameMakeColor(int r, int g, int b, int a) { return (a << 24) | (r << 16) | (g << 8) | b; }

class GameWindow;

struct Rva0031E92DElement
{
	char m_data[1];
};

struct PlayerAITypeEntry
{
	AsciiString m_name;
	char m_unknown[12];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void reset();
	virtual void update();
protected:
	int m_flag;
	AsciiString m_name;
};

class SubsystemInterfaceList
{
public:
	void rva001B5018(void *sys);
};
extern SubsystemInterfaceList *TheSubsystemList;

class Rva0053B914
{
public:
	void rva0053B914();
};

class Rva0053ED1A
{
public:
	Rva0053ED1A();
private:
	char m_pad[0x5C];
};

class Rva0053ED1A_InitView
{
public:
	virtual void v00();
	virtual void v01();
};

class ControlBar : public SubsystemInterface
{
public:
	ControlBar();
	void rva0031AD14(int a, int b, int c, int d, int e);

private:
	void *m_000C[4];
	int m_001C;
	int m_0020;
	int m_0024;
	bool m_0028;
	char m_pad29[3];
	void *m_002C;
	_STL::hash_map<int, Rva0031E92DElement> m_0030;
	GameWindow *m_contextParent[10];
	void *m_006C;
	int m_0070;
	int m_0074;
	float m_0078;
	int m_007C;
	int m_0080;
	void *m_0084;
	void *m_0088;
	char m_pad8C[0xA0 - 0x8C];
	void *m_00A0;
	void *m_00A4;
	GameWindow *m_00A8[5];
	GameWindow *m_00BC[5];
	char m_padD0[4];
	void *m_00D4;
	void *m_00D8;
	GameWindow *m_00DC[32];
	void *m_015C[32];
	bool m_01DC;
	char m_pad1DD[3];
	int m_01E0;
	int m_01E4;
	int m_01E8;
	int m_01EC;
	int m_01F0;
	int m_01F4;
	int m_01F8;
	int m_01FC;
	void *m_0200;
	int m_0204;
	UnsignedInt m_0208;
	bool m_020C;
	char m_pad20D[3];
	void *m_0210;
	bool m_0214;
	char m_pad215[3];
	int m_0218[5];
	UnsignedInt m_022C;
	_STL::vector<PlayerAITypeEntry> m_0230;
	_STL::vector<PlayerAITypeEntry> m_023C;
	void *m_0248;
	void *m_024C;
	void *m_0250;
	void *m_0254;
	void *m_0258;
	void *m_025C;
	void *m_0260;
	void *m_0264;
	char m_pad268[4];
	void *m_026C;
	void *m_0270;
	void *m_0274;
	bool m_0278;
	char m_pad279[0x290 - 0x279];
	bool m_0290;
	char m_pad291[3];
	int m_0294;
	void *m_0298;
	int m_029C;
	Rva0053ED1A *m_02A0;
	void *m_02A4;
	_STL::vector<PlayerAITypeEntry> m_02A8;
};

ControlBar::ControlBar() : m_0214(false), m_02A0((Rva0053ED1A *)0), m_02A4((void *)0)
{
	m_002C = 0;
	m_contextParent[0] = 0;
	m_020C = false;
	m_0210 = 0;
	m_01F4 = 0;
	m_01F0 = 0;
	m_01E4 = 0;
	m_01E0 = 0;
	m_01FC = 0;
	m_01F8 = 0;
	m_01EC = 0;
	m_01E8 = 0;
	m_0200 = 0;
	m_0204 = 0;
	for (int i = 0; i < 32; ++i)
		m_015C[i] = 0;
	UnsignedInt clock = GameMakeColor(0, 0, 0, 100);
	m_0208 = clock;
	m_022C = clock;
	m_0070 = 0;
	m_0020 = 0;
	m_001C = 0;
	m_0278 = false;
	m_024C = 0;
	m_0248 = 0;
	m_0028 = false;
	for (int i = 1; i < 10; ++i)
		m_contextParent[i] = 0;
	for (int i = 0; i < 32; ++i)
		m_00DC[i] = 0;
	for (int i = 0; i < 5; ++i)
	{
		m_00A8[i] = 0;
		m_00BC[i] = 0;
	}
	m_00D8 = 0;
	m_00D4 = 0;
	m_0084 = 0;
	m_0088 = 0;
	m_00A0 = 0;
	m_00A4 = 0;
	m_006C = 0;
	m_0070 = 0;
	m_0074 = 0;
	m_0078 = -1.0f;
	m_007C = 0;
	((Rva0053B914 *)this)->rva0053B914();
	int white = (int)GameMakeColor(255, 255, 255, 0);
	m_0080 = 0;
	m_000C[0] = 0;
	m_000C[1] = 0;
	m_000C[3] = 0;
	m_000C[2] = 0;
	m_0250 = 0;
	m_0254 = 0;
	m_0258 = 0;
	m_025C = 0;
	m_0260 = 0;
	m_0264 = 0;
	m_0270 = 0;
	m_0274 = 0;
	m_026C = 0;
	m_01DC = false;
	rva0031AD14(white, white, white, white, white);
	m_0290 = false;
	m_0294 = 0;
	m_0298 = 0;
	m_029C = 0;
	Rva0053ED1A *overlay = new Rva0053ED1A;
	m_02A0 = overlay;
	((Rva0053ED1A_InitView *)overlay)->v01();
	if (TheSubsystemList != 0)
		TheSubsystemList->rva001B5018(this);
}
