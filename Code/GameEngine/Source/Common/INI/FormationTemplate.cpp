// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/ini
// "FormationTemplate" INI block parser (retail 0x00425842, 818 B) and the
// formation template object it builds (constructor retail 0x004257AD, 84 B).
// Original class and member names are unknown: LightPoint/LightSubPoint are
// the ledger's existing spellings for this object and its row element (its
// unwind funclet 0x00787199 destroys the member with the rowed
// vector<LightSubPoint> destructor 0x00425717), and the STL views use the
// ledger's folded callee spellings.
// Target evidence (parser): GapBodiesS3E's block table pairs "FormationTemplate"
// with 0x00425842; the literals name the block and its "Rows" field (parsed by
// the rowed 0x00425421 into the three-level deque the rowed 0x00425806 builds at
// +0x08 and the rowed 0x00425756 destroys). Each parsed cell key is looked up
// in the int map at 0x00E03168; the template gets a per-row list of cell lists
// (+0x00, 12-byte elements) and a de-duplicated per-row list (+0x0C), and is
// appended to the pointer deque at 0x00E03174 whose index the int map at
// 0x00E0319C records under the template key (FormationSelectionCriteria
// 0x00424185 reads it back).
// Target evidence (constructor): retail 0x004257AD builds a temporary at
// ebp-0x28 with 0x00424CB6, passes it to the rowed vector fill constructor
// 0x0042545A for the member at +0x00, destroys it with LightSubPoint's rowed
// destructor 0x004247E3 and stores its first argument at +0x0C; the destructor
// thunk 0x00425801 and scalar deleting destructor 0x00425826 tear the same
// object down.
#include <stdlib.h>
#include "ascii_string.h"
#include "../../../Include/Common/INI/FieldParse.h"


inline void *operator new(unsigned int, void *where) throw() { return where; }

class INI;
typedef void (*Parser)(INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/INI.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
void Rva00425421Parse(INI *ini, void *what);
void rva00425842(INI *ini, void *instance, void *store, const void *userData);

class ModuleData;
struct BfmeOpaque40;
struct Rva001408C0Target;
struct BfmeWordValue4
{
	int m_key;
};

// STLport 4.5.3 bodies of the callees that receive a local's address stay
// visible, as in retail's header-only STLport; each compiles to its rowed body.
namespace _STL {
template <class T> class allocator;
template <> class allocator<char>
{
public:
	static char *allocate(unsigned n, const void *hint);
};
template <class T> class allocator
{
public:
	allocator() {}
	T *allocate(unsigned n, const void * = 0) const
	{
		return n != 0 ? reinterpret_cast<T *>(allocator<char>::allocate(n * sizeof(T), 0)) : 0;
	}
	void deallocate(T *p, unsigned) const
	{
		if (p != 0)
			::free((void *)p);
	}
};
// The deque buffer allocation stays inline; retail's allocator<void *> body
// (0x00620180) belongs to its rowed unit, so this TU emits no copy.
template <> __declspec(dllimport) __forceinline void **allocator<void *>::allocate(unsigned n, const void *) const
{
	return n != 0 ? reinterpret_cast<void **>(allocator<char>::allocate(n * sizeof(void *), 0)) : 0;
}
template <class V, class T, class A> class _STLP_alloc_proxy : public A
{
public:
	T *allocate(unsigned n) { return A::allocate(n, 0); }
	void deallocate(T *p, unsigned n) { A::deallocate(p, n); }
	V _M_data;
};
template <class T> inline void _Construct(T *p, const T &value)
{
	new (p) T(value);
}
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
template <class OutputIter, class Size, class T> inline OutputIter fill_n(OutputIter first, Size n, const T &value)
{
	for (; n > 0; --n, ++first)
		*first = value;
	return first;
}
void *__copy_trivial(const void *first, const void *last, void *result);
template <class A, class B> struct pair
{
	pair();
	pair(const A &a, const B &b) : first(a), second(b) {}
	A first;
	B second;
};
struct __true_type
{
};
template <class T> struct _Identity
{
};
template <class P> struct _Select1st
{
};
template <class T> struct less
{
};
template <class T> struct _Const_traits
{
};
template <class T> struct _Nonconst_traits
{
};
template <class V> struct _Rb_tree_node
{
	int _M_color;
	void *_M_parent;
	void *_M_left;
	void *_M_right;
	V _M_value_field;
};
template <class V, class Tr> struct _Rb_tree_iterator
{
	_Rb_tree_iterator();
	void *_M_node;
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
	friend void ::rva00425842(INI *, void *, void *, const void *);
	template <class KT> _Rb_tree_node<V> *_M_find(const KT &key) const;
public:
	pair<_Rb_tree_iterator<V, _Nonconst_traits<V> >, bool> insert_unique(const V &value);
	_Rb_tree_node<V> *_M_header;
	unsigned _M_node_count;
	C _M_key_compare;
};
template <class K, class T, class C = less<K>, class A = allocator<pair<const K, T> > > class map
{
public:
	T &operator[](const K &key);
	_Rb_tree<K, pair<const K, T>, _Select1st<pair<const K, T> >, C, A> _M_t;
};
// The set's lookups use the rowed pointer-key find 0x00357180.
template <class K, class C = less<K>, class A = allocator<K> > class set
{
public:
	set();
	__declspec(noinline) pair<_Rb_tree_iterator<K, _Const_traits<K> >, bool> insert(const K &value)
	{
		pair<_Rb_tree_iterator<K, _Nonconst_traits<K> >, bool> p = _M_t.insert_unique(value);
		return pair<_Rb_tree_iterator<K, _Const_traits<K> >, bool>(
			reinterpret_cast<const _Rb_tree_iterator<K, _Const_traits<K> > &>(p.first), p.second);
	}
	_Rb_tree<K, K, _Identity<K>, C, A> _M_t;
};
template <class T, class A = allocator<T> > class vector
{
public:
	vector(unsigned count, const T &value, const A &alloc = A());
	~vector();
	T *begin() { return _M_start; }
	unsigned size() const { return unsigned(_M_finish - _M_start); }
	T &operator[](unsigned n) { return *(begin() + n); }
	__declspec(noinline) void push_back(const T &x)
	{
		if (_M_finish != _M_end_of_storage._M_data)
		{
			_Construct(_M_finish, x);
			++_M_finish;
		}
		else
			_M_insert_overflow(_M_finish, x, __true_type(), 1, true);
	}
	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, A> _M_end_of_storage;
protected:
	__declspec(noinline) void _M_insert_overflow(T *position, const T &x, const __true_type &, unsigned fillLen, bool atEnd = false)
	{
		const unsigned oldSize = size();
		const unsigned len = oldSize + (max)(oldSize, fillLen);
		T *newStart = _M_end_of_storage.allocate(len);
		T *newFinish = (T *)__copy_trivial(_M_start, position, newStart);
		newFinish = fill_n(newFinish, fillLen, x);
		if (!atEnd)
			newFinish = (T *)__copy_trivial(position, _M_finish, newFinish);
		_M_clear();
		_M_set(newStart, newFinish, newStart + len);
	}
	void _M_clear()
	{
		_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
	}
	void _M_set(T *start, T *finish, T *end)
	{
		_M_start = start;
		_M_finish = finish;
		_M_end_of_storage._M_data = end;
	}
};
template <class T> struct _Deque_iterator_base
{
	__declspec(noinline) void _M_increment()
	{
		if (++_M_cur == _M_last)
		{
			_M_set_node(_M_node + 1);
			_M_cur = _M_first;
		}
	}
	void _M_set_node(T **node)
	{
		_M_last = (_M_first = *(_M_node = node)) + int(_S_buffer_size());
	}
	static unsigned _S_buffer_size() { return sizeof(T) < 128 ? 128 / sizeof(T) : 1; }
	int _M_subtract(const _Deque_iterator_base &other) const;
	T *_M_cur;
	T *_M_first;
	T *_M_last;
	T **_M_node;
};
template <class T, class Tr> struct _Deque_iterator : _Deque_iterator_base<T>
{
	T &operator*() const { return *this->_M_cur; }
	T &operator[](int n) const;
	_Deque_iterator &operator++() { this->_M_increment(); return *this; }
	bool operator!=(const _Deque_iterator &other) const { return this->_M_cur != other._M_cur; }
};
template <class T, class A = allocator<T> > class deque
{
public:
	typedef _Deque_iterator<T, _Nonconst_traits<T> > iterator;
	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
	T &front() { return *_M_start; }
	T &operator[](int n) { return _M_start[n]; }
	int size() const { return _M_finish._M_subtract(_M_start); }
	__declspec(noinline) void push_back(const T &t)
	{
		if (_M_finish._M_cur != _M_finish._M_last - 1)
		{
			_Construct(_M_finish._M_cur, t);
			++_M_finish._M_cur;
		}
		else
			_M_push_back_aux_v(t);
	}
	iterator _M_start;
	iterator _M_finish;
	T **_M_map;
	_STLP_alloc_proxy<unsigned, T, A> _M_map_size;
protected:
	// Called only if _M_finish._M_cur == _M_finish._M_last - 1.
	__declspec(noinline) void _M_push_back_aux_v(const T &t)
	{
		T copy = t;
		_M_reserve_map_at_back();
		*(_M_finish._M_node + 1) = _M_map_size.allocate(_Deque_iterator_base<T>::_S_buffer_size());
		_Construct(_M_finish._M_cur, copy);
		_M_finish._M_set_node(_M_finish._M_node + 1);
		_M_finish._M_cur = _M_finish._M_first;
	}
	void _M_reserve_map_at_back(unsigned nodesToAdd = 1);
};
}

// Rows and cells are 40-byte deques; the rowed iterator helpers spell their
// elements with the neutral BfmeOpaque40.
struct BfmeOpaque40 : _STL::deque<BfmeOpaque40>
{
};
typedef _STL::deque<BfmeWordValue4> CellKeys;
namespace _STL {
template <> class deque<deque<CellKeys> > : public deque<BfmeOpaque40>
{
public:
	~deque();
};
}

class Rva00425806
{
public:
	Rva00425806();
	int m_key;
	int m_04;
	_STL::deque<_STL::deque<CellKeys> > m_rows;
};

class Rva00421CE9 : public _STL::set<Rva001408C0Target *>
{
public:
	~Rva00421CE9();
};

typedef _STL::vector<const ModuleData *> UnitList;
struct LightSubPoint
{
	LightSubPoint(unsigned columns);
	~LightSubPoint();
	_STL::vector<UnitList> m_cells;
	UnitList m_units;
};
class LightPoint
{
public:
	LightPoint(int key, unsigned rows, unsigned columns);
	_STL::vector<LightSubPoint> m_points;
	int m_key;
};

LightPoint::LightPoint(int key, unsigned rows, unsigned columns) : m_points(rows, LightSubPoint(columns))
{
	m_key = key;
}

typedef _STL::map<int, int> IntMap;
typedef _STL::_Rb_tree_node<_STL::pair<const int, int> > IntMapNode;
extern unsigned int g_Va00E03168;
extern unsigned int g_Va00E03174;
extern unsigned int g_Va00E0319C[3];
#define unitTypes (*reinterpret_cast<IntMap *>(&g_Va00E03168))
#define formationTemplates (*reinterpret_cast<_STL::deque<void *> *>(&g_Va00E03174))
#define formationIndices (*reinterpret_cast<IntMap *>(g_Va00E0319C))

void rva00425842(INI *ini, void *, void *, const void *)
{
	Rva00425806 data;
	AsciiString name = ini->getNextQuotedAsciiString();
	if (name.isEmpty())
		throw INIException(3, "Formation Template must have name at %s:%d", ini->getFilename().str(), ini->getLineNum());
	data.m_key = TheNameKeyGenerator->nameToKey(name);
	if (formationIndices._M_t._M_find(data.m_key) != formationIndices._M_t._M_header)
		throw INIException(3, "Formation Template name must be unique %s:%d", ini->getFilename().str(), ini->getLineNum());
	FieldParse fields[] = {
		{ "Rows", (Parser)Rva00425421Parse, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(&data, fields);
	int rows = data.m_rows.size();
	int columns = data.m_rows.front().size();
	LightPoint *formation = new LightPoint(data.m_key, rows, columns);
	Rva00421CE9 seen;
	_STL::vector<LightSubPoint> &points = formation->m_points;
	for (int row = rows - 1; row >= 0; --row)
	{
		for (int column = 0; column < columns; ++column)
		{
			CellKeys &cell = reinterpret_cast<CellKeys &>(data.m_rows[row][column]);
			for (CellKeys::iterator it = cell.begin(); it != cell.end(); ++it)
			{
				const int &key = (*it).m_key;
				IntMapNode *unit = unitTypes._M_t._M_find(key);
				if (unit == unitTypes._M_t._M_header)
					throw INIException(3, "Invalid unit type '%s' at %s:%d",
						TheNameKeyGenerator->keyToName((NameKeyType)key).str(),
						ini->getFilename().str(), ini->getLineNum());
				UnitList *cells = points[row].m_cells.begin();
				int &value = unit->_M_value_field.second;
				cells[column].push_back(reinterpret_cast<const ModuleData *>(&value));
				if (seen._M_t._M_find(reinterpret_cast<Rva001408C0Target *const &>(value)) == seen._M_t._M_header)
				{
					seen.insert(reinterpret_cast<Rva001408C0Target *const &>(value));
					points[row].m_units.push_back(reinterpret_cast<const ModuleData *>(value));
				}
			}
		}
	}
	formationTemplates.push_back(reinterpret_cast<void *&>(formation));
	formationIndices[data.m_key] = formationTemplates.size() - 1;
}
