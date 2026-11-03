# SJA inline-adapter frozen-inventory repair

Inspected source revision: cc80e697fd. This tooling commit does not change
game sources, ledger rows, markers, whitelists or compiler flags.

The earlier refusal is recorded in
`sja-native-providers-20261103/frozen-refusal-proof.json` and the existing
false-reject re_attempts entry for Rva00411336 at 0x00411336. Replaying HEAD's
checker on a minimal qualified typedef specialization reproduces exit 1 and
`_STL::TableAlias::_M_bkt_num_key`, even with an unrelated matched owner row.

Keep these definitions in the source inventory. Exempt only explicit
`template <> __declspec(dllimport) __forceinline` definitions whose inspected
source equals the working copy and whose strict current compile receipt
covers source, flags, headers and include search inventory. The current COFF
must contain neither an emitted definition nor any import/reference with that
method name, across all class spellings (typedefs differ from COFF names).
Missing/stale objects and staged/working-copy differences fail closed.

Validation: `python3 -m pytest -q tools/tests/test_find_declared_unmatched.py
tools/tests/test_gate_exploits.py`: 102 passed, 1 optional replay-fixture skip.
Tests exercise actual COFF parsing, emitted bodies, unresolved imports, another
class's same-named method, absent/stale objects, staged-copy differences, and
comments/inline keywords without object proof. All concrete gate exploits
remain refused. Current unchanged DeferredWalkers passes `--fail`.

The three source adapters remain unapplied in this commit. Apply and byte/link
verify them independently after this checker repair; no link gain is claimed.
