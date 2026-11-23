# Miles volume methods and canonical data bindings

The prepared move of `MilesAudioManagerRva0005CA03.cpp` into the device unit at `4169acf49c6` matched both approved rows. The 114 bytes and all relocations of `0x0005CA03` agreed with the donor. The 109 bytes of `0x0005CA75` also agreed. Its only relocation differences were `__real@bf800000` for the old float symbol at +62 and `AsciiString::TheEmptyString` for the old empty-string alias at +71. The original donor's two EH graphs verified exactly with a fresh 2/2 receipt.

The retail `0x0005CA75` loads `-1.0f` by value at VA `0x00BBB9AC`. The already-matched `0x0005E377` calls the same method with that literal and retail operand. The published `8ac58f86ea5` image stores identical `00 00 80 BF` bytes at both linked float locations. Its map puts the two empty-string names at the same zero-filled VA `0x02BF1D1C`. [Real-link run 45271811271](https://github.com/Open-BFME/Open-BFME-2/actions/runs/45271811271)

The prepared split refused `0x0005CA75` under the provider definition-bytes check because the data relocation symbols differ. The refused transaction returned with the donor intact. Any change to the check needs current relocation evidence for the canonical referents and a regression covering unequal or unresolved data.


The subsequent transfer carried the donor's registered data references with the same totals. Its normal build verified 463 functions and 89 exact EH graphs. Both moved bodies and all 16 relocations agreed with the donor. The canonical rebinding remains subject to the provider check.
