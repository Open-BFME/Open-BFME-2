# Castle-member Module/data view, 2026-10-30

`Rva00395C80Check.cpp` now includes canonical Module.h. The old view called
the pointer at +4 `m_next` and described the second flag as another Module.
Canonical Module identifies that field as `const ModuleData *m_moduleData`.
Native 395CC9 tests module byte +25, 395CCF loads +4, and 395CD2 tests the
result's byte +19. The CastleMemberBehavior literal establishes the lookup
key; it does not establish an original derived-class or function identity.

The corrected source uses a partial Module-derived view for +25, exposes
the inherited data pointer without emitting a getter, and casts it to a
separate const data view for +19. The unconditional data dereference and
the original static-key/EH flow are preserved. No shared-header, ledger,
symbol, data ownership, hatch, pin, source-path or build-flag change is needed.

Private original/corrected probes match all three rows (107-byte parent,
13-byte guard rollback, 10-byte handler) and the parent's EH graph. Both
external emitted functions and their symbolic relocations are unchanged.
`proof.json` records those probes, native access instructions and the
actual strict-current object comparison. The compiler renumbers the guard
rollback from $L341 to $L445; verified parent EH data places it at the same
780DB7 address, so no ledger/pin spelling is edited.

Retire only this file's Module header key through `header_adopt_lane.py
accept`; no manual register deletion. The normal lane may normalize other
queue rows' ordering; those rows are not retirements. The bounded current
link preview conserves 106 linked bytes; this is header debt
retirement, not a claimed census gain. The broader audit remains qualified
by the old published index and missing affected-consumer receipts.

The previous header-only swap failed C2039 because it lost both private
flag declarations. This change supplies the separately evidenced storage
views; the prior failed attempt is retained in re_attempts.log.
