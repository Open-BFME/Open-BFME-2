// cl: /MD
// ?rva005D5A7E@Rva005D5A7E@@QBE_NABV1@@Z @0x005D5A7E 53B.
// Ordering by int at +4 then AsciiString NoCase at inner+4.
// Evidence: 13 callers (0x005D5B09 0x005D5B3C 0x005D5BC9 0x005D5C6F etc.)
// unblock 7 (3 ready); callee StringBase<char>::compareNoCase rowed at 0x6A00;
// 12B stride (imul 0xC movsd x3) in callers 0x005D5B21 0x005D5BA3 0x005D5C61.

template <typename T>
class StringBase
{
public:
    int compareNoCase(const StringBase &other) const;
private:
    void *m_data;
};

struct Rva005D5A7EInner
{
    int m00;
    StringBase<char> m_str;
    int m08;
    int m0C;
    int m10;
};

class Rva005D5A7E
{
public:
    bool rva005D5A7E(const Rva005D5A7E &other) const;
private:
    Rva005D5A7EInner *m_ptr;
    int m_val;
    int m_pad;
};

bool Rva005D5A7E::rva005D5A7E(const Rva005D5A7E &other) const
{
    if (m_val == other.m_val)
        return m_ptr->m_str.compareNoCase(other.m_ptr->m_str) < 0;
    return m_val > other.m_val;
}

void Rva005D5B21Insert(Rva005D5A7E *last, Rva005D5A7E val, int dummy)
{
    (void)dummy;
    Rva005D5A7E *next = last;
    --next;
    while (val.rva005D5A7E(*next)) {
        *last = *next;
        last = next;
        --next;
    }
    *last = val;
}

void Rva005D5DF0Sort(Rva005D5A7E *first, Rva005D5A7E *last, Rva005D5A7E *tag, int comp)
{
    (void)tag;
    for (Rva005D5A7E *it = first; it != last; ++it)
        Rva005D5B21Insert(it, *it, comp);
}

Rva005D5A7E *Rva005D5C61Median(Rva005D5A7E *a, Rva005D5A7E *b, Rva005D5A7E *c, int comp)
{
    (void)comp;
    if (a->rva005D5A7E(*b)) {
        if (b->rva005D5A7E(*c))
            return b;
        else if (a->rva005D5A7E(*c))
            return c;
        else
            return a;
    } else {
        if (a->rva005D5A7E(*c))
            return a;
        else if (b->rva005D5A7E(*c))
            return c;
        else
            return b;
    }
}

struct BfmeE12 { float x, y, z; };
namespace _STL {
template <class _Tp> void swap(_Tp &a, _Tp &b);
template <class _InputIter, class _OutputIter>
_OutputIter copy_backward(_InputIter first, _InputIter last, _OutputIter result);
}

Rva005D5A7E *Rva005D5CBFPartition(Rva005D5A7E *first, Rva005D5A7E *last, Rva005D5A7E pivot)
{
	while (true) {
		while (first->rva005D5A7E(pivot))
			++first;
		--last;
		while (pivot.rva005D5A7E(*last))
			--last;
		if (first >= last)
			return first;
		_STL::swap(*(BfmeE12 *)first, *(BfmeE12 *)last);
		++first;
	}
}

// ?Rva005D5DA5Guarded@@YAXPAVRva005D5A7E@@0V1@H@Z @0x005D5DA5 75B.
// Guarded linear insert: if val precedes *first shift via copy_backward else unguarded insert.
// Evidence: callees rowed 0x005D5A7E 0x0051C94D 0x005D5B21; caller 0x005D63FA; neighbours share /O1 /MD.
void Rva005D5DA5Guarded(Rva005D5A7E *first, Rva005D5A7E *last, Rva005D5A7E val, int comp)
{
	if (val.rva005D5A7E(*first)) {
		_STL::copy_backward((BfmeE12 *)first, (BfmeE12 *)last, (BfmeE12 *)(last + 1));
		*first = val;
	} else {
		Rva005D5B21Insert(last, val, comp);
	}
}
