# Subsystem template: turning a directory into real source

Pillar 3 of the fix plan. One queue item = one subsystem (a directory, or a
retail address block that maps to a handful of original source files). The
profile library (`Code/Libraries/Source/profile/`, retail
0x006C5300-0x006C87AF) was the pilot; its commits are the worked example.

An item is done when the acceptance commands at the end pass. Matching new
rows is optional. Losing an existing match is not allowed.

## 0. Pick and claim

Choose a block with a Zero Hour (or BFME1) counterpart, at least ~40 matched
rows and few callers/callees outside it. List every ledger row in the block's
address range, including rows sourced from other directories:

    python3 - <<'EOF'
    import csv
    lo, hi = 0x006C5300, 0x006C87B0          # the block
    for r in csv.DictReader(open('reverse/functions.csv')):
        a = int(r['target_rva'], 16)
        if lo <= a < hi: print(hex(a), r['status'], r['name'], r['source'])
    EOF

Rows inside the block but sourced elsewhere (`GlobalGetterSingles.cpp`,
`ConstIntGetters*.cpp`, `VtableConstantPredicates.cpp`, ...) usually belong
to the block's TUs under an opaque `Rva...` name. The pin in `symbols.csv` or
the vtable slot that refers to them tells you the real name.

## 1. Assign rows to original TUs

Use the reference tree's file list (`reference/open-bfme-1/inputs/reference/
CnC_Generals_Zero_Hour/GeneralsMD/...`) and retail address order: each
original `.cpp` is a contiguous range. Header-inline COMDATs from other
libraries (e.g. WWLib's `FastCriticalSectionClass` lock) can sit inside the
range; leave them with their owning library and note it.
`_audit/scratch_r_tu/assign.py` automates this for larger blocks.

## 2. Canonical headers first

One header per original header, next to the TUs, with the reference header's
declarations, changed only where retail evidence says so. Evidence goes in a
comment on the header: constructor stores, vtable slot reads (dump the
vtable from the retail image), allocation sizes, field offsets read in
matched rows. Rules:

- No private copies of a class in a `.cpp`. Every TU includes the headers.
- No `/alternatename`, no `#define X (*(T *)0x...)`, no casts to a view
  struct to reach a field. If a call only binds through an alias today, the
  callee needs its real name: rename the row to the name its pin or vtable
  slot gives it.
- Classes owned by another library get one shared header in that library
  (`debug/debug.h`, `WWLib/mutex.h` in the pilot), restricted to evidenced
  members. Register the subsystem's own classes in
  `reverse/canonical_classes.csv` so `tools/class_gate.py` refuses new private
  copies. Register a shared header too once its other private layouts
  (`python3 tools/class_views.py --class NAME`) agree with it.
- Access specifiers and `static`/`virtual` are part of the mangled name. The
  ledger row name, or the `symbols.csv` pin, decides them.

## 3. Write the TUs

One `.cpp` per original file, functions in reference order, each data item
defined once in its TU (delete the address-named duplicates elsewhere and
point their users at the real symbol). One `// cl:` line per TU, the same for
every TU of the subsystem where possible; check it against
`reverse/retail_inventory/flag_regions.csv` (the base flags in `build.py`
already give `/O2`). Start from the bodies that already match: copy them
verbatim and only change the declarations around them.

Compile and compare in scratch before touching the ledger. The pilot's
helpers are in `_impl/scratch/fix-pilot-bfme2/` (`pilot_map.py` maps rows to
TUs; `pilot_verify.py` compiles to `build/pilot/` and runs
`build.compile_function` on every mapped row; `variant.py` compiles a
transformed copy of one TU so you can bisect a codegen difference).

Things that changed codegen in the pilot, and how they were found:

- A dynamic initializer in the TU (`m_clockCycles = GetClockCyclesFast()`)
  changed register allocation in an unrelated function. Removing it
  restored the match: retail has no such initializer in that unit.
- Defining a callee in the same TU (`Profile::SimpleMatch`) changed the
  caller's register allocation. Retail calls `Debug::SimpleMatch`.
- Bisect by deleting blocks in a variant, not by guessing: each variant
  compile costs a few seconds.

## 4. Move the rows

Edit `reverse/functions.csv`: point each row's `source` at its TU, and rename
the opaque `Rva...` rows that now have real names. Then `git rm` the
one-function files and delete the moved definitions from the shared files.
Re-run `tools/hatch_counters.py` and delete the baseline lines for the
removed files from `reverse/hatch_baseline.tsv` (shrink only).

## 5. Acceptance commands

All of these must pass:

    python3 tools/check_csv.py
    python3 tools/build.py <subsystem dir> <each other file you edited>
    python3 tools/class_gate.py <subsystem dir>/*.cpp
    python3 tools/subsystem_link.py <subsystem dir> \
        --harness tools/tests/subsystem_harness/<name>_main.cpp \
        --externs tools/tests/subsystem_harness/<name>_externs.cpp \
        --own <Class> ... [--allow <symbol>] --run
    python3 tools/link_cycle.py --build --out <scratch>/after

`build.py <dir>` byte-verifies every row sourced from the directory plus
its string, float and import references. Run it for each other file you edited
too.

`subsystem_link.py` compiles the TUs, archives them into
`build/subsystem/<name>/<name>.lib` and links the harness with the real
VC7.1 linker without `/FORCE`. It fails if a TU does not compile, the link
reports a duplicate or unresolved name, the harness's extern file defines one
of the subsystem's own symbols, or the library leaves an own-class symbol
undefined (unless it is listed with `--allow`, with the reason given in the
queue item). The externs file stands in for other libraries only.
`report.json` lists the subsystem's external dependencies. That list is the
subsystem's dependency surface.

`link_cycle.py` is the scoreboard. Compare the subsystem's rows in
`link_status.csv` before and after (placed, self_strict, closed_strict).

    python3 - <<'EOF'
    import csv, sys
    for f in sys.argv[1:]:
        rows = [r for r in csv.DictReader(open(f)) if '/profile/' in r['source']]
        print(f, len(rows), *(sum(int(r[k]) for r in rows) for k in ('placed', 'self_strict', 'closed_strict')))
    EOF

## 6. Commit

One commit for the headers and TUs plus the ledger move, through the hooks
(`git -c core.hooksPath=.githooks commit`; never `--no-verify`). Commits that
touch `tools/`, `.githooks/` or baselines need a `Verifier-Change:` trailer.
