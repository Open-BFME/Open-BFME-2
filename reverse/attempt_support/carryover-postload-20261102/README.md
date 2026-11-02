# Real Carryover post-load override

Native CarryoverUnit table VA BDF158 slot1 points to the shared empty RET
at B3FD0. Its real C++ loadPostProcess override now owns a verified one-byte
twin through add_match --icf-owner. The old linker alias is removed only
after the actual same-name definition exists. Region2D's original provider
and every other user remain unchanged; no pin or old row is removed.

The complete index has only this unit touching/emitting that alias and no
incoming alias route. Its only current runtime relocation is vtable +4.
All eleven rows, both EH graphs and strict checks pass, and prior complete
definitions remain unchanged. The source stays LINKS; the added one-byte
fold is not new unique/global coverage. The owning hatch tool retires one
alternatename. The unrelated transfer/getter aliases remain. Transfer
cleanup needs a refreshed ArmySummaryEntry consumer: its shared object is
stale against current source, so the index alone does not clear that work.
