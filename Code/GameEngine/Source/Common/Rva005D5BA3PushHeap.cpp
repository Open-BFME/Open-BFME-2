// cl: /MD
// ?Rva005D5BA3PushHeap@@YAXPAVRva005D5A7E@@HHV1@H@Z @0x005D5BA3 90B.
// __push_heap sift-up for 12B Rva005D5A7E via rva005D5A7E ordering.
// Evidence: caller 0x005D5F09 in 0x005D5E8A cleans 0x1C (28B = 4+4+4+12+4);
// callee rva005D5A7E rowed; imul 0xC needs /G7 (probe: /O1 alone gives lea 92B).

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

void Rva005D5BA3PushHeap(Rva005D5A7E *first, int hole, int top, Rva005D5A7E val, int comp)
{
    (void)comp;
    int parent = (hole - 1) / 2;
    while (hole > top && (first + parent)->rva005D5A7E(val)) {
        *(first + hole) = *(first + parent);
        hole = parent;
        parent = (hole - 1) / 2;
    }
    *(first + hole) = val;
}

void Rva005D5E8AAdjustHeap(Rva005D5A7E *first, int hole, int len, Rva005D5A7E val, int comp)
{
    int top = hole;
    int secondChild = hole + hole + 2;
    while (secondChild < len) {
        if ((first + secondChild)->rva005D5A7E(*(first + secondChild - 1)))
            --secondChild;
        *(first + hole) = *(first + secondChild);
        hole = secondChild;
        secondChild = hole + hole + 2;
    }
    if (secondChild == len) {
        *(first + hole) = *(first + (secondChild - 1));
        hole = secondChild - 1;
    }
    Rva005D5BA3PushHeap(first, hole, top, val, comp);
}
