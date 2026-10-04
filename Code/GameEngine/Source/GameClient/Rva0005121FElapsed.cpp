// cl: /O1 /Oy- /arch:SSE /DNDEBUG /MD
// ?rva0005121F@Rva0005121F@@QAEMXZ @0x0005121F 157B, a virtual whose table
// entry is at VA 0x00BC5764: seconds since the frame stamped at +0x94,
// using TheGameClient's frame (slot 0x7C, as DrawableFade.cpp has it) and
// the seconds-per-frame float at 0x00DBA4FC, clamped at zero, restamping
// +0x94. When +0x678 is set or the byte at +0x6A5 is, or there is no
// client, it only restamps (if it can) and returns one frame's worth.
// Retail tests the delta with fcompi, which MSVC 7.1 emits only under
// /arch:SSE. Class, method and global names are address-derived.
//
// ?rva000511C3@Rva0005121F@@QAEXPAUCoord3D@@@Z @0x000511C3 92B, the
// virtual four entries before it in the same table: by the mode at +0x678,
// copy TheTacticalView's slot-71 position (0x11C), tail-call slot 32 (0x80)
// of the object at 0x00DFEF18 with the same out pointer, or zero it. Its
// ebp frame needs /Oy-, which leaves 0x0005121F unchanged.
class ClientFrameSubsystem;
extern ClientFrameSubsystem *TheGameClient;
class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual unsigned int slot1F();
};
#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)
extern float g_Va00DBA4FC;

struct Coord3D
{
	float x, y, z;
};
class TacticalView
{
public:
	virtual void _v000();
	virtual void _v001();
	virtual void _v002();
	virtual void _v003();
	virtual void _v004();
	virtual void _v005();
	virtual void _v006();
	virtual void _v007();
	virtual void _v008();
	virtual void _v009();
	virtual void _v010();
	virtual void _v011();
	virtual void _v012();
	virtual void _v013();
	virtual void _v014();
	virtual void _v015();
	virtual void _v016();
	virtual void _v017();
	virtual void _v018();
	virtual void _v019();
	virtual void _v020();
	virtual void _v021();
	virtual void _v022();
	virtual void _v023();
	virtual void _v024();
	virtual void _v025();
	virtual void _v026();
	virtual void _v027();
	virtual void _v028();
	virtual void _v029();
	virtual void _v030();
	virtual void _v031();
	virtual void _v032();
	virtual void _v033();
	virtual void _v034();
	virtual void _v035();
	virtual void _v036();
	virtual void _v037();
	virtual void _v038();
	virtual void _v039();
	virtual void _v040();
	virtual void _v041();
	virtual void _v042();
	virtual void _v043();
	virtual void _v044();
	virtual void _v045();
	virtual void _v046();
	virtual void _v047();
	virtual void _v048();
	virtual void _v049();
	virtual void _v050();
	virtual void _v051();
	virtual void _v052();
	virtual void _v053();
	virtual void _v054();
	virtual void _v055();
	virtual void _v056();
	virtual void _v057();
	virtual void _v058();
	virtual void _v059();
	virtual void _v060();
	virtual void _v061();
	virtual void _v062();
	virtual void _v063();
	virtual void _v064();
	virtual void _v065();
	virtual void _v066();
	virtual void _v067();
	virtual void _v068();
	virtual void _v069();
	virtual void _v070();
	virtual const Coord3D *slot11C();
};
extern TacticalView *TheTacticalView;
class Rva00DFEF18
{
public:
	virtual void _w000();
	virtual void _w001();
	virtual void _w002();
	virtual void _w003();
	virtual void _w004();
	virtual void _w005();
	virtual void _w006();
	virtual void _w007();
	virtual void _w008();
	virtual void _w009();
	virtual void _w010();
	virtual void _w011();
	virtual void _w012();
	virtual void _w013();
	virtual void _w014();
	virtual void _w015();
	virtual void _w016();
	virtual void _w017();
	virtual void _w018();
	virtual void _w019();
	virtual void _w020();
	virtual void _w021();
	virtual void _w022();
	virtual void _w023();
	virtual void _w024();
	virtual void _w025();
	virtual void _w026();
	virtual void _w027();
	virtual void _w028();
	virtual void _w029();
	virtual void _w030();
	virtual void _w031();
	virtual void slot80(Coord3D *out);
};
extern Rva00DFEF18 *g_00DFEF18;
class Rva0005121F
{
public:
	float rva0005121F();
	void rva000511C3(Coord3D *out);
private:
	char m_pad000[0x94];
	unsigned int m_lastFrame;	// +0x94
	char m_pad098[0x678 - 0x98];
	int m_678;			// +0x678
	char m_pad67C[0x6A5 - 0x67C];
	bool m_6A5;			// +0x6A5
};

float Rva0005121F::rva0005121F()
{
	if (m_678 == 0 && !m_6A5) {
		if (TheRva00DFE77C) {
			float elapsed = ((float)TheRva00DFE77C->slot1F() - (float)m_lastFrame) * g_Va00DBA4FC;
			if (elapsed < 0.0f)
				elapsed = 0.0f;
			m_lastFrame = TheRva00DFE77C->slot1F();
			return elapsed;
		}
	} else if (TheRva00DFE77C) {
		m_lastFrame = TheRva00DFE77C->slot1F();
	}
	return g_Va00DBA4FC;
}

void Rva0005121F::rva000511C3(Coord3D *out)
{
	switch (m_678) {
	case 0:
		if (TheTacticalView) {
			*out = *TheTacticalView->slot11C();
			return;
		}
		break;
	case 1:
		if (g_00DFEF18) {
			g_00DFEF18->slot80(out);
			return;
		}
		break;
	}
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
}
