// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// 0x141EF0 151B drain. Donor guide BFME1 6583b3c1 Rva00943F70Clear.cpp:34.
// Retail uses global 8-byte pool at 0xDB424C (free-list at +8 = 0xDB4254) via
// rowed grow 0x6EFC8, not STLport slist allocate: slist push_front emits
// push-8 + STLport call, retail emits pool-check + grow-call + prepend.
// Keep Remove 0x141640 CALL out of line (inlining adds 98B per 2313).
// Layout 0x28 via TU-local view matching canonical BFME2SceneSpatialIndex
// (actual header included, equivalence asserted). Reject 16B dtor view.
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

	int m_00; // +0x00 retail 0x80 (pool default count, size=m_00*8+4 via 0x6FAEC mov [esi],0x80)
	void *m_04; // +0x04 retail 0 (current block via 0x6FAEC mov [esi+4],0)
	void *m_head; // +0x08 retail 0 (free-list head at VA 0xDB4254, .data RVA 0x9B4254)
	void *(__cdecl *m_alloc)(int size, int arg); // +0x0C retail 0x42FFC0 (Rva0002FFC0Alloc pinned 6854, via 0x6FAEC mov [esi+0x0C])
	void (__cdecl *m_free)(void *ptr, int arg); // +0x10 retail 0x42FFE0 (Rva0002FFE0Free pinned 6855, via 0x6FAEC mov [esi+0x10])
	int m_14; // +0x14 retail 0 (allocator arg via 0x6FAEC mov [esi+0x14],0)
};

extern Rva0006EFC8 g_Rva0006EFC8Pool00DB424C;
typedef char Rva0006EFC8PoolSize24[(sizeof(Rva0006EFC8) == 0x18) ? 1 : -1];

struct BfmeSceneVectorElement
{
	unsigned int m_00;
	MultiListClass<RenderObjClass> m_objects;
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

class BfmeSceneVector
{
public:
	void rva00141EF0(Gen_00943CF0_Node **objects);

	Rva00141F90Bounds bounds;
	BfmeSceneVectorElement *vector;
	int vector_max;
	float scale;
	unsigned int level_mask;
};

typedef char BfmeSceneVectorSizeMatchesCanonical[(sizeof(BfmeSceneVector) == 0x28) ? 1 : -1];
typedef char BfmeSceneVectorMatchesIndex[(sizeof(BfmeSceneVector) == sizeof(BFME2SceneSpatialIndex)) ? 1 : -1];
typedef char BfmeSceneClearElementMatchesNode[(sizeof(BfmeSceneVectorElement) == sizeof(BFME2SceneSpatialNode)) ? 1 : -1];

void BfmeSceneVector::rva00141EF0(Gen_00943CF0_Node **objects)
{
	BfmeSceneVectorElement *element = vector;
	for (int index = 0; index < vector_max; ++index, ++element) {
		RenderObjClass *object;
		while ((object = element->m_objects.Peek_Head()) != 0) {
			// 8-byte node via global pool. Layout matches retail: fall-through
			// grow + prepend, far pop at end jumping back (no jmp on fail path).
			Gen_00943CF0_Node *node;
		retry:
			if (g_Rva0006EFC8Pool00DB424C.m_head != 0)
				goto pop_end;
			{
				int size = g_Rva0006EFC8Pool00DB424C.m_00 * 8 + 4;
				if (g_Rva0006EFC8Pool00DB424C.rva0006EFC8(0, size))
					goto retry;
				node = 0;
			}
			goto prepend;
		pop_end:
			node = (Gen_00943CF0_Node *)g_Rva0006EFC8Pool00DB424C.m_head;
			g_Rva0006EFC8Pool00DB424C.m_head = node->m_next;
		prepend:
			void **valuePtr = (void **)((char *)node + 4);
			if (valuePtr != 0)
				valuePtr[0] = object;
			node->m_next = 0;
			node->m_next = *objects;
			*objects = node;
			((BFME2SceneSpatialIndex *)this)->Remove(object);
		}
	}
}
