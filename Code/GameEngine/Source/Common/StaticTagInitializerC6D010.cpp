// cl: /O2 /Ob0
// Carried from the Open-BFME-1 donor at submodule revision 77db49c3
// (game/GameEngine/Source/Common/StaticTagInitializers.cpp, b1 0x00C6D010).
// The first "msgr" record, AUTH, as a file-scope object. MSVC 7.1 emits its
// .text$yc dynamic initializer _$E1 and a .CRT$XCU entry. The body is
// mov eax, [type]; push 'AUTH'; push eax; mov ecx, &record; call ctor; ret,
// byte-identical to retail 0x007B5DF0, which retail's table names first
// among the msgr records. The other records follow in StaticTagInitializers.cpp,
// and the (int, int) constructor 0x0065D090 is in Rva007F0210Set.cpp.

class Rva007F0210
{
    int m_00;
    int m_04;
    int m_08;

public:
    Rva007F0210(int a, int b);
};

// The "msgr" service type, defined beside the msgr codec object in
// Rva007B5DE0StaticInstance.cpp.
extern int bfmeRva012C3B38TagValue;
// bfmeRva0130A98CTagSlot: the AUTH record at VA 0xe0a3a4 (zero-filled until its initializer runs).
Rva007F0210 bfmeRva0130A98CTagSlot(bfmeRva012C3B38TagValue, 'AUTH');
