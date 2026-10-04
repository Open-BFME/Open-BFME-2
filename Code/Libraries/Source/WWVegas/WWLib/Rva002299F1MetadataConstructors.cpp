// cl: /O1 /MD /EHsc /DNDEBUG
// BFME1 GameEngine.cpp and MapUtil.h at 1281192, reconciled with BFME2.
// Native MapCache22E28B allocates 36B and stores DFF12C in GameEngine::init;
// its metadata-map path22E272->22C68C->2299F1 allocates 276B headers.
// Existing MapMetaDataCopy independently proves 256B value records.
// Original template identities come from reference; address prefixes below
// preserve only observed construction state/ABI, never other map operations.
// Native relationships: MapCache22E28B -> map22E272 -> tree22C68C ->
// header2299F1 -> shared 11B proxy14F3C4 and byte allocator307F0/22.
// Header allocation 0x114 = observed 16B node header + 4B string key + 256B
// metadata. Pointer initialization at+0/+4/+8/+C and count+4 is independently
// observed in full 42B tree constructor. The extra tree word+8 stays opaque.
// Empty allocator objects are donor-derived stateless ABI arguments; their
// empty copy has no independent native identity and remains unpinned.
// Existing proxy binds only the proved
// ignored-reference/dword-copy thiscall ABI; no native proxy name is claimed.
namespace _STL { template<class T> class allocator; template<> class allocator<char> {
public: static char *allocate(unsigned int,const void*);
}; }
struct RvaMapCacheEmptyAllocator {
 // ?RvaMapCacheEmptyAllocator::RvaMapCacheEmptyAllocator present-unmatched
 __forceinline RvaMapCacheEmptyAllocator() {}
};
struct RvaMapCacheNodeHeader {
 unsigned char color00; unsigned char padding01[3];
 RvaMapCacheNodeHeader *parent04,*left08,*right0C;
};
class RvaMapCacheProxy0014F3C4 {
public:
 RvaMapCacheProxy0014F3C4(const RvaMapCacheEmptyAllocator&,RvaMapCacheNodeHeader*);
 RvaMapCacheNodeHeader *pointer00;
};
#pragma comment(linker,"/alternatename:??0RvaMapCacheProxy0014F3C4@@QAE@ABURvaMapCacheEmptyAllocator@@PAURvaMapCacheNodeHeader@@@Z=??0?$_STLP_alloc_proxy@IHV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@I@Z")
class Rva002299F1MetadataHeader {
public:
 __declspec(noinline) Rva002299F1MetadataHeader(const RvaMapCacheEmptyAllocator&);
 RvaMapCacheProxy0014F3C4 header00;
};
Rva002299F1MetadataHeader::Rva002299F1MetadataHeader(const RvaMapCacheEmptyAllocator&)
 :header00(RvaMapCacheEmptyAllocator(),0) {
 header00.pointer00=reinterpret_cast<RvaMapCacheNodeHeader*>(_STL::allocator<char>::allocate(0x114,0));
}
class Rva0022C68CMetadataTree {
public:
 __declspec(noinline) Rva0022C68CMetadataTree(const RvaMapCacheEmptyAllocator&,const RvaMapCacheEmptyAllocator&);
 Rva002299F1MetadataHeader base00;
 unsigned int count04,opaque08;
};
Rva0022C68CMetadataTree::Rva0022C68CMetadataTree(const RvaMapCacheEmptyAllocator&,const RvaMapCacheEmptyAllocator&allocator)
 :base00(allocator) {
 count04=0;
 base00.header00.pointer00->color00=0;
 base00.header00.pointer00->parent04=0;
 base00.header00.pointer00->left08=base00.header00.pointer00;
 base00.header00.pointer00->right0C=base00.header00.pointer00;
}
class Rva0022E272MetadataMap {
public:
 __declspec(noinline) Rva0022E272MetadataMap();
 Rva0022C68CMetadataTree tree00;
};
Rva0022E272MetadataMap::Rva0022E272MetadataMap()
 :tree00(RvaMapCacheEmptyAllocator(),RvaMapCacheEmptyAllocator()) {}
