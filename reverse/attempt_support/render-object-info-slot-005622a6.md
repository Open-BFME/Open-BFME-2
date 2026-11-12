# Render-object particle info transfer at 0x005622A6

In retail table 0x0081D358, slot 2 points to 0x003AE26A, a six-byte
getter returning the string RenderObjectParticleUpdateModuleInfo. Slot 3
points to 0x005622A6, which transfers twelve floats at +4 through +0x30
and the rotation enum at +0x34. The constructor at 0x0056224F installs
this table. The shared destructor address alone does not identify the class.

Tested a shared Rva0056224F declaration with a protected xfer(Xfer *)
override in the existing constructor and transfer units, and a qualified
base call in Rva0056234AXfer.cpp. The ordinary build matched all ten rows
across these three files. The rebuilt table contained the weak deleting
destructor, loadPostProcess, __purecall, and the new xfer symbol in order.
rename.py correctly rejected slot 2: retail calls the getter there.

A joint function --to-class plan for 0x005622A6 and 0x003AE26A refused
the latter's current free cdecl symbol, ?Rva003AE26AGet@@YAHXZ. This is
the P41 free-getter prerequisite. A future repair needs to prove the
getter identity and its calling convention through an admitted route,
then verify both slots and the direct 0x0056234A caller together.
The separate copy-constructor table name Rva005EA0D0 is still open.
