// cl: /O1 /Oy- /EHsc /MD
// stlport
// ?rva00150959@Rva00150959@@QAEXPAURva001504A1Record@@IABVRva0014F699@@@Z @0x00150959 258B
// vector fill-insert 76B elements with EH and x_copy dtor via rowed callees.
// Evidence: unlock lane idiv strides tag at ebp+0xb callers 0x00150BD7/0x00150A86.
#include <vector>

struct Rva001504A1Record
{
	char bytes[76];
};
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &other);
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

extern const void *const g_00BC6F24[];

class Snapshot
{
public:
  virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = (const void *)g_00BC6F24;
}

class __declspec(novtable) Rva0014F699 : public Snapshot
{
public:
	Rva0014F699(const Rva0014F699 &other);
	virtual ~Rva0014F699();
	Rva0014F699 &operator=(const Rva0014F699 &other);
private:
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	RefCountPtr<TextureClass> m_48;
};
void __cdecl Rva0014FA0DCopyBackward(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result);
typedef void (__cdecl *CopyBackward4Fn)(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result, const _STL::__false_type &tag);
void __cdecl Rva0014FA2AFill(Rva0014F699 *first, Rva0014F699 *last, const Rva0014F699 &value);
void *__cdecl rva0014FA47(void *first, unsigned int n, void *value);

class Rva00150959 : public _STL::vector<Rva001504A1Record>
{
public:
	void rva00150959(Rva001504A1Record *pos, unsigned int n, const Rva0014F699 &x);
};

void Rva00150959::rva00150959(Rva001504A1Record *pos, unsigned int n, const Rva0014F699 &x)
{
	if (n == 0)
		return;
	if ((unsigned int)(_M_end_of_storage._M_data - _M_finish) >= n) {
		Rva0014F699 x_copy(x);
		unsigned int elems_after = (unsigned int)(_M_finish - pos);
		Rva001504A1Record *old_finish = _M_finish;
		if (elems_after > n) {
			_STL::__uninitialized_copy(old_finish - n, old_finish, old_finish, *(const _STL::__false_type *)((char *)&pos + 3));
			_M_finish += n;
			Rva001504A1Record *p = pos;
			((CopyBackward4Fn)Rva0014FA0DCopyBackward)((Rva0014F699 *)p, (Rva0014F699 *)(old_finish - n), (Rva0014F699 *)old_finish, *(const _STL::__false_type *)((char *)&pos + 3));
			Rva0014FA2AFill((Rva0014F699 *)p, (Rva0014F699 *)(p + n), x_copy);
		} else {
			rva0014FA47(old_finish, n - elems_after, (void *)&x_copy);
			_M_finish += n - elems_after;
			_STL::__uninitialized_copy(pos, old_finish, _M_finish, *(const _STL::__false_type *)((char *)&pos + 3));
			_M_finish += elems_after;
			Rva0014FA2AFill((Rva0014F699 *)pos, (Rva0014F699 *)old_finish, x_copy);
		}
	} else {
		_M_insert_overflow(pos, (const Rva001504A1Record &)x, *(const _STL::__false_type *)((char *)&pos + 3), n, false);
	}
}
