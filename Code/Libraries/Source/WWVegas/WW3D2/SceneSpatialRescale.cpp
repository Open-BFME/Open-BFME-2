// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// 0x141F90 197B bounds-rescale. Donor guide BFME1 6583b3c1 scene.cpp:610
// BfmeSceneVector::rva00943FF0 (recovery name, NOT retail).
// Target: SEH body calling rowed clear 0x141EF0, copying 6 floats to +0x00,
// scale = g_bfmeDefaultBU / max(dx,dy) to +0x20 via comiss+divss, calling
// rowed process 0x141C40, scope-end dtor pushing to 0xDB4254.
// 197-vs-201B 4B delta = EH + unordered-max/div shape under /arch:SSE /G7.
// Layout 0x28 TU-local matching canonical (actual header included).
// Exclude Set_Level verbatim + 142960 ctor per lane.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);
	void *rva00141800();

	int m_00; // +0x00 retail 0x80
	void *m_04; // +0x04 retail 0
	void *m_head; // +0x08 VA 0xDB4254 (.data RVA 0x9B4254, free-list head)
	void *(__cdecl *m_alloc)(int size, int arg); // +0x0C retail 0x42FFC0 (Rva0002FFC0Alloc pinned)
	void (__cdecl *m_free)(void *ptr, int arg); // +0x10 retail 0x42FFE0 (Rva0002FFE0Free pinned)
	int m_14; // +0x14 retail 0
};

extern Rva0006EFC8 g_Rva0006EFC8Pool00DB424C; // VA 0xDB424C (.data RVA 0x9B424C), 24B pool
typedef char Rva0006EFC8PoolSize24[(sizeof(Rva0006EFC8) == 0x18) ? 1 : -1];

class Gen_00943CF0
{
public:
	void process(Gen_00943CF0_Node **list);
};

struct Rva00141F90Bounds
{
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
};

struct Rva00943FF0List
{
	Gen_00943CF0_Node *head;

	~Rva00943FF0List()
	{
		// Retail inlines the 8-byte free-list push at VA 0xDB4254 (no CALL).
		// Typed pool base VA 0xDB424C (.data RVA 0x9B424C, 24B: 80/0/0/42FFC0/42FFE0/0)
		// via g_Rva0006EFC8Pool00DB424C.m_head (+8 == 0xDB4254); phony
		// g_SceneNodeFreeList00DB4254 removed (was undefined, no symbols.csv row,
		// no defining TU; Gemini-r4 CRITICAL_LINK_HAZARD). Manual push keeps byte
		// shape; _M_deallocate would emit push-8+CALL and fail.
		Gen_00943CF0_Node *current = head;
		while (current != 0) {
			Gen_00943CF0_Node *old = current;
			current = current->m_next;
			old->m_next = (Gen_00943CF0_Node *)g_Rva0006EFC8Pool00DB424C.m_head;
			g_Rva0006EFC8Pool00DB424C.m_head = old;
		}
	}
};

// Retail divisor VA 0xBBB8D8 is .rdata (RVA 0x7BB8D8, float=1, 1684 refs),
// NOT .data: AudioManagerFocusVolume.cpp `float g_Va00BBB8D8 = 1.0f;`
// is section-wrong (.data VA 0xDAxxxx, cannot be at 0xBBB8D8) and
// T_009F4FB0.cpp `static float g_bfmeDefaultBU;` is TU-local (invisible).
// Correct provider is compiler literal 1.0f -> __real@3f800000 COMDAT in
// .rdata, folded by /OPT:ICF to the single retail 0xBBB8D8 (same mechanism
// as Rva00263653Ctor/Rva002DB311Ctor which use literals, not externs).
// Extern g_bfmeDefaultBU removed (was undefined link hazard); literal keeps
// identical movss/divss shape (DIR32-masked per-TU, link-correct via COMDAT).

struct BfmeSceneVectorElement
{
	unsigned int m_00;
	MultiListClass<RenderObjClass> m_objects;
};

class BfmeSceneVector
{
public:
	void rva00141EF0(Gen_00943CF0_Node **objects);
	void rva00141F90(const Rva00141F90Bounds &newBounds);

	Rva00141F90Bounds bounds;
	BfmeSceneVectorElement *vector;
	int vector_max;
	float scale;
	unsigned int level_mask;
};

typedef char BfmeSceneRescaleSizeMatchesCanonical[(sizeof(BfmeSceneVector) == 0x28) ? 1 : -1];
typedef char BfmeSceneRescaleMatchesIndex[(sizeof(BfmeSceneVector) == sizeof(BFME2SceneSpatialIndex)) ? 1 : -1];

void BfmeSceneVector::rva00141F90(const Rva00141F90Bounds &newBounds)
{
	Rva00943FF0List objects = {0};
	rva00141EF0((Gen_00943CF0_Node **)&objects);
	bounds = newBounds;
	float dx = bounds.m_0C - bounds.m_00;
	float dy = bounds.m_10 - bounds.m_04;
	float greater = dx > dy ? dx : dy;
	scale = 1.0f / greater;
	((Gen_00943CF0 *)this)->process(&objects.head);
}
