// cl: /DNDEBUG /MD /EHs
//
// CrateSystem's lifetime and reset, Zero Hour CrateSystem.cpp bodies:
//   ??0CrateSystem@@QAE@XZ       retail 0x0035CAD6  49B
//   ?reset@CrateSystem@@UAEXXZ   retail 0x0035C9CF  51B (vtable slot 9)
//   ??1CrateSystem@@UAE@XZ       retail 0x0035CB07 134B
//   ??_GCrateSystem@@UAEPAXI@Z   retail 0x0035CBE2  28B (vtable slot 0)
// Identity (target evidence): the class with vtable 0x00C1635C keeps a
// pointer vector at +0x0C that CrateSystem::newCrateTemplate 0x0035CF2C
// appends to and friend_findCrateTemplate 0x0035CA2F searches; its slot 9
// (0x0035C9CF) walks that vector calling Overridable::deleteOverrides
// 0x001E35ED and erasing what it returns NULL for (Zero Hour's reset), and
// its dtor global-deletes each template (vtable slot 0 with flag 0, then
// ::operator delete 0x0002FD60, as deleteOverrides does) before clearing.
// The base is SubsystemInterface (ctor 0x001B4E63, dtor 0x001B4E74). These
// rows were held as the address-named Rva0035CAD6 (see deleted_rows.csv).
//
// Shape notes: the STLport vector is a declared view (same decorated names)
// whose shared bodies are pinned: _Vector_base(const allocator &) 0x00211E58,
// erase(first, last) 0x0031BD55, erase(position) 0x001FF51F. Both are
// nothrow in STLport (cl sees their bodies there), so they are declared
// throw() here, which keeps the ctor free of an EH frame as in retail.
// /EHs rather than /EHsc: retail's dtor keeps the EH state store before the
// vector storage is freed, which cl drops when it assumes extern "C" free
// cannot throw.

extern "C" void __cdecl free(void *);

class SubsystemInterface
{
public:
	SubsystemInterface();			// 0x001B4E63
	virtual ~SubsystemInterface();		// 0x001B4E74, slot 0 (deleting)
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void reset() = 0;		// slot 9

private:
	int m_04;
	int m_08;
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *deleteOverrides();		// 0x001E35ED

private:
	Overridable *m_nextOverride;
	bool m_isOverride;
};

class CrateTemplate : public Overridable
{
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

struct __true_type {};
template <class T> inline void __destroy_aux(T *, T *, const __true_type &) {}
template <class T> inline void _Destroy(T *first, T *last) { __destroy_aux(first, last, __true_type()); }

template <class T, class Alloc>
class _Vector_base
{
public:
	_Vector_base(const Alloc &a) throw();	// 0x00211E58, folded
	~_Vector_base()
	{
		if (_M_start)
			free(_M_start);
	}

protected:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};

template <class T, class Alloc = allocator<T> >
class vector : public _Vector_base<T, Alloc>
{
public:
	typedef T *iterator;

	explicit vector(const Alloc &a = Alloc()) : _Vector_base<T, Alloc>(a) {}
	~vector() { _Destroy(this->_M_start, this->_M_finish); }

	iterator begin() { return this->_M_start; }
	iterator end() { return this->_M_finish; }
	unsigned int size() const { return this->_M_finish - this->_M_start; }
	T &operator[](unsigned int n) { return *(begin() + n); }

	iterator erase(iterator position);		// 0x001FF51F, folded
	iterator erase(iterator first, iterator last) throw();	// 0x0031BD55, folded
	void clear() { erase(begin(), end()); }
};
}

class CrateSystem : public SubsystemInterface
{
public:
	CrateSystem();
	virtual ~CrateSystem();
	virtual void reset();

private:
	_STL::vector<CrateTemplate *> m_crateTemplateVector;	// +0x0C
};

void CrateSystem::reset()
{
	// clean up overrides
	_STL::vector<CrateTemplate *>::iterator it;
	for (it = m_crateTemplateVector.begin(); it != m_crateTemplateVector.end(); )
	{
		CrateTemplate *ct = *it;
		if (ct)
		{
			Overridable *stillValid = ct->deleteOverrides();
			if (stillValid == 0)
			{
				// Also needs to be erased
				it = m_crateTemplateVector.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
		{
			it = m_crateTemplateVector.erase(it);
		}
	}
}

CrateSystem::CrateSystem()
{
	m_crateTemplateVector.clear();
}

CrateSystem::~CrateSystem()
{
	int count = m_crateTemplateVector.size();
	for (int i = 0; i < count; i++)
	{
		CrateTemplate *crateTemplate = m_crateTemplateVector[i];
		if (crateTemplate)
		{
			::delete crateTemplate;
		}
	}
	m_crateTemplateVector.clear();
}
