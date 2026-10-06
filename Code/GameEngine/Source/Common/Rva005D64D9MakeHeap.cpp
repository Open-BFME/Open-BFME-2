// cl: /MD
//
// ?Rva005D64D9MakeHeap@@YAXPAVRva005D5A7E@@0H@Z retail 0x005D64D9 128 bytes.
// make_heap for 12B Rva005D5A7E via rowed AdjustHeap 0x005D5E8A. Evidence:
// caller 0x005D6697, count via idiv 0xC, parent via sar, movsd x3 copies.

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

void Rva005D5E8AAdjustHeap(Rva005D5A7E *first, int hole, int len, Rva005D5A7E val, int comp);

void Rva005D64D9MakeHeap(Rva005D5A7E *first, Rva005D5A7E *last, int comp)
{
	int n = last - first;
	if (n < 2)
		return;
	int parent = (n - 2) / 2;
	Rva005D5A7E val = *(first + parent);
	Rva005D5E8AAdjustHeap(first, parent, n, val, comp);
	if (parent == 0)
		return;
	do
	{
		--parent;
		val = *(first + parent);
		Rva005D5E8AAdjustHeap(first, parent, n, val, comp);
	} while (parent != 0);
}
