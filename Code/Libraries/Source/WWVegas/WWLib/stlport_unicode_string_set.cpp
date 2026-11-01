// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Native604D64..604DFD unique insert uses the established retail tree-layout
// option: leftmost-parent shortcut inserts with parent,parent before the
// predecessor check. Comparator37B40 and node creation604C57 independently
// establish UnicodeString key nodes20B. BFME1 reference6583b3c1 STLport4.5.3
// and ZH MapUtil set supply algorithm; original application owner unknown.
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// MapUtil's UnicodeString set supplies the donor instantiation. Target nodes
// allocate 20 bytes: 16-byte tree links plus the four-byte string handle.
// The value constructor at54DF6 and comparison at6AA4 establish the string
// type; the enclosing target caller's public identity remains unknown.
#include <memory>
#include <set>
#include <utility>

#include "../../../../GameEngine/Include/Common/BfmeStringData.h"
#include "unicode_string.h"
namespace _STL {
typedef _Rb_tree_node<UnicodeString> UnicodeNode;
template<> __declspec(dllimport) __forceinline UnicodeNode* allocator<UnicodeNode>::allocate(size_t n,const void*)const {return n!=0 ? reinterpret_cast<UnicodeNode*>(allocator<char>::allocate(n*sizeof(UnicodeNode),0)):0;}
template<> __declspec(dllimport) __forceinline UnicodeNode* _STLP_alloc_proxy<UnicodeNode*,UnicodeNode,allocator<UnicodeNode> >::allocate(size_t n) {return __stl_alloc_rebind(static_cast<allocator<UnicodeNode>&>(*this),(UnicodeNode*)0).allocate(n,0);}
}
namespace rts {
    template <class T> struct less_than_nocase {
        bool operator()(const T &a, const T &b) const { return a.compareNoCase(b) < 0; }
    };
    // Use the byte-verified comparator at 0x00037B40; /O1's local copy differs.
    template <> bool less_than_nocase<UnicodeString>::operator()(
        const UnicodeString &a, const UnicodeString &b) const;
}
// Preserve the tree helpers' calls to the retail comparator at 0x00037B40;
// this instantiation must not emit its own non-retail standalone copy.
namespace rts {
    template <>
    bool less_than_nocase<UnicodeString>::operator()(const UnicodeString &a, const UnicodeString &b) const;
}
typedef std::set<UnicodeString, rts::less_than_nocase<UnicodeString> > UnicodeNameSet;

std::pair<UnicodeNameSet::iterator, bool> Force_UnicodeStringSet_insert(UnicodeNameSet &s, const UnicodeString &v)
{
    return s.insert(v);
}
UnicodeNameSet::iterator Force_UnicodeStringSet_find(UnicodeNameSet &s, const UnicodeString &v)
{
    return s.find(v);
}

// Native604DFD (20B, after the unique insert): set::find, the hidden-return
// iterator around the rowed _M_find 0x00604D0E.
template UnicodeNameSet::iterator UnicodeNameSet::find<UnicodeString>(const UnicodeString &) const;
