// ?rva00302459@@YAXIPAV?$vector@PAVMapMetaData@@V?$allocator@PAVMapMetaData@@@_STL@@@_STL@@@Z
// partial score=0.9 date=2026-10-05
// ?rva00302459@@YAXIPAV?$vector@PAVMapMetaData@@V?$allocator@PAVMapMetaData@@@_STL@@@_STL@@@Z @0x00302459 99B.
// Collector-only TU (no defaultmap, no shared-header edits, no new pins).
//
// Target facts (game.dat read-only decode):
// - cdecl free function void (unsigned int flags, vector<MapMetaData*>* out);
//   EBP frame, single 4B local [ebp-4] push_back temp; ends leave/ret.
// - flags in EBX (mov ebx,[ebp+8]; test bl,0x40 gates clear).
// - clear path: mov ecx,[ebp+0xC]; push [ecx+4]; push [ecx]; call 0x31BD55
//   (rowed void* vector erase 34B; out->clear() spelling).
// - header triple-load: mov eax,[0xDFF12C]; mov eax,[eax]; mov esi,[eax+8];
//   cmp esi,eax (empty test; begin = header->[+8], end = header).
// - predicate slot: mov [ebp+8],ebx AFTER header load (0x302480);
//   loop calls 0x300021 as lea ecx,[ebp+8]/push edi where edi = [esi+0x14]
//   (node value at node+0x14).
// - append: mov ecx,[ebp+0xC]; lea eax,[ebp-4]; push eax with mov [ebp-4],edi;
//   call 0x4DFCB0 (rowed 49B pointer-vector push_back; ICF-folded alias).
// - increment: push esi; call 0x24250; mov esi,eax (rowed _M_increment 105B);
//   per-iteration reload mov eax,[0xDFF12C]; cmp esi,[eax]; jne loop.
// - global TheMapCache pointer at 0xDFF12C (also read by findMap 0x3024BC,
//   isValidMap 0x3057AB, updateCache path).
// - MapMetaData 256B proven by rowed copy 0x3039E8; predicate reads value
//   bytes +0x24/+0x25/+0x26 (rowed test 0x300021 masks 1/2 then 4/8 then
//   0x10/0x20).
//
// Donor facts:
// - Predicate 0x300021 ONLY has a named clean donor: BFME1
//   game/GameEngine/Source/Common/Bfme5TinySix3.cpp (Rva0044F630FlagTest)
//   at rev 1281192, landed as Rva00042FE4FlagTest.cpp row 54336.
// - Collector has NO clean donor. BFME1 Rva00453480MapPointerCollector.h
//   is same-family lead only (same walk purpose, same +0x24/25/26 bytes,
//   same _M_increment; direct goto-ladder filter, different constness and
//   providers). Do NOT port it as donor.
// - STLport providers (erase 31BD55, increment 24250, push_back 4DFCB0,
//   base 211E58, sort 304530 family) are rowed providers, not donors.
//
// Inference (not claimed as target fact):
// - Retail 302459 feeds retail 30582D (defaultmap REL32 calls 302459 with
//   flags (isMP?8:4)|1); original 302459 spelling unknown, hence rva name.
// - Comparator 0x30145C is PIN-ONLY (symbols 6645), not a collector dep.
//
// Build config (single-variable experiment vs banked 0.90 stash):
// - Banked reverse/attempts/0x00302459.cpp used /O1 /G7 /arch:SSE.
// - This TU uses plain /O1 /MD /EHsc with NO /G and NO /arch:SSE, plus
//   #pragma optimize("s", on) around the collector (size-leaf hypothesis:
//   one 4B local, dead-arg-slot reuse [ebp+8], out* reloaded not enregistered).
// - No /O2, no G5/G6/G7, no /Ob2, no clamp, no iterator-constness or
//   predicate-ctor respellings (all refuted per 9403 log).
// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
#include <map>
#include <algorithm>
#include "ascii_string.h"
class MapMetaData { public: char unknown00[0x50]; AsciiString m_fileName; char unknown54[0x100-0x54]; };
class MapCache:public _STL::map<AsciiString,MapMetaData> { public:void updateCache(); };
extern MapCache *TheMapCache;
struct Rva00300021Argument {char unknown00[0x24];bool byte24,byte25,byte26;};
class Rva00300021Flags {public:unsigned int flags;bool test(const Rva00300021Argument*) const;};
#pragma optimize("s", on)
void rva00302459(unsigned int flags,_STL::vector<MapMetaData*> *out) {
 if(!(flags&0x40))out->clear();
 MapCache::const_iterator it=TheMapCache->begin();
 Rva00300021Flags predicate={flags};
 for(;it!=TheMapCache->end();++it) {
  if(predicate.test(reinterpret_cast<const Rva00300021Argument*>(&it->second))) {MapMetaData *md=const_cast<MapMetaData*>(&it->second);out->push_back(md);}
 }
}
#pragma optimize("", on)
