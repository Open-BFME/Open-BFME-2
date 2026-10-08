// Target containment list ABI: 36ADF9 copies eight-byte elements, and
// 36AE51 returns a one-word STLport list from an eight-byte descriptor.
// The original element identity and second word remain unresolved. The
// existing copier's double[1] is opaque storage, not floating-point evidence.
#ifndef BFME_CONTAINMENT_LIST_VIEW_H
#define BFME_CONTAINMENT_LIST_VIEW_H
#include <list>
struct Rva0036ADF9Element {
    // MSVC 7.1's union representation preserves the observed first-dword
    // loads while the STLport copier retains the existing eight-byte shape.
    union { double words[1]; int rawWords[2]; };
    bool operator<(const Rva0036ADF9Element &) const;
    bool operator==(const Rva0036ADF9Element &) const;
};
typedef _STL::list<Rva0036ADF9Element> ContainmentList;
// Consumers read the first dword as an object pointer or identifier. Preserve
// its bits without treating the opaque element as a different C++ object type.
inline const int &containmentFirstWord(const Rva0036ADF9Element &element)
{
    return element.rawWords[0];
}
class Rva0036AE51ListView {
public:
    void *a;
    ContainmentList *b;
    ContainmentList rva0036AE51();
};
#endif
