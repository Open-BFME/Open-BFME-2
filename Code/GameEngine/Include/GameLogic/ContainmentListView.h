// Target containment list ABI: 36ADF9 copies a list through the four-byte
// element insertion chain BB975 -> 2C526D -> 5925E2 -> B6447, and
// 36AE51 returns a one-word STLport list from an eight-byte descriptor.
// The original element identity remains unresolved. The copier wrapper
// alone does not establish element width; the allocation/insertion chain does.
#ifndef BFME_CONTAINMENT_LIST_VIEW_H
#define BFME_CONTAINMENT_LIST_VIEW_H
#include <list>
struct Rva0036ADF9Element {
    int rawWords[1];
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
