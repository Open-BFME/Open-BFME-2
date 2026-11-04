# W3DTornadoDraw mechanical merge blocker (2026-11-04)

Allocated and checked `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTornadoDraw.cpp`.
The unchanged merge dry run accepted no donors: `W3DTornadoDraw_xfer.cpp`
fails because `xfer` is not a member of `W3DTornadoDraw`; `W3DTornadoDrawModuleDataDtor.cpp`
fails byte verification. LinkGuard could evaluate the three census-linked
units. Reconcile the class views and bytes in another lane before retrying.
