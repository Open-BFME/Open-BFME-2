// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1SortingNodeStruct@@QAE@XZ
// retail 0x0012FCA0, 213 bytes. Dedicated TU.
//
// BFME2's sorting state carries sixteen texture stages (retail passes count
// 0x10 to the eh vector destructor over Textures), while the Zero Hour
// header (used by sortingrenderer.cpp) only has eight. Ported from
// Open-BFME-1 Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.cpp, whose
// TU-local BfmeSortingRenderStateStruct already models the textures as owning
// RefCountPtr<TextureClass> handles released by an inline destructor; only
// the stage count differs here (16 vs 8), which shifts vertex_buffers to
// state+0x280 and index_buffer to state+0x288.
//
// The TU-scoped replicas below mangle identically to the real instantiations
// (same identifiers), so the base-class Remove call resolves to the matched
// ?Remove@?$DLNodeClass@VSortingNodeStruct@@@@QAEXXZ at 0x0012DC00 and the
// texture element destructor to the matched
// ??1?$RefCountPtr@VTextureClass@@@@QAE@XZ at 0x0017098D with no pins.

// ----------------------------------------------------------------------------
// Minimal TU-local views. Only the layout, the virtual Release_Ref slot and
// the non-trivial RefCountPtr destructor matter to this dtor's bytes.
// ----------------------------------------------------------------------------

template<class T>
class DLNodeClass
{
public:
	DLNodeClass() : succ(0), pred(0), list(0) {}
	~DLNodeClass() { Remove(); }
	void Remove();

private:
	DLNodeClass<T> *succ;
	DLNodeClass<T> *pred;
	void *list;
};

class VertexMaterialClass;
class VertexBufferClass;
class IndexBufferClass;
class TextureClass;

// TU-local mirror of WWLib RefCountClass (refcount.h, NDEBUG shape): the
// refcount lives at +4 behind the vptr, Release_Ref inlines to a decrement
// with a virtual Delete_This call (slot 0) on reaching zero, and the virtual
// dtor sits at slot 1. Only this shape reproduces the retail releases.
#include "../WWLib/RefCountData.h"

class VertexMaterialClass : public RefCountClass
{
};

class VertexBufferClass : public RefCountClass
{
};

class IndexBufferClass : public RefCountClass
{
};

class TextureClass : public RefCountClass
{
public:
	// Out-of-line release: the rowed ?Release_Ref@TextureClass@@QAEXXZ at
	// 0x0061ED10, which retail's RefCountPtr<TextureClass> destructor
	// (0x0017098D) tail-jumps to.
	void Release_Ref(void);
};

template<class T>
class RefCountPtr
{
public:
	// Both are reached only out of line here (the eh vector constructor and
	// destructor iterators): retail's copies are 0x00326BE6 and 0x0017098D.
	RefCountPtr();
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}

private:
	T *Referent;
};

struct D3DLIGHT8Replica
{
	// 104 bytes: D3DLIGHTTYPE + 3xD3DCOLORVALUE + 2xD3DVECTOR + 7 floats.
	// (Not 96: the trailing block is Range/Falloff/Att0-2/Theta/Phi.)
	unsigned char data[104];
};

struct Matrix4x4Replica
{
	float m[4][4];
};

struct SortingShaderState
{
	unsigned int bits;

	SortingShaderState() : bits(0x0010441B) {}
};

struct SortingRenderStateStruct
{
	SortingShaderState shader;
	VertexMaterialClass *material;
	RefCountPtr<TextureClass> Textures[16];
	D3DLIGHT8Replica Lights[4];
	bool LightEnable[4];
	Matrix4x4Replica world;
	Matrix4x4Replica view;
	unsigned vertex_buffer_types[2];
	unsigned index_buffer_type;
	unsigned short vba_offset;
	unsigned short vba_count;
	unsigned short iba_offset;
	VertexBufferClass *vertex_buffers[2];
	IndexBufferClass *index_buffer;
	unsigned short index_base_offset;

	SortingRenderStateStruct()
		: shader(), material(0), index_buffer(0)
	{
		vertex_buffers[0] = 0;
		vertex_buffers[1] = 0;
	}

	__forceinline ~SortingRenderStateStruct()
	{
		if (material) {
			material->Release_Ref();
			*reinterpret_cast<VertexMaterialClass * volatile *>(&material) = 0;
		}
		for (unsigned i = 0; i < 2; ++i) {
			if (vertex_buffers[i]) {
				vertex_buffers[i]->Release_Ref();
				*reinterpret_cast<VertexBufferClass * volatile *>(&vertex_buffers[i]) = 0;
			}
		}
		if (index_buffer) {
			index_buffer->Release_Ref();
			*reinterpret_cast<IndexBufferClass * volatile *>(&index_buffer) = 0;
		}
	}
};

class SortingNodeStruct : public DLNodeClass<SortingNodeStruct>
{
public:
	// ??0SortingNodeStruct@@QAE@XZ, retail 0x0012E840 (114B). An empty body:
	// the base zeroing, the 16-way Textures construction, the shader-bits
	// store and the material/vertex/index nulling are all implicit member
	// initialization in declaration order.
	SortingNodeStruct();
	SortingRenderStateStruct sorting_state;

	// Retail node extent is 0x2A8 (Get_Sorting_Struct news 0x2A8): 0xC list
	// base + 0x290 state + a 0xC tail, i.e. a plain float center with no
	// bounding sphere (same tail as Open-BFME-1's class).
	float transformed_center;
	unsigned short start_index;
	unsigned short polygon_count;
	unsigned short min_vertex_index;
	unsigned short vertex_count;
};

// ??0SortingNodeStruct@@QAE@XZ
inline SortingNodeStruct::SortingNodeStruct()
{
}

template<class T>
class DLListClass
{
public:
	T *Head() { return static_cast<T *>(head); }

private:
	DLNodeClass<T> *head;
	DLNodeClass<T> *tail;
};

#include <new>

static DLListClass<SortingNodeStruct> clean_list;

// ?Get_Sorting_Struct@@YAPAVSortingNodeStruct@@XZ, retail 0x0012FD80 (128B).
// Verbatim Open-BFME-1 shape: reuse a clean-list node when available,
// otherwise allocate a 0x2A8-byte node (validates the TU layout).
SortingNodeStruct *Get_Sorting_Struct()
{
	SortingNodeStruct *state = clean_list.Head();
	if (state) {
		state->Remove();
		return state;
	}
	state = new SortingNodeStruct();
	return state;
}

// Anchor: emits the implicit ??1SortingNodeStruct COMDAT this TU exists to place.
void destroySortingNode(SortingNodeStruct *node)
{
	node->~SortingNodeStruct();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeSortingNodeStructInlineAnchor@@YAXPAVSortingNodeStruct@@@Z absent-from-retail
void _bfmeSortingNodeStructInlineAnchor(SortingNodeStruct *sortingNode)
{
    sortingNode->SortingNodeStruct::SortingNodeStruct();
}
#pragma inline_depth()
