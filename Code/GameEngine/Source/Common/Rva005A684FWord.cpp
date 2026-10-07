// cl: /O1 /MD
// Native 0x005A684F..0x005A6869: one stack index, ECX receiver, RET4.
// The pointer table begins at +0x90C; the related native 0x005A6A4C loop
// consumes eight slots. This method returns the unsigned word at pointee+4,
// or zero for a null slot. Class identities and full table/object extents
// are unresolved; the eight-slot prefix and scalar types are storage views.
struct Rva005A684FWord { unsigned int m_00; unsigned short m_04; };
class Rva005A684F
{
public:
 unsigned int get(unsigned int index) const;
private:
 char m_00[0x90C];
 Rva005A684FWord *m_slots[8];
};
unsigned int Rva005A684F::get(unsigned int index) const
{
 return m_slots[index] ? m_slots[index]->m_04 : 0;
}
