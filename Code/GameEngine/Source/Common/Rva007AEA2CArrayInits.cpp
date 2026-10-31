// cl: /MD /d1Binl
//
// Static-init and atexit bodies for four file-scope object arrays, from the
// startup strip and the cleanup-thunk strip. Each array's initializer runs
// the CRT eh vector constructor iterator (0x00629512) over the elements and
// registers the matching cleanup with atexit; each cleanup runs the eh vector
// destructor iterator (0x00629110), called under their real CRT names
// (/d1Binl admits the __thiscall callback types, as in ehvecctr.cpp). The
// element constructor and destructor are referenced only as DIR32 function
// addresses, so they are spelled with the ICF owner names rowed at those
// addresses, not as proven element types.
//
//   0x007AEA2C / 0x007B7BBE  20 x 4-byte AsciiString-shaped slots at VA 0x00E01D60
//                            (ctor 0x00326BE6, dtor ~AsciiString 0x0048BA39)
//   0x007AF10C / 0x007B7DD1  2 x 12-byte chat-history vectors g_00E022F8
//                            (LANChatHistory.cpp; ctor closure 0x00256646,
//                            dtor 0x00381AE0)
//   0x007AC207 / 0x007B6C84  the cursorTextures table at VA 0x00DE4B40
//                            (0x498 4-byte texture handles; ctor 0x00326BE6,
//                            dtor 0x0017098D)
//   0x007ABF7B / 0x007B6BB9  8 x 4-byte texture handles at VA 0x00DE1F8C
//                            (ctor 0x00326BE6, dtor 0x0017098D)
//   0x007B93EC               cleanup of the function-local static array of 30
//                            12-byte points at VA 0x00E060B8 that the unrowed
//                            body around 0x0055DDF8 builds under guard bit
//                            0x00E06220 (ctor 0x0047A6A9, empty dtor 0x000B3FD0)

#include <stdlib.h>

typedef void (__thiscall *ElemFn)(void *);
void __stdcall __ehvec_ctor(void *, unsigned, int, ElemFn, ElemFn);
void __stdcall __ehvec_dtor(void *, unsigned, int, ElemFn);

extern "C" void __identifier("??0AsciiString@@QAE@XZ")(void *);					// 0x00326BE6 (ICF owner)
extern "C" void __identifier("??1AsciiString@@QAE@XZ")(void *);					// 0x0048BA39
extern "C" void __identifier("??_F?$vector@PBVObjectCreationList@@V?$allocator@PBVObjectCreationList@@@_STL@@@_STL@@QAEXXZ")(void *);	// 0x00256646
extern "C" void __identifier("??1Rva00381AE0@@QAE@XZ")(void *);					// 0x00381AE0
extern "C" void __identifier("??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")(void *);	// 0x0017098D
extern "C" void __identifier("??1Coord3D@@QAE@XZ")(void *);						// 0x000B3FD0
#define Rva00326BE6NullFirstWordCtor ((ElemFn)__identifier("??0AsciiString@@QAE@XZ"))
#define Rva0048BA39AsciiStringDtor ((ElemFn)__identifier("??1AsciiString@@QAE@XZ"))
#define Rva00256646VectorCtorClosure ((ElemFn)__identifier("??_F?$vector@PBVObjectCreationList@@V?$allocator@PBVObjectCreationList@@@_STL@@@_STL@@QAEXXZ"))
#define Rva00381AE0VectorDtor ((ElemFn)__identifier("??1Rva00381AE0@@QAE@XZ"))
#define Rva0017098DTextureHandleDtor ((ElemFn)__identifier("??1?$RefCountPtr@VTextureClass@@@@QAE@XZ"))
#define Rva000B3FD0EmptyPointDtor ((ElemFn)__identifier("??1Coord3D@@QAE@XZ"))

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector;
}
struct BfmeStringRecord005DDD40;
extern unsigned int g_chatHistoryVectors[6];
// Retail startup constructs two 12-byte vectors in this zero-filled storage.
#define g_00E022F8 ((_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > *)g_chatHistoryVectors)

struct CursorTextureSlot;
extern CursorTextureSlot cursorTextures[][21];

unsigned g_Va00E01D60[20];	// retail RVA 0x00A01D60 (.bss), defined here
extern void *g_shaderTextureSlots[8];	// VA 0x00DE1F8C (W3DShroudMaterialPass.cpp)
unsigned g_Va00E060B8[90];	// retail RVA 0x00A060B8, the function-local static of the unrowed 0x0055DDF8 body, defined here

void __cdecl rva007B7BBE()
{
	__ehvec_dtor(g_Va00E01D60, 4, 0x14, Rva0048BA39AsciiStringDtor);
}

void __cdecl destroyChatHistoryVectors()
{
	__ehvec_dtor(g_00E022F8, 0xC, 2, Rva00381AE0VectorDtor);
}

void __cdecl destroyCursorTextures()
{
	__ehvec_dtor(cursorTextures, 4, 0x498, Rva0017098DTextureHandleDtor);
}

void __cdecl destroyShaderTextureSlots()
{
	__ehvec_dtor(g_shaderTextureSlots, 4, 8, Rva0017098DTextureHandleDtor);
}

void __cdecl rva007B93EC()
{
	__ehvec_dtor(g_Va00E060B8, 0xC, 0x1E, Rva000B3FD0EmptyPointDtor);
}

struct Rva007AEA2CArrayInits
{
	static void rva007AEA2C();
	static void initChatHistoryVectors();
	static void initCursorTextures();
	static void initShaderTextureSlots();
};

void Rva007AEA2CArrayInits::rva007AEA2C()
{
	__ehvec_ctor(g_Va00E01D60, 4, 0x14, Rva00326BE6NullFirstWordCtor, Rva0048BA39AsciiStringDtor);
	atexit(rva007B7BBE);
}

void Rva007AEA2CArrayInits::initChatHistoryVectors()
{
	__ehvec_ctor(g_00E022F8, 0xC, 2, Rva00256646VectorCtorClosure, Rva00381AE0VectorDtor);
	atexit(destroyChatHistoryVectors);
}

void Rva007AEA2CArrayInits::initCursorTextures()
{
	__ehvec_ctor(cursorTextures, 4, 0x498, Rva00326BE6NullFirstWordCtor, Rva0017098DTextureHandleDtor);
	atexit(destroyCursorTextures);
}

void Rva007AEA2CArrayInits::initShaderTextureSlots()
{
	__ehvec_ctor(g_shaderTextureSlots, 4, 8, Rva00326BE6NullFirstWordCtor, Rva0017098DTextureHandleDtor);
	atexit(destroyShaderTextureSlots);
}
