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

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version); // +0x28
	virtual Xfer &xferTypeName(const char *const &name); // +0x2C
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual Xfer &xferAsciiString(AsciiString *value); virtual void xferReal(float *value); virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value); // +0x78
 virtual void slot31();virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();virtual void xferBool(bool*);
 void Version1();
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

namespace _STL {
template<class K,class V,class C,class A>class map{char bytes[12];};
}
typedef _STL::map<AsciiString,float,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,float> > > AsciiFloatMap;
Xfer *Rva00058DC6Xfer(Xfer*,AsciiStringSet*);
Xfer *Rva0005CC28Xfer(Xfer*,AsciiFloatMap*);
class MilesAudioManager {public:class GlobalVolumeData {public:
 int view;float volume[6][2];char pad34[0x9C-0x34];float at9C;AsciiStringSet names;char padA8[4];float atAC,atB0,atB4,atB8,atBC,atC0;bool atC4;char padC5[0x1B8-0xC5];AsciiFloatMap map;
 void rva0005CE7E(Xfer*);void refreshAll();
};};
void MilesAudioManager::GlobalVolumeData::rva0005CE7E(Xfer*xfer) {
 xfer->Version1();
 for(int i=0;i<6;++i)for(int j=0;j<2;++j)xfer->xferReal(&volume[i][j]);
 Rva00058DC6Xfer(xfer,&names);xfer->xferReal(&at9C);xfer->xferBool(&atC4);
 if(atC4){xfer->xferReal(&atAC);xfer->xferReal(&atB0);xfer->xferReal(&atB4);xfer->xferReal(&atB8);xfer->xferReal(&atBC);xfer->xferReal(&atC0);}
 Rva0005CC28Xfer(xfer,&map);refreshAll();
}
