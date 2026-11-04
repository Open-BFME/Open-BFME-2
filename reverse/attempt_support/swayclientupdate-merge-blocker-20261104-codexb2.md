# SwayClientUpdate unchanged merge dry run (2026-11-04)

Allocated `Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdate.cpp`;
the 9-row plan has 2 donors. Dry run accepted none: the constructor donor fails
with C2511 because `SwayClientUpdate(Thing *, const ModuleData *)` is absent
from the destination class view. LinkGuard confirms both census units remain
linked. Reconcile the class view in another lane before retrying.
