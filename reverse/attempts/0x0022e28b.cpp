// ??0MapCache@@QAE@XZ
// partial score=0.99 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Bank: full61B normal exact with these individually full-byte-verified
// direct constructor bindings; none of these trial pins was retained:
// ??0?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@_STL@@U12@V?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@_STL@@@1@PAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@1@@Z ->0x0014F3C4/11B
// ??0?$_Rb_tree_base@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@1@@Z ->0x002299F1/39B
// ??0?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@3@@_STL@@QAE@ABU?$less@VAsciiString@@@1@ABV?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@1@@Z ->0x0022C68C/42B
// ??0?$map@VAsciiString@@VMapMetaData@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@4@@_STL@@QAE@XZ ->0x0022E272/25B
// ??0?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@_N@_STL@@@_STL@@U12@V?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@_N@_STL@@@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@_N@_STL@@@_STL@@@1@PAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@_N@_STL@@@1@@Z ->0x0014F3C4/11B
// ??0?$_Rb_tree_base@U?$pair@$$CBVAsciiString@@_N@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@1@@Z ->0x001F0534/36B
// ??0?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@@_STL@@QAE@ABU?$less@VAsciiString@@@1@ABV?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@1@@Z ->0x001F068F/42B
// ??0?$map@VAsciiString@@_NU?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@@_STL@@QAE@XZ ->0x0033C432/25B
// BLOCKED: existing selected-wrong tree destructors for metadata/seen/allowed
// maps and existing AsciiString set-base ctor; full header instantiation also
// emits losing allocator/pair/cleanup copies. Constructor-only specializations
// below suppress most new copies but cannot repair these existing providers.
// Target identity: native22FE81 allocation36B,22FE9C call and22FEAB DFF12C
// store agree with independently matched MapCache::findMap3024BC and
// reference MapUtil.h base-map/m_seen/m_allowedMaps layout. Metadata256B
// is independently proved by MapMetaDataCopy and276B native header allocation.

#include <map>
#include <set>
#include "ascii_string.h"
bool operator<(const AsciiString &,const AsciiString &);
class MapMetaData { public: ~MapMetaData(); unsigned char opaque[0x100]; };
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,MapMetaData>,_STL::_Select1st<_STL::pair<const AsciiString,MapMetaData> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,MapMetaData> > > MetaTree;
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,bool>,_STL::_Select1st<_STL::pair<const AsciiString,bool> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,bool> > > SeenTree;
typedef _STL::_Rb_tree<AsciiString,AsciiString,_STL::_Identity<AsciiString>,_STL::less<AsciiString>,_STL::allocator<AsciiString> > AllowedTree;
template<> MetaTree::~_Rb_tree();
template<> SeenTree::~_Rb_tree();
template<> AllowedTree::~_Rb_tree();
class MapCache: public _STL::map<AsciiString,MapMetaData> {
public: MapCache();
private: _STL::map<AsciiString,bool> m_seen; _STL::set<AsciiString> m_allowedMaps;
};
MapCache::MapCache() {}
