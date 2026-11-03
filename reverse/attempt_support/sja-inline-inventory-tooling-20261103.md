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

## Follow-up: distinguish other STL specializations conservatively

The first repair alone remains too conservative for DeferredWalkers: its
unrelated value-table specializations emit the same method names. A second
tooling commit permits excluding a COFF name only when it lacks a necessary
record name from the source typedef. It expands unique, bounded typedefs;
the sole supported dependent member is STLport 4.6's
`hash_map<K,V,...>::value_type = pair<const K,V>` (_hash_map.h). Unknown,
ambiguous or cyclic typedefs and other dependent members supply no evidence.
Sharing the record names never proves a type equal: it keeps the refusal.
Definitions/imports for the candidate specialization still prevent acceptance.

Source, recorded-header and command-line macros invalidate affected record
names, including spliced macro directives. Both strict currency checks and
the staged-copy equality check remain required. No compiler-attribute-only
exemption is used. Microsoft's description of imported inline functions was
also consulted ([documentation](https://learn.microsoft.com/en-us/cpp/cpp/defining-inline-cpp-functions-with-dllexport-and-dllimport));
the decision still requires current COFF and receipt evidence.

The ordinary build supplies a legacy receipt, so the source trial additionally
used `python3 tools/link_check.py --prepare-current
Code/GameEngine/Source/Common/BfmeConv1292DeferredWalkers.cpp`. That bounded
preparation succeeds and byte-verifies all 6 rows with a strict reusable
receipt. The refined `find_declared_unmatched.py --fail` then passes. Trial
source is restored before the tooling commit; bindings remain a separate
source change. Updated tests: 115 passed, 1 optional replay-fixture skip.
