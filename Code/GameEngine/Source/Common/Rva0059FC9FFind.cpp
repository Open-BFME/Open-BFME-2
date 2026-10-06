// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// ?rva0059FC9F@Rva0059FC9F@@QAEHXZ @ 0x0059FC9F (155B).
// Lookup helper: copies Rva0059F479 record from this+0x58+0x298, fetches the
// RB-tree map from the GameSpy-like global at 0x00A02320 (vtable slot 0xA4),
// then linear-searches nodes comparing the record's first string (Open2Rec
// m_at08 at rec+12) against each node's Rva0059F340 field string via rowed
// compare 0x000069D6. Returns the node's int at +0x10 or -1. Temp AsciiString
// at ebp-0x10 destroyed via rowed releaseBuffer 0x00036410; record tail at
// ebp-0x24 destroyed via rowed dtor 0x00416088 (layout shares first 0x10B
// with Open2Rec3A4420, trailing int trivial). Rows: copy 0x0059F479, get
// 0x0059F340, compare 0x000069D6, release 0x00036410, increment 0x00024250,
// dtor 0x00416088. Callers 0x005A57BA/0x005A61C6.

template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void releaseBuffer() throw();
public:
	int compare(const StringBase<T> &other) const throw();
	__forceinline ~StringBase() { releaseBuffer(); }
private:
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class AsciiString : public StringBase<char>
{
public:
	__forceinline AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	__forceinline AsciiString() {}
	__forceinline ~AsciiString() {}
	AsciiString &operator=(const AsciiString &other);
};

class Rva0059F340AsciiField
{
public:
	AsciiString get() const throw();
private:
	char m_pad[0xFDC];
	AsciiString m_value;
};

struct Rva00416088
{
	unsigned int m_00;
	unsigned int m_04;
	AsciiString m_08;
	AsciiString m_0C;
	~Rva00416088();
};

class Rva0059F479
{
public:
	int m_00;
	Rva00416088 m_04;
	int m_14;
	Rva0059F479(const Rva0059F479 &other);
};

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *) throw();
};
}

struct MapNode
{
	_STL::_Rb_tree_node_base m_base;
	int m_id10;
	Rva0059F340AsciiField *m_field14;
};

struct MapHolder
{
	_STL::_Rb_tree_node_base *m_header;
};

class MapProvider
{
public:
	virtual void f00();
	virtual void f04();
	virtual void f08();
	virtual void f0c();
	virtual void f10();
	virtual void f14();
	virtual void f18();
	virtual void f1c();
	virtual void f20();
	virtual void f24();
	virtual void f28();
	virtual void f2c();
	virtual void f30();
	virtual void f34();
	virtual void f38();
	virtual void f3c();
	virtual void f40();
	virtual void f44();
	virtual void f48();
	virtual void f4c();
	virtual void f50();
	virtual void f54();
	virtual void f58();
	virtual void f5c();
	virtual void f60();
	virtual void f64();
	virtual void f68();
	virtual void f6c();
	virtual void f70();
	virtual void f74();
	virtual void f78();
	virtual void f7c();
	virtual void f80();
	virtual void f84();
	virtual void f88();
	virtual void f8c();
	virtual void f90();
	virtual void f94();
	virtual void f98();
	virtual void f9c();
	virtual void fa0();
	virtual MapHolder *getMap();
};

// ?g_00A02320@@3PAVMapProvider@@A: the global at this VA is ?TheGameSpyInfo@@3PAVGameSpyInfoInterface@@A; this name is an alias for it.
extern MapProvider * g_00A02320;
#pragma comment(linker, "/alternatename:?g_00A02320@@3PAVMapProvider@@A=?TheGameSpyInfo@@3PAVGameSpyInfoInterface@@A")

struct Outer58
{
	char m_pad[0x298];
	Rva0059F479 m_rec298;
};

class Rva0059FC9F
{
public:
	int rva0059FC9F();
private:
	char m_pad[0x58];
	Outer58 *m_58;
};

int Rva0059FC9F::rva0059FC9F()
{
	Rva0059F479 rec(m_58->m_rec298);
	MapHolder *map = g_00A02320->getMap();
	_STL::_Rb_tree_node_base *node = map->m_header->_M_left;
	int out;
	if (node == map->m_header)
		goto neg;
	do
	{
		MapNode *mn = (MapNode *)node;
		unsigned char isEqual = (unsigned char)(mn->m_field14->get().compare((const StringBase<char> &)rec.m_04.m_08) == 0);
		if (isEqual != 0)
		{
			out = mn->m_id10;
			goto done;
		}
		node = _STL::_Rb_global<bool>::_M_increment(node);
	} while (node != map->m_header);
neg:
	out = -1;
done:
	return out;
}
