# Volume-name tree consolidation and residual reference count

The prepared whole-donor move of approved `0x0005CE32` from `Rva0005CE32Method.cpp` stopped before compilation at `8828fdb47f9`. The donor owns one 65-byte code row and its object contributes one method definition. The staged destination text proposed moving its existing float declaration and use to the Miles device unit. No source was staged.

The current counter scans two occurrences of `g_Va00BBB8D8` in the original donor, one declaration and one read. The prepared destination retains those two occurrences. The carve's interim residual text also retains the declaration, adding a third occurrence to the guard's input. This declaration would disappear with the absorbed donor. The read-only call to `prepared_hatches` returned a refusal with the intermediate text and returned the original count of two for the planned final files.

A verifier regression needs to distinguish a complete donor deletion from any transition that still owns code, data, or other residual obligations. After that distinction is proved, rerun the guarded transfer. Its remaining checks include the original 65 bytes and both relocations, the selected typed erase provider, and the 48-byte fill of `0x02` at `+0x188`.
