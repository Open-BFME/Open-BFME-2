# Retire the unsupported 0x001DE3E3 sweep

Base: `bd37f44974`. The 31-byte range remains owned by
`Common/Rva001DE3E3Guard.cpp`; its bytes and both native callees are unchanged.
The deleted `StlSweepR3Rva001DE3E3.cpp` claimed the same assignment using a
one-byte record explicitly described as donor inference. That record cannot
establish the actual name-map element: the native allocation/placement-copy
chain uses a twelve-byte node containing an eight-byte value.

The sweep emitted unresolved `Rva001DE3E3Record` copy-constructor/destructor
references and incorrect clear/copy workers. This is an existing duplicate
claim, not lost matching coverage. No original application type is recovered.

The orphan scan found one consumer of the assignment, `Eva.cpp`. Its native
reset calls the same address with receiver `this+0x34` and source `this+0x48`.
It now calls the existing `Rva001DE3E3::rva001DE3E3` spelling directly. The
unsupported record, container typedef and size assertion are removed from
that consumer. All of Eva's rows remain exact, including the reset and EH.

The current-object/census definition audit identified fifteen sweep-specific
definitions. Only the assignment had an outside touch (Eva). None of the
other fourteen definitions has an outside census touch; a source/shim scan
finds no remaining use of the record. The two shared placement-new/delete
definitions retain earlier providers. Both private clear/copy pins are
removed; the surviving assignment uses the actual existing providers, so no
pin or alias replaces them.

Verification:

- Normal build: 29/29 rows in Eva, the surviving assignment, and the copy
  worker `StlSweepR3Rva001DDCC5.cpp`; literal/float/import checks pass.
- Frozen-file checks are clean for Eva and the surviving assignment.
- True current-object base/tip link_check uses the same `a62ac1c10b` index
  and a 50-source cohort, including Team, Eva, the copy worker and every
  first-copy COMDAT provider of those units. All 47 base LINKS units stay
  LINKS. Tip has 49 sources after removal; preview bytes stay 165,621.
  The other two retained units were already blocked at base.
- Scoped DIR32 passes 29 owned rows plus 24 witnesses.
- `check_csv.py` passes (99,439 rows, 9,334 pins); pin consistency passes.
- The full setup gate passed at the session's initial `efb5fcbb60`.

Path/debt audit: there is no active tool, hook, workflow, source/include,
flag, gate, data, code-identity, header-queue, data-owner or TU-map key for
the removed source. Historical census rows remain historical. The linking
checklist is updated. The retired row has a tombstone; `re_log.py` records
the retirement. `hatch_counters.py --update` retires the two pins; its
unrelated stale W3DVideoBuffer-marker removals were reverted. No rows move,
no TU map is regenerated, and no unique matched bytes disappear.

Local receipts: `build/seat_r3_{base,tip,build}.log`,
`build/seat_r3_cohort.{txt,json}`, `build/seat_r3_sole_providers.json`.
These are bounded previews, not a new census or a full real-link result.
