// cl: /MD
// Five scalar deleting destructors sharing one 28B shape (dtor call, flags
// byte test, conditional scalar delete through pinned ??3@YAXPAX@Z
// 0x0002FD60, return this), same recipe as the landed 0x005E948B/0x005E3051/
// 0x005EB35D rows: each dtor is declared but not defined here and reached
// through an address-honest pin (all five retail sites call directly, so the
// dtors are non-virtual). Emitted via delete anchors; anchors never called.
// Honest address names; owners unproven.
//  0x0009A200 via dtor 0x001076E9
//  0x000FE9C7 via dtor 0x000FE290
//  0x001732C6 via dtor 0x0018C57C
//  0x001F097A via dtor 0x001F077D

class Rva0009A200 { public: ~Rva0009A200(); };
class Rva000FE9C7 { public: ~Rva000FE9C7(); };
#include "../../Include/Common/Rva001732C6.h"
class Rva001F097A { public: ~Rva001F097A(); };

#include <new>

void Rva0009A200_DeleteAnchor(Rva0009A200 *p) { delete p; }
void Rva000FE9C7_DeleteAnchor(Rva000FE9C7 *p) { delete p; }
void Rva001732C6_DeleteAnchor(Rva001732C6 *p) { delete p; }
void Rva001F097A_DeleteAnchor(Rva001F097A *p) { delete p; }

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x000FE290 reads ?bfmeResetSH@BfmeThingSH@@QAEXXZ
#pragma comment(linker, "/alternatename:??1Rva000FE9C7@@QAE@XZ=?bfmeResetSH@BfmeThingSH@@QAEXXZ")
//   0x001F077D reads ??1Rva001F077D@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva001F097A@@QAE@XZ=??1Rva001F077D@@QAE@XZ")
