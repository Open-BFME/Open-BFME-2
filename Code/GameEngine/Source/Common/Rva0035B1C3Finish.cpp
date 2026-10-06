// ?rva0035B1C3@Rva0035B1C3@@QAEHH@Z
// cl: /MD
//
// ?rva0035B1C3@Rva0035B1C3@@QAEHH@Z @0x0035B1C3 38B
// Bounds-checked int list getter over vector<int> at +0xec: negative or
// past-end index returns 0 else m_begin[index].
// Evidence: ecx-first thiscall ret 4; sar-2 count shape like twin
// Rva0035B232Getter; caller 0x005679C9; prev/next donor TUs in Common.
//
// The count is a SIGNED (sar) shift of the char* end-begin difference, and
// the good path is the fall-through so the bounds branch targets the zero tail.
struct Rva0035B1C3Vec {
    int *begin; int *end; int *cap;
    int size() const { return (int)((char *)end - (char *)begin) >> 2; }
    int &at(int i) { return begin[i]; }
};
class Rva0035B1C3 { char m_pad[0xec]; Rva0035B1C3Vec m_vec; public: int rva0035B1C3(int index); };
int Rva0035B1C3::rva0035B1C3(int index)
{
    if (index < 0) return 0;
    if ((unsigned int)index < (unsigned int)m_vec.size())
        return m_vec.at(index);
    return 0;
}