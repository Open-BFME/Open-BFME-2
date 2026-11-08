// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0005CE7E@GlobalVolumeData@MilesAudioManager@@QAEXPAVXfer@@@Z, retail 0x0005ce7e, 225 bytes. Banked partial (score 0.995) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native0005CE7E..0005CF5D and WB77A930 establish GlobalVolumeData snapshot.
// Current MilesAudioManager class and matched map serializer guide target layout.
// All225 body bytes match once the unprovided58DC6 set-xfer relocation is masked.
#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

namespace _STL {
struct _Rb_tree_node_base{int color;_Rb_tree_node_base*parent,*left,*right;};
template<class T>struct _Const_traits;
template<class T,class Traits>struct _Rb_tree_iterator{_Rb_tree_node_base*node;};
template<class T>struct _Rb_global{static _Rb_tree_node_base*_M_increment(_Rb_tree_node_base*);};
template<class T>struct less;
template<class T>class allocator;
template<class A,class B>struct pair{pair():first(A()),second(B()){} pair(const pair&o):first(o.first),second(o.second){} ~pair(){} A first;B second;};
template<class K,class C,class Al>class set{public:typedef _Rb_tree_iterator<K,_Const_traits<K> > iterator;pair<iterator,bool>insert(const K&);_Rb_tree_node_base*header;unsigned count;};
}
typedef _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > AsciiStringSet;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"

namespace _STL {
template<class K,class V,class C,class A>class map{char bytes[12];};
}
typedef _STL::map<AsciiString,float,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,float> > > AsciiFloatMap;
Xfer *Rva00058DC6Xfer(Xfer*,AsciiStringSet*);
Xfer *Rva0005CC28Xfer(Xfer*,AsciiFloatMap*);
#include "../../../GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h"
class MilesAudioManager::GlobalVolumeData {public:
 int view;float volume[6][2];char pad34[0x9C-0x34];float at9C;AsciiStringSet names;char padA8[4];float atAC,atB0,atB4,atB8,atBC,atC0;bool atC4;char padC5[0x1B8-0xC5];AsciiFloatMap map;
 void rva0005CE7E(Xfer*);void refreshAll();
};
void MilesAudioManager::GlobalVolumeData::rva0005CE7E(Xfer*xfer) {
 xfer->Version1();
 for(int i=0;i<6;++i)for(int j=0;j<2;++j)(*xfer == volume[i][j]);
 Rva00058DC6Xfer(xfer,&names);(*xfer == at9C);(*xfer == atC4);
 if(atC4){(*xfer == atAC);(*xfer == atB0);(*xfer == atB4);(*xfer == atB8);(*xfer == atBC);(*xfer == atC0);}
 Rva0005CC28Xfer(xfer,&map);refreshAll();
}
