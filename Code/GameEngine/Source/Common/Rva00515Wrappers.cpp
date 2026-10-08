// cl: /MD /EHsc /O1
// The two target boundaries at 0x00515BCA and 0x00515C17 each construct the
// matched 0x00211E75 one-int handle from a local address, call the adjacent
// helper at 0x00515B0A with (handle, argument), then release the handle. Their
// only difference is the callback copied into the handle: the rowed good- and
// evil-campaign start wrappers 0x00515921 and 0x005158C2.
// The handle view reuses the matched constructor layout and rowed release call.

// The handle's counted target: a vtable and the count at +0x04.
struct Impl00211E75
{
	void *m_vtbl;
	int m_refs;
};

class Rva00211E75
{
public:
	Rva00211E75(const int *arg);
	Rva00211E75(const Rva00211E75 &);

protected:
	Rva00211E75() {}

public:
	Impl00211E75 *m_impl;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00515Handle : public Rva00211E75
{
public:
	explicit Rva00515Handle(const int *arg) : Rva00211E75(arg) {}

	~Rva00515Handle()
	{
		Impl00211E75 *impl = *reinterpret_cast<Impl00211E75 **>(
			static_cast<Rva00211E75 *>(this));
		if (impl)
			ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(impl));
	}
};

void __cdecl rva00515B0A(Rva00515Handle *handle, int value);

int goodCampaignRva00515921(float time, bool start);
int evilCampaignRva005158C2(float time, bool start);

// ?Rva00515BCA@@YAXH@Z @0x00515BCA 77B
void __cdecl Rva00515BCA(int value)
{
	const int callback = reinterpret_cast<int>(&goodCampaignRva00515921);
	Rva00515Handle handle(&callback);
	rva00515B0A(&handle, value);
}

// ?Rva00515C17@@YAXH@Z @0x00515C17 77B
void __cdecl Rva00515C17(int value)
{
	const int callback = reinterpret_cast<int>(&evilCampaignRva005158C2);
	Rva00515Handle handle(&callback);
	rva00515B0A(&handle, value);
}

// ?rva00515B0A@@YAXPAVRva00515Handle@@H@Z @0x00515B0A 192B: the campaign
// start both wrappers above share. The side character picks the campaign
// global 0x00DD1538 ('E' 0, 'H' 2, else 1; AptMainMenu::LinearCampaignStart
// sends it with the campaign index), TheLivingWorldManager is cleaned
// (rowed 0x0021427A) and, for a side, TheLivingWorldLogic's +0xEC takes it.
// Then the event sequencer (rowed 0x003FE7E6, id slot 0x00E02EC4) queues the
// parchment-map fade 0x005157EE, the 0x0051573A movie step unless
// TheGlobalData's +0x2D is set, and finally the caller's handle; the open
// main menu (0x00E048DC) gets its +0x280 flag. WorldBuilder's twin
// (0x01458290, unnamed) makes the same three AddControl calls.
class Rva00211E75Callback : public Rva00211E75
{
public:
	// The registry owns destruction, as in Rva00211FA8Registration.cpp.
	~Rva00211E75Callback();
	Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}
	Rva00211E75Callback(const Rva00515Handle &other)
	{
		m_impl = other.m_impl;
		if (m_impl)
			++m_impl->m_refs;
	}
};

extern int g_00E02EC4;
bool Rva003FE7E6(Rva00211E75Callback callback, int *id);

int rva0051E280PreParchmentMapFadeStartNew(int, bool);
int rva0051573A(float, bool);

extern int g_Va00DD1538;

class LivingWorldManager
{
public:
	void rva0021427A();
};
extern LivingWorldManager *TheLivingWorldManager;

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva00515B0ALogic
{
	unsigned char m_pad000[0xEC];
	int m_campaignSide;				// +0xEC
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva00515B0AGlobalData
{
	unsigned char m_pad00[0x2D];
	bool m_2d;						// +0x2D
};

// The open main menu's +0x280 flag (AptMainMenuCallbacks.cpp's m_280).
extern int g_Va00E048DC;

struct Rva00515B0AMenu
{
	unsigned char m_pad000[0x280];
	bool m_280;						// +0x280
};

void __cdecl rva00515B0A(Rva00515Handle *handle, int value)
{
	char side = (char)value;
	switch (side)
	{
	case 'E':
		g_Va00DD1538 = 0;
		break;
	case 'H':
		g_Va00DD1538 = 2;
		break;
	default:
		g_Va00DD1538 = 1;
		break;
	}
	if (TheLivingWorldManager)
		TheLivingWorldManager->rva0021427A();
	if (side)
		reinterpret_cast<Rva00515B0ALogic *>(TheLivingWorldLogic)->m_campaignSide = g_Va00DD1538;
	Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva0051E280PreParchmentMapFadeStartNew)), &g_00E02EC4);
	if (!reinterpret_cast<Rva00515B0AGlobalData *>(TheWritableGlobalData)->m_2d)
		Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva0051573A)), &g_00E02EC4);
	Rva003FE7E6(Rva00211E75Callback(*handle), &g_00E02EC4);
	reinterpret_cast<Rva00515B0AMenu *>(g_Va00E048DC)->m_280 = true;
}
