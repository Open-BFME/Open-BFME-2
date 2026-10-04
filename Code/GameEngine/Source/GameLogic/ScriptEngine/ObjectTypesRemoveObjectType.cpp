// cl: /Ireference/shims/bfme2_ascii /O1 /MD /DNDEBUG
// Clean reference: BFME1 game/GameEngine/Source/GameLogic/Object/
// ObjectTypesRemoveObjectType.cpp at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// itself preserving the Zero Hour ObjectTypes::removeObjectType algorithm.
// Native 0x00376B1E/50 calls contains 0x00376A62/34, find 0x000BD22F/27,
// then this erase 0x003769C2/55 on the vector prefix at ObjectTypes+8.
// ObjectTypes identity comes from its native vtable/name getter and constructor
// family (0x003769F9, 0x00376A19), independently of the donor's method label.
// Original template/payload spellings at 0x003769C2 are not established.
// The historical generated ledger name is retained only as a compatibility
// alias; object-symbol names the verified address view below. It is not an
// original payload-name claim. No source under Code/gen_small is edited.
//
// Native erase observes 4-byte elements and finish at vector+4, shifts the
// suffix through the existing 0x000B6614/29 copy wrapper, decrements finish,
// then reaches the existing 0x0048BA39/5 narrow-string cleanup entry.
// The copy wrapper routes to 0x000B4431/47, whose loop calls StringBase<char>
// assignment; cleanup tail-jumps to releaseBuffer 0x00036410/133. Canonical
// AsciiString/StringBase supply the proven width and character-buffer ABI.
// The cleanup address view binds to the real rowed destructor using a linker
// alias; it introduces no literal address and no synthetic runtime provider.
// Inline end() preserves the donor header's access/codegen pattern. An
// uninitialized empty copy tag carries no value, as the native caller does.

#include "ascii_string.h"
namespace _STL {
struct __false_type {};

template<class Input,class Output> Output __copy_ptrs(Input,Input,Output,const __false_type&);
}
struct Rva0048BA39StringElement {
 void *data;
 ~Rva0048BA39StringElement();
};
class Rva003769C2StringVector {
public:
 AsciiString *first;
 AsciiString *finish;
 AsciiString *capacity;
 AsciiString *end() { return finish; }
 AsciiString *erase(AsciiString *position);
};

// ?erase@?$vector@UGen_t_001db910_p4cd@@V?$allocator@UGen_t_001db910_p4cd@@@_STL@@@_STL@@QAEPAUGen_t_001db910_p4cd@@PAU3@@Z
AsciiString *Rva003769C2StringVector::erase(AsciiString *position) {
 if(position+1!=end()) {
  _STL::__false_type tag;
  _STL::__copy_ptrs(position+1,end(),position,tag);
 }
 --finish;
 reinterpret_cast<Rva0048BA39StringElement *>(finish)->~Rva0048BA39StringElement();
 return position;
}


#pragma comment(linker, "/alternatename:??1Rva0048BA39StringElement@@QAE@XZ=??1AsciiString@@QAE@XZ")

#pragma comment(linker, "/alternatename:?erase@?$vector@UGen_t_001db910_p4cd@@V?$allocator@UGen_t_001db910_p4cd@@@_STL@@@_STL@@QAEPAUGen_t_001db910_p4cd@@PAU3@@Z=?erase@Rva003769C2StringVector@@QAEPAVAsciiString@@PAV2@@Z")
