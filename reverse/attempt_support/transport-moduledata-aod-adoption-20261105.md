# TransportContainModuleData: AOD factory header adoption

Inspected source: `74edab4b7be2` plus this adoption, 2026-11-05.
Canonical header: `Code/GameEngine/Include/GameLogic/Module/TransportContainModuleData.h`.
Changed consumer: `Code/GameEngine/Source/GameLogic/Object/Contain/AODHordeContain.cpp`.

The private class contained declarations and padding only. Replacing it with
an include at its old location failed: Drawable had already selected Snapshot's
capitalized pure virtual slots, leaving the canonical module-data class abstract
(C2259; LoadPostProcess and DoXfer). Including module data before Drawable selects
the lowercase Snapshot profile and makes the existing factories compile. No shared
header, symbol, row identity, pin or alias was changed.

Verification:

- Control and adopted `./build.sh` runs pass. Adopted run verifies 30/30 function
  rows, one data row, two funclet pins and nine float references; string/import
  checks pass. `find_declared_unmatched.py` passes after the edit.
- The old and new objects each define the same 84 external symbols, with no lost
  or gained providers. Their 115 non-debug sections have identical runtime graphs
  (bytes, relocations, provider locations, weak bindings and COMDAT policies),
  except `.drectve` ordering: the directive multiset and default-library order
  are identical; only existing AsciiString alias directives moved in the stream.
  Thus the edit removes no link-wide provider or alias.
- `link_check.py` against index f44cbcf5b0 (2026-11-05 15:19) predicts LINKS for
  all four cohort units: AODHordeContain 2204 -> 2204 bytes,
  ContainModuleDeletingDtors 420 -> 392, TransportContain 2958 -> 2986,
  TransportContainModuleDataDtor 114 -> 114. Total 5696 -> 5696. The historical
  duplicate constructor/getter diagnostics are absent in this preview scope.
  The existing unreferenced Object::clearCondition diagnostic remains.
- One full-cohort `header_adopt_lane.py accept` retires AOD's queue row. The other
  three rows remain: TransportContain and the standalone destructor still need
  typed payload/container fields absent from the opaque canonical declaration;
  ContainModuleDeletingDtors already includes the header but acceptance predicts
  its historical 28-byte loss (the four-unit preview transfers those bytes to
  TransportContain). Recheck acceptance after a census refresh before retiring it.
- Staged-tree `link_batch_audit.py` exits 2, INCONCLUSIVE: the index predates the
  outgoing base and AOD lacks a current object receipt. This is not a passing
  batch-wide audit. The ordinary previews and exact before/after provider/runtime
  comparison above have narrower scope. The push hook will run its own audit.

No measured census gain, real-image link or game-runtime result is claimed.
Remaining work: recover the typed canonical container declarations, verify their
whole consumer cohort, and refresh census confirmation/provider receipts.
