### Apt character setter unused CRT declarations (2026-10-29, codexb4)

Removed unused local `atoi` and `strtol` prototypes from
`AptCharacterSetMember.cpp`; neither function is called in the TU. The scoped
owning scanner retires its Microsoft-header queue row. All five rows verify,
including three naturally renumbered funclets; all 25 COMDAT digests/sizes,
72 external symbol records and 68 external relocation target names remain
unchanged. Strict current preparation passes and ordinary preview preserves
LINKS, 3,735 -> 3,735 authored bytes against index `840db2d676`.

The outgoing audit is INCONCLUSIVE: the index predates the base and affected
consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry
this provider and consumer into the next scheduled census. No measured linking
or ownership gain is claimed. [Evidence and reference-update boundary](../../reverse/attempt_support/apt-character-crt-cleanup-20261029-codexb4.md).
