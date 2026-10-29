# AptMessengerOnline TU merge (verified, apply blocked) — 2026-10-29, worker dd-09

Item: `next_work.py --tier consolidate --claim` served "tu-merge
Code/GameEngine/Source/Common/AptMessengerOnline.cpp" (one donor, 18 rows:
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMessengerOnline.cpp`).

Scope claims: `file:` on both paths, taken by the picker on the PC. The sandbox
cannot push claim refs (no GitHub credentials by design), so `tu_skeleton.py
--merge` was run with `--no-claim`; the scope was already held by this seat.
That also means the merge's own RVA claims never ran here — the next seat should
run it with the picker's `--claim` or a direct `claims.py claim` on the rows.

## Landed: the donor reconciliation (9ebc5ba033)

The merge first rejected the donor with `C2511: 'AptMessengerOnline::AptMessengerOnline(void *)'
: overloaded member function not found`, because the two files declared different
views of `AptMessenger`/`AptMessengerOnline`. `tu_views.py --dry-run` planned
`AptMessenger` but refused `AptMessengerOnline` ("prefix at +0x0 lies under the
bases") and `Rva005AE7A5Class` (class-key differs).

Target evidence settles the layout: `AptMessengerConstructor.cpp` (the base's own
constructor, row 0x0051215B) declares `AptMessenger` with `m_27C`,
`m_280` (vector<unsigned int>), `m_28C` (vector of the 8-byte tab entries),
`m_298`, `m_29C`, `m_29D`, and constructs `m_28C(2)`; so the base ends at +0x2A0
and the donor's `prefix[0x28c]` stood in for the whole base. Commit 9ebc5ba033
gives both files that view (fields `protected` so the derived body may read
them), names the vector/flag the same way in both, and both files byte-match,
18/18 rows.

## Dry run now accepts

`python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/AptMessengerOnline.cpp --dry-run`:

    accepted: ['Code/GameEngine/Source/Common/AptMessengerOnline.cpp',
               'Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMessengerOnline.cpp']
    rejected: {}
    flags: ['/DNDEBUG', '/MD', '/EHs', '/D_CRTIMP=', '/D_STLP_USE_STATIC_LIB',
            '/Ireference/shims/bfmealloc', '/Ireference/shims/bfme2_ascii']
    rows: 18
    carried: {'reverse/hatch_baseline.tsv': 'hatch_counters --update'}
    trailer: Verifier-Change: tu_skeleton --merge carried the protected-register
             keys of 1 absorbed donor(s) to Code/GameEngine/Source/Common/AptMessengerOnline.cpp
             (transfer; totals kept)

## Apply blocked in the ms-header audit

`--merge` (with `--no-claim`) writes the TU and the two row ledgers, then
`transfer_registers()` calls `ms_header_audit.load_index()`; with no cached
`build/ms_header_audit/index-<key>.pickle` it runs `build_index()`, whose
"kitchen sink" step preprocesses a 4488-byte probe of the CRT/Platform SDK
headers with `cl -E`. On this sandbox that `cl.exe` ran at ~99% CPU for 11+
minutes with no output, twice (once inside the merge, once in a standalone
`load_index(rebuild=True, jobs=1)`); single-header probes (`<stdio.h>`,
`<windows.h>`, `<comdef.h>`) return in about a second, so it is the combined
probe, not the toolchain. Both runs were stopped and the tree restored
(`git checkout` of the TU and the two ledgers); nothing partial was committed.

## Next steps

1. Warm the index where it builds: `python3 -c "import sys; sys.path.insert(0,'tools');
   import ms_header_audit; ms_header_audit.load_index()"`, then
2. `BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --merge
   Code/GameEngine/Source/Common/AptMessengerOnline.cpp`, and
3. `./build.sh Code/GameEngine/Source/Common/AptMessengerOnline.cpp`,
   `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/Common/AptMessengerOnline.cpp`,
   then commit with the printed subject and the `trailer:` line above.

The reconciliation commit is independent of the merge (both files keep their
own rows and byte-match), so it is safe to land on its own.
