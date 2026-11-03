# ArmyDetails static cleanup identity boundary

Inspected `bc8e2a3575`, 2026-11-03; source:
`Code/GameEngine/Source/Common/Rva005F2FEFApt.cpp`.

The picker served the registered wrong-target findings for compiler callbacks
at RVAs `0x007B99D3` and `0x007B99DD`. Native cleanup jumps to `0x0048BA39`,
whose current ledger owner is `??1?$StringBase@D@@AAE@XZ`. The default source
instead relocates each callback to `?releaseBuffer@?$StringBase@D@@AAEXXZ`,
whose body is at `0x00036410`. This is existing identity debt, not lost coverage.

## Verified trials (all reverted)

- Original: normal builder verifies 43/43 rows, 20 nonempty and 10 empty
  string references. Frozen-file check finds no unrowed definitions.
- `/DBFME_ASCII_DTOR_DECL`: normal builder still verifies 43/43 masked rows.
  Object comparison finds unchanged raw code for common definitions, but
  redirects **nine** cleanup relocations to `??1AsciiString@@QAE@XZ`:
  the two callbacks and seven ordinary temporary cleanups. The ordinary calls
  need the release worker, so matching masked bytes does not justify landing.
- `/DBFME_ASCII_IMPLICIT_DTOR`: both callbacks now refer to
  `??1AsciiString@@QAE@XZ`, and ordinary temporary cleanup keeps the worker.
  However ShowMemberRank and ShowCommandPoints no longer match their static
  string construction call. The emitted AsciiString text constructor grows
  from 18 to 49 bytes: member initialization plus the in-body StringBase
  construction introduce EH. The parent EH/funclet gate refuses the trial.
- An out-of-class `__forceinline` redeclaration of the existing constructor
  is rejected by MSVC C2761; it cannot supply a unit-local inline policy.

Restored the original source, rebuilt it successfully (43/43), and reran the
ordinary link preview. Index `8661f15284`, measured 2026-11-03 20:03:
`LINKS`, 1,682 -> 1,682 authored bytes. This is a preview, not a census gain.
`link_check.py --fetch-index` also supplied the published object store.

Before the trials, the owning `repair_queue.py retire identity` refused to
retire either key because 150 ledger objects were missing and eleven
referenced-provider objects were not proven current. No baseline was edited.
These are separate prerequisites from correcting the two live relocations.
The existing data-guard debt at `0x00A068D8/E0` is outside this attempt.

## Next useful work

Recover a coherent AsciiString implicit lifetime and text-constructor shape.
In the existing shared shim, implicit mode stores a StringBase member, but the
text constructor first default-initializes it and then reconstructs it through
a cast in the body. Investigate direct member initialization under that mode,
keeping other consumers verified; this is a structural lead, not a tested fix.
Require the two parent constructors, their EH graphs and both static thunks
exact together; inspect all nine cleanup relocations, not just masked bytes.
Only retire registered keys after the owning tool has current provider closure.
No source change, alias, pin, hatch, debt reduction or link gain is claimed.
