// cl: /Ob0 /MD /EHsc
// Clean C++ donor: Open-BFME/Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69,
// game/GameEngine/Source/Common/Rva00C6DC90ArrayInit.cpp, b1 0x00C6DC90.
// Native BFME2 initializer 0x007B67C0 (39B, independent int3 extent) passes
// storage VA 0x00E18388, stride 4, count 178, reset callback 0x006D2F90 and
// destructor 0x006D3010 to the rowed EH vector constructor iterator, then
// registers cleanup 0x007B9C60 via the rowed CRT atexit helper.
// Native callbacks independently resolve to EAStringC::clear and destructor.
// The constructor alias uses the verified reset's compatible thiscall ABI;
// it returns this after storing the empty block and incrementing its refcount.
// The opaque one-pointer element view preserves the native initialization
// and lifetime operations without claiming an original class or array name.
// The compiler's _$E1 and _$E2 are selected in ledger object-symbol notes.
// Existing cleanup 0x007B9C60 remains one 23B row; its former raw-storage
// unit is replaced here so this array has one owner and one registration.

class Rva007B67C0Element
{
    void *m_block;
public:
    Rva007B67C0Element();
    ~Rva007B67C0Element();
};
#pragma comment(linker, "/alternatename:??0Rva007B67C0Element@@QAE@XZ=?clear@EAStringC@@QAEAAV1@XZ")
#pragma comment(linker, "/alternatename:??1Rva007B67C0Element@@QAE@XZ=??1EAStringC@@QAE@XZ")
extern "C" Rva007B67C0Element bfmeObjDAE[178];
Rva007B67C0Element bfmeObjDAE[178];
