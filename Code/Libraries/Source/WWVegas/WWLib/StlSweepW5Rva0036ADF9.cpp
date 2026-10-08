// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

#include "../../../../GameEngine/Include/GameLogic/ContainmentListView.h"
template class _STL::list<Rva0036ADF9Element>;

// Retail 36AE51 (40B): clear the descriptor's first word before copying
// its source, otherwise copy the existing empty-list sentinel at E0362C.
// 36ADF9's complete copier establishes the element width independently.
extern unsigned g_Va00E0362C;
ContainmentList Rva0036AE51ListView::rva0036AE51()
{
    if (a) {
        a = 0;
        return ContainmentList(*b);
    }
    return ContainmentList(*reinterpret_cast<const ContainmentList *>(&g_Va00E0362C));
}
