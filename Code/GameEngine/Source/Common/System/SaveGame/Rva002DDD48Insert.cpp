// cl: /Oy-
//
// ?rva002DDD48@Rva002DDD48@@QAEXPAVSaveMapPreview@@ABV2@ABU__false_type@_STL@@I_N@Z
// retail 0x002DDD48, 186 bytes.
// Masked-identical to landed 0x0039C1C3 / 0x004EE6D0 insert paths (0x14 stride).
// Helpers rowed: allocate 0x00395960, uninit-copy 0x002DBEFF, copy-ctor
// 0x002262E7, fill_n 0x002DBF28, tidy 0x00565A42.

struct BfmeStringRecord002CF4C6;
namespace _STL
{
struct __false_type
{
};
template <class T> class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &);
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &);
}

class Xfer;
class Rva002262E7SnapshotBase
{
public:
	virtual ~Rva002262E7SnapshotBase();
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
};
class SaveMapPreview : public Rva002262E7SnapshotBase
{
public:
	unsigned int word04;
	struct Words { unsigned int a, b, c; } words08;
	SaveMapPreview(const SaveMapPreview &o);
	virtual ~SaveMapPreview();
};

typedef char SaveMapPreviewSizeCheck[sizeof(SaveMapPreview) == 0x14 ? 1 : -1];

#pragma optimize("y", on)
inline void *__cdecl operator new(unsigned int, void *p) { return p; }
#pragma optimize("", on)

class Rva00565A42
{
public:
	void rva00565A42();
	SaveMapPreview *m_00;
	SaveMapPreview *m_04;
};

class Rva002DDD48
{
public:
	void rva002DDD48(SaveMapPreview *pos, const SaveMapPreview &x, const _STL::__false_type &, unsigned int n, bool at_end);
	void push_back(const SaveMapPreview &x);

private:
	SaveMapPreview *m_start;
	SaveMapPreview *m_finish;
	union
	{
		_STL::allocator<BfmeStringRecord002CF4C6> m_alloc;
		SaveMapPreview *m_end;
	};
};

void Rva002DDD48::rva002DDD48(SaveMapPreview *pos, const SaveMapPreview &x, const _STL::__false_type &, unsigned int n, bool at_end)
{
	unsigned int old_size = (unsigned int)(m_finish - m_start);
	const unsigned int &maxv = old_size < n ? n : old_size;
	unsigned int len = old_size + maxv;
	SaveMapPreview *new_start = (SaveMapPreview *)m_alloc.allocate(len, 0);
	SaveMapPreview *new_finish = _STL::__uninitialized_copy<const SaveMapPreview *, SaveMapPreview *>((const SaveMapPreview *)m_start, (const SaveMapPreview *)pos, new_start, *(const _STL::__false_type *)((char *)&at_end + 3));
	if (n == 1)
	{
		if (new_finish != 0)
			new (new_finish) SaveMapPreview(x);
		++new_finish;
	}
	else
	{
		new_finish = _STL::__uninitialized_fill_n<SaveMapPreview *, unsigned int, SaveMapPreview>(new_finish, n, x, *(const _STL::__false_type *)((char *)&at_end + 3));
	}
	if (!at_end)
	{
		new_finish = _STL::__uninitialized_copy<const SaveMapPreview *, SaveMapPreview *>((const SaveMapPreview *)pos, (const SaveMapPreview *)m_finish, new_finish, *(const _STL::__false_type *)((char *)&at_end + 3));
	}
	((Rva00565A42 *)this)->rva00565A42();
	SaveMapPreview *new_end = new_start + len;
	m_start = new_start;
	m_finish = new_finish;
	m_end = new_end;
}

// Retail 0x002DDE6E, 56 bytes: STLport push_back. Placement copy at the
// finish when capacity remains, otherwise the 0x002DDD48 overflow insert of
// one element at the end. Its only caller is the save-game info xfer
// 0x002DDEC0 (SaveGameInfoCopyBFME2.cpp), which fills the +0x38 preview range.
void Rva002DDD48::push_back(const SaveMapPreview &x)
{
	if (m_finish != m_end)
	{
		new (m_finish) SaveMapPreview(x);
		++m_finish;
	}
	else
		rva002DDD48(m_finish, x, _STL::__false_type(), 1, true);
}
