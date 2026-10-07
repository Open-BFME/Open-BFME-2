// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?XferMap@PSPlayerStats@@QAEXPAVMapHolder@@PAVXferStub@@@Z @0x005548E9 177B unlock lane map uchar-short xfer.
// Evidence: callers at 0x005550A0 0x00555109 0x0055573B 0x00555988; callees map op[] 0x00554816 inc 0x00024250 clear 0x003828B6; honest address names.
#include <map>

// Use the native creator from the common pair/clone unit, rather than
// emitting the generic malloc-based creator's different 32-byte body.
typedef _STL::pair<const unsigned char, short> BfmeByteWordNodeValue;
typedef _STL::_Rb_tree<unsigned char, BfmeByteWordNodeValue,
    _STL::_Select1st<BfmeByteWordNodeValue>, _STL::less<unsigned char>,
    _STL::allocator<BfmeByteWordNodeValue> > BfmeByteWordNodeTree;
template <> _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_create_node(const BfmeByteWordNodeValue &value);

class XferStub {
public:
	virtual ~XferStub();
	virtual void _d1();
	virtual bool _isWriting();
	virtual void _d3();
	virtual void _d4();
	virtual void _d5();
	virtual void _d6();
	virtual void _d7();
	virtual void _d8();
	virtual void _d9();
	virtual void _d10();
	virtual void _d11();
	virtual void _d12();
	virtual void _d13();
	virtual void _d14();
	virtual void _d15();
	virtual void _d16();
	virtual void _d17();
	virtual void _d18();
	virtual void _d19();
	virtual void _d20();
	virtual void _d21();
	virtual void _d22();
	virtual void _d23();
	virtual void _d24();
	virtual void _d25();
	virtual void _d26();
	virtual void _d27();
	virtual void _slot70(float &v);
	virtual void _d29();
	virtual void _slot78(int &v);
	virtual void _d31();
	virtual void _slot80(short &v);
	virtual void _d33();
	virtual void _slot88(unsigned char &v);
};

class MapHolder : public _STL::map<unsigned char, short> {
};

class Rva0038201D {
public:
	void rva003828B6();
};

class MapFloatHolder : public _STL::map<unsigned char, float> {};
class MapIntHolder : public _STL::map<unsigned char, int> {};
class Rva0038204A { public: void rva003828DF(); };
class Rva00382077 { public: void rva00382908(); };
template <> float &_STL::map<unsigned char, float>::operator[](const unsigned char &);
template <> int &_STL::map<unsigned char, int>::operator[](const unsigned char &);

class PSPlayerStats
{
public:
	void XferMap(MapHolder *a, XferStub *b);
	void rva0055499A(MapFloatHolder *a, XferStub *b);
	void rva00554A4A(MapIntHolder *a, XferStub *b);
};

void PSPlayerStats::XferMap(MapHolder *a, XferStub *b)
{
	unsigned int cnt = *(unsigned int *)((char *)a + 4);
	unsigned int n = cnt;
	b->_slot78((int &)n);
	if (b->_isWriting()) {
		for (MapHolder::iterator it = a->begin(); it._M_node != a->end()._M_node; ++it) {
			unsigned char k = (*it).first;
			short v = (*it).second;
			b->_slot88(k);
			b->_slot80(v);
		}
		return;
	}
	((Rva0038201D *)a)->rva003828B6();
	if (n <= 0U)
		return;
	do {
		unsigned char k;
		short v;
		b->_slot88(k);
		b->_slot80(v);
		(*a)[k] = v;
	} while (--n != 0);
}

// Retail 0x0055499A: uchar/float map, node key +0x10 and value +0x14; xfer slots 0x88/0x70.
void PSPlayerStats::rva0055499A(MapFloatHolder *a, XferStub *b)
{
	unsigned int cnt = *(unsigned int *)((char *)a + 4);
	unsigned int n = cnt;
	b->_slot78((int &)n);
	if (b->_isWriting()) {
		for (MapFloatHolder::iterator it = a->begin(); it._M_node != a->end()._M_node; ++it) {
			unsigned char k = (*it).first;
			float v = (*it).second;
			b->_slot88(k);
			b->_slot70(v);
		}
		return;
	}
	((Rva0038204A *)a)->rva003828DF();
	if (n <= 0U)
		return;
	do {
		unsigned char k;
		float v;
		b->_slot88(k);
		b->_slot70(v);
		(*a)[k] = v;
	} while (--n != 0);
}

// Retail 0x00554A4A: uchar/int map, node key +0x10 and value +0x14; xfer slots 0x88/0x78.
void PSPlayerStats::rva00554A4A(MapIntHolder *a, XferStub *b)
{
	unsigned int cnt = *(unsigned int *)((char *)a + 4);
	unsigned int n = cnt;
	b->_slot78((int &)n);
	if (b->_isWriting()) {
		for (MapIntHolder::iterator it = a->begin(); it._M_node != a->end()._M_node; ++it) {
			unsigned char k = (*it).first;
			int v = (*it).second;
			b->_slot88(k);
			b->_slot78(v);
		}
		return;
	}
	((Rva00382077 *)a)->rva00382908();
	if (n <= 0U)
		return;
	do {
		unsigned char k;
		int v;
		b->_slot88(k);
		b->_slot78(v);
		(*a)[k] = v;
	} while (--n != 0);
}
