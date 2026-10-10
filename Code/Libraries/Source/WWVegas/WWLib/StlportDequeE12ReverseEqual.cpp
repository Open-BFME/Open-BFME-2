// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX-
// stlport
// STLport4.5.3 reverse_iterator equality. Native00584D14..00584D3F
// copies both16B base iterators and compares their current pointers.
// Formation update005863E5 calls this at0058678D and005867B8 after
// copying the start iterator from its84B record's deque+28.
// WB1473460 independently shows reverse traversal with that comparison.
// BfmeE12 records the observed12B element stride; its semantic identity
// remains unknown. Actual STLport implementation; whole43B verified.
#include <deque>
struct BfmeE12 { float x,y,z; };
namespace _STL {
template bool operator==<deque<BfmeE12>::iterator>(
 const reverse_iterator<deque<BfmeE12>::iterator> &,
 const reverse_iterator<deque<BfmeE12>::iterator> &);
}
