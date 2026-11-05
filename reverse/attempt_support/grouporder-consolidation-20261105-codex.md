# GroupOrder consolidation dry-run handoff

The allocated `GroupOrder.cpp` passed its TU allocation check; the scoped
GameLogic/AI consolidation report passed its freshness check. The plan has 12
approved rows and two donors, with no mixed or refused files. The guarded dry
run accepted no donors. `GroupOrderHolderCtor.cpp` fails combined-TU
compilation with C2995 because `_STL::_Vector_base<...>::~_Vector_base` is
already defined. LinkGuard lists both census-linked objects, and the tool
requires reconciliation of the donor's private `GroupOrder` view before a
retry. No source, ledger or claim changes were made; this repair belongs to
another lane.
