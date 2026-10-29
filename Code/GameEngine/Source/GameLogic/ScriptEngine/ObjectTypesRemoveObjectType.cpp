// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ivendor /Ireference/shims/bfmealloc
// stlport
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
#include <stlport/stl/_algobase.h>
#include <vector>

// Retail's vector<AsciiString>::erase calls the out-of-line pointer copy (the
// rowed 0x000B6614 wrapper); the explicit instantiation declaration keeps the
// call on that external instance instead of expanding the template inline.
template AsciiString * _STL::__copy_ptrs<AsciiString *, AsciiString *>(AsciiString *, AsciiString *, AsciiString *, _STL::__false_type const &);
class Rva003769C2StringVector {
public:
 AsciiString *first;
 AsciiString *finish;
 AsciiString *capacity;
 AsciiString *end() { return finish; }
 AsciiString *begin() { return first; }
 AsciiString *erase(AsciiString *position);
};

// ?erase@?$vector@UGen_t_001db910_p4cd@@V?$allocator@UGen_t_001db910_p4cd@@@_STL@@@_STL@@QAEPAUGen_t_001db910_p4cd@@PAU3@@Z
AsciiString *Rva003769C2StringVector::erase(AsciiString *position) {
 if(position+1!=end()) {
  _STL::__false_type tag;
  _STL::__copy_ptrs(position+1,end(),position,tag);
 }
 --finish;
 ((AsciiString *)finish)->~AsciiString();
 return position;
}


#pragma comment(linker, "/alternatename:?erase@?$vector@UGen_t_001db910_p4cd@@V?$allocator@UGen_t_001db910_p4cd@@@_STL@@@_STL@@QAEPAUGen_t_001db910_p4cd@@PAU3@@Z=?erase@Rva003769C2StringVector@@QAEPAVAsciiString@@PAV2@@Z")

// Native ObjectTypes storage prefix from the established constructor family:
// vptr/list-name occupy the first8 bytes, and the observed vector starts+8.
// This address view introduces no additional private ObjectTypes definition.
class ObjectTypes {
 unsigned char prefix[8];
 Rva003769C2StringVector values;
public:
 bool isInSet(const AsciiString &name) const;
 void remove(const AsciiString &name);
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *,StringBase<char> *,const StringBase<char> &);
// ?remove@ObjectTypes@@QAEXABVAsciiString@@@Z
void ObjectTypes::remove(const AsciiString &name) {
 const StringBase<char> &needle=*reinterpret_cast<const StringBase<char> *>(&name);
 if(isInSet(name)) {
  AsciiString *position=reinterpret_cast<AsciiString *>(Rva000BD22FFind(
   reinterpret_cast<StringBase<char> *>(values.begin()),
   reinterpret_cast<StringBase<char> *>(values.end()),needle));
  values.erase(position);
 }
}
