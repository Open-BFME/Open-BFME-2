# Apt numeric-string predicate CRT header

Inspected base: `4c4e488578`. Claimed source:
`Code/Libraries/Source/Apt/Rva006FC370.cpp`.

The address-derived predicate retains its existing identity and grammar.
Replace its local `strtol` declaration with the toolchain's `stdlib.h`,
using the file's existing supported `_CRTIMP` configuration. Target evidence:
the call at RVA `0x006FC442`, inside the 762-byte row at `0x006FC370`,
targets the existing `_strtol` thunk at `0x00629ABA`. Its six bytes are
`FF 25 60 A7 BB 00`, an indirect jump through IAT `0x00BBA760`.
`Msvcr71ImportThunks.cpp` already owns that thunk and its import identity.
The other existing CRT calls still use the `isdigit` thunk at `0x00629982`.
No source or donor identity is inferred from these import facts.

Verification:

- Ordinary before/after builds pass the complete existing 762-byte extent.
  Frozen-file checks pass before and after; no row, pin or flag changes.
- EH verification is EXACT 1, including the string cleanup graph.
- All five non-debug object sections (864 bytes, 52 relocations) and all
  17 external symbol records are identical. Compiler-local EH labels are
  compared by section and offset: only their generated numbers change.
  Scratch snapshots and raw facts are under
  `build/apt-predicate-crt-20261030-codexb4/`.
- Strict explicit-provider preparation passes with a reusable receipt.
  Ordinary preview retains LINKS, 761 -> 761 authored bytes, against
  index `12b9e7a7c0` (2026-10-30 10:11).
- The owning Microsoft-header scan classifies the source as clean, with
  only the supported `_CRTIMP` configuration input. Its scoped
  `refresh_queue` removes exactly this source's one local-declaration
  finding; unrelated queue records remain intact. `verify-removed` passes.

The staged outgoing-batch audit (base `8e056464a0`, including the three
previously handed-over commits) exits 2, INCONCLUSIVE: the index predates
the base and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks
a current receipt. Full affected-consumer selection/loss verification and
census confirmation remain pending. Carry this predicate, the preceding
browser/shader, BuildAssistant and glyph providers, and their consumers
into the next scheduled census. The identical object comparison above
establishes this cleanup's preserved bindings independently of that preview.

This is header-debt cleanup; no census gain or image-ownership gain is claimed.
