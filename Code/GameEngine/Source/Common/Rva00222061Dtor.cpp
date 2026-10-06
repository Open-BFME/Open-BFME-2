// cl: /MD /EHsc
// ??1Rva00222061@@UAE@XZ retail 0x00221FFA 74B
// Own vptr BE6C3C; the AsciiString-keyed tree at +0x28 is torn down through
// its rowed _Rb_tree dtor 0x00221E02 (EH state 1), the member at +0xC through
// the rowed ??1Open2Dtor4793C0@@QAE@XZ 0x002218D0 (state 0), then the rowed
// base dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74. Tree spelling as
// in stlport_rb_tree_hint_00221e02_dtor.cpp. Names address-derived.

class AsciiString;
struct TreeHintRef00221D6B;

namespace _STL {
template<class T> class allocator {};
template<class First, class Second> struct pair;
template<class Pair> struct _Select1st;
template<class T> struct less {};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree {
public:
    ~_Rb_tree();
private:
    void *header;
    unsigned int nodeCount;
    Compare keyCompare;
};

typedef pair<const AsciiString, TreeHintRef00221D6B> HintValue;
typedef _Rb_tree<AsciiString, HintValue, _Select1st<HintValue>,
    less<AsciiString>, allocator<HintValue> > HintTree;
}

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Open2Dtor4793C0
{
public:
	~Open2Dtor4793C0();

private:
	unsigned char m_pad[0x1C];
};

class Rva00222061 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00222061();

private:
	Open2Dtor4793C0 m_0C; // +0x0C
	_STL::HintTree m_tree; // +0x28
};

Rva00222061::~Rva00222061()
{
}
