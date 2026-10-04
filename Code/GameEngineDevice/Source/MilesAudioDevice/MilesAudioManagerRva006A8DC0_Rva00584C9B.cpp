// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/MilesAudioDevice
// stlport
//
// ?begin@?$deque@VPlayingAudioRef@@V?$allocator@VPlayingAudioRef@@@_STL@@@_STL@@QAE?AU?$_Deque_iterator@VPlayingAudioRef@@U?$_Nonconst_traits@VPlayingAudioRef@@@_STL@@@2@XZ
// retail 0x00584C9B, 19 bytes.
//
// This is NOT a body the donor TU can be copied from. The BFME 1 donor sweep
// credits the symbol to a HEADER the translation unit includes
// (game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerRva006A8DC0.cpp
// at reference/open-bfme-1 @ 6d943426), not to the TU, so land.py refuses to
// prepare one. Retail does carry begin() out of line, and the landed sibling
// Code/Libraries/Source/WWVegas/WWLib/stlport_deque_e16_o1.cpp is the proven way
// to make this compiler emit it: an explicit instantiation of the container.
//
//   00584C9B  8b 44 24 04        mov eax, [esp+4]      ; the hidden return slot
//   00584C9F  56                 push esi
//   00584CA0  57                 push edi
//   00584CA1  8b f1              mov esi, ecx
//   00584CA3  8b f8              mov edi, eax
//   00584CA5  a5                 rep movsd             ; x4 = 16 bytes
//   00584CA6  a5
//   00584CA7  a5
//   00584CA8  a5
//   00584CA9  5f                 pop edi
//   00584CAA  5e                 pop esi
//   00584CAB  c2 04 00           ret 4
//
// with 0x00584C9A (`00`) immediately before it, so the boundary is proven.
//
// WHAT IT IS. stl/_deque.h:387 is `iterator begin() { return this->_M_start; }`,
// so the body is a by-value copy of the deque's start iterator: _Deque_iterator
// is _M_cur plus _M_first plus _M_last plus _M_node, four pointers, and the four
// `rep movsd` is MSVC 7.1's 16-byte block move for them. The `QAE?AU...2@XZ`
// mangling is the by-value hidden-return convention -- [esp+4] is the caller's
// return slot and `ret 4` pops no argument, since begin() takes none.
//
// The element type only fixes that 16-byte stride through the traits, and
// PlayingAudioRef is a single-pointer class here: its copy constructor and
// operator= are user-declared, but the emitted copy is the raw pointer move, so
// nothing of the element is touched.

#include <deque>

// The retail element type, spelled as the donor declares it. Only its size
// reaches the emitted code -- the four-pointer _Deque_iterator block move -- so
// no PlayingAudio member is touched and the declaration can stay minimal.
class PlayingAudio;

class PlayingAudioRef
{
public:
	PlayingAudioRef(PlayingAudio *p = 0) : m_ptr(p) {}
	PlayingAudio *operator->() const { return m_ptr; }

private:
	PlayingAudio *m_ptr;
};

template class _STL::deque<PlayingAudioRef, _STL::allocator<PlayingAudioRef> >;