// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URvaPair00207E26@@V?$allocator@URvaPair00207E26@@@_STL@@@_STL@@QAE@XZ @0x00207E26 63B.
// 8-byte AsciiString-keyed pair vector dtor: destroys range through rowed
// 8-byte DestroyPairs at 0x0032C0CA then frees via 0x00030830 (EH states 0/-1).
// ICF-twin family of rowed 0x004C3D4C/0x00257544 (StlportVectorDtorFamily.cpp).
// Called by ScriptEngine dtor 0x0020A473 plus Unwind funclets. Element is honest
// RvaPair address name for 8-byte AsciiString-plus-int layout retail proves.
#include <vector>
#include "ascii_string.h"
struct RvaPair00207E26 { AsciiString m_key; int m_value; public: ~RvaPair00207E26(); };
template _STL::vector<RvaPair00207E26>::~vector();

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00207E26Vector@@QAE@XZ=??1?$vector@URvaPair00207E26@@V?$allocator@URvaPair00207E26@@@_STL@@@_STL@@QAE@XZ")
