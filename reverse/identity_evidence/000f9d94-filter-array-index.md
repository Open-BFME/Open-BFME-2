# Smoke-glow filter array index

The full gate at BFME 2 `a6aa6319ee`, with committed BFME 1 inputs
`874e38488c7dcf8cf3343452e8e5371bb3a0e64c`, byte-verified all 72,625 rows
but refused DIR32 consistency for `W3DFilters`: its two external views imply
different array bases, `0x00DE1F2C` and `0x00DE1F30`.

Independent retail evidence establishes the former base:

* `W3DShaderManager::shutdown`, RVA `0x0007684A`, loads `ESI = 0x00DE1F2C`
  at VA `0x004768D7`. Its filter traversal advances four bytes and compares
  against `0x00DE1F54` at `0x004768EA`: ten pointer entries.
* `ScreenBWFilter::init`, RVA `0x000FB9D4`, registers at `0x00DE1F30`.
  Its source's index one agrees with the independently established base.
* The smoke-glow initializer, RVA `0x000F9D94`, stores `ESI` to
  `0x00DE1F40` at VA `0x004F9F6C`. This is entry **five** of that array:
  `(0x00DE1F40 - 0x00DE1F2C) / 4 = 5`.

`ScreenFilterRva007DCA80Init.cpp` currently declares five entries and writes
`W3DFilters[4]`. Its row still reproduces the whole 494-byte native body
because DIR32 resolution patches the operand, but its relocation addend
implies the wrong shared base. Its declaration should cover the witnessed
ten entries and its registration should use index five. The source comment
and ledger note also need to reflect that corrected index.

This is a source data-identity repair, not a verifier false rejection. Keep
the gate and its whitelist unchanged. Verify the whole initializer and both
array consumers together, then rerun full DIR32 consistency and the full gate.

The implicated source was held by `codex-6bc6-20261008` when inspected on
2026-10-09. Its file was left untouched and the overlapping body claim was
released. The incoming source's independent offset facts above establish
the failure; the BFME 1 freshness stamp was not advanced after the red gate.
