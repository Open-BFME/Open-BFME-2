# Retail FESL TU root evidence

Starting revision: `fa3296b16d`. Selected TU-evidence run:
`0x0065D1E0..0x0065DDA0` (14 code rows, 13 current source files).

## Target facts

Retail `game.dat` contains 11 source paths under the exact diagnostic root
`\views\feslbuild_main\jabba\fesl\source\`. All 43 function references listed
for these paths in `reverse/string_xrefs.tsv` were independently checked by
disassembling their retail bodies and finding an immediate operand pointing to
the corresponding NUL-terminated string. The image base is `0x00400000`.

For `blobservice.cpp`, the string VA is `0x00CE1EA4`:

* `0x0065D322`: `push 0x00CE1EA4`, inside row `0x0065D2D0`.
* `0x0065DFD3`: `mov dword ptr [esp + 8], 0x00CE1EA4`, inside row `0x0065DF80`.

The other ten source-relative paths are `address.cpp`, `servicehub.cpp`,
`ariesudp.cpp`, `gamebrowser/gamebrowser.cpp`, `demangler.cpp`, `transactor.cpp`,
`util.cpp`, `gamebrowser/gamebrowserdemangler.cpp`,
`gamebrowser/gamebrowserpinger.cpp` and `gamebrowser/lantheateremulator.cpp`.
No external donor source was used to establish these names.

## Placement and inference

The mapper previously recognised only diagnostic roots containing `Code/`.
It now also recognises the exact FESL build root above, preserving the relative
source path under repository home `Code/Libraries/Source/Fesl/`. This home is
a repository placement, not a claim that the SDK originally lived inside
BFME 2's `Code/` tree. Unrelated external roots, headers and ambiguous relative
components do not qualify. Existing confidence and propagation rules remain.

Fresh in-memory maps before/after this change give:

| Change | Code | Other rows |
| --- | ---: | ---: |
| Newly approved | 125 | 52 |
| Approval withdrawn | 87 | 19 |
| Approved TU retargeted | 32 | 35 |

Every withdrawn or retargeted approval previously carried `provisional`.
No nonprovisional approval was withdrawn or retargeted. Approved code rows
increase from 43,709 to 43,747 (+38 net); the rebuilt map's own-evidence check
finds zero contradictions. These are predictions from current inputs, not a
committed map update, source-file reduction, byte-match gain or census gain.
`reverse/tu_map.csv` and its fingerprint are deliberately unchanged.

In the selected run, `0x0065D2D0` becomes an F anchor and the bracketed rows
through `0x0065DDA0` become approved. The preceding `0x0065D1E0` remains only
a K proposal, and `0x0065D280` remains an unapproved C proposal. Later tail
rows `0x0065E030` and `0x0065E270` also lack approval. Shared placeholder class
names and proximity do not establish either boundary; additional independent
TU evidence is still needed before merging those rows. No source was moved.

## Verification

* New tests cover F anchors, C brackets, nested paths, repository case spelling
  and rejection of unrelated roots, headers and malformed relative paths.
* TU structure, TU evidence and gate exploit suites: 150 passed, one skipped,
  excluding the two existing failures below. The complete invocation produced
  the same 150 passes, one skip and those two failures.
* Existing failures reproduced with `HEAD:tools/tu_map.py` substituted for the
  modified module: `test_generated_placeholder_file_is_never_a_donor` (stale
  fixture map yields no donors), and
  `test_repoint_moves_only_absorbed_donor_rows_and_keeps_terminators`
  (`tu_skeleton.repoint` no longer exists). They are outside this change.
* `./build.sh Code/GameEngine/Source/GameNetwork/Rva007F04B0BlobContent.cpp
  Code/GameEngine/Source/Common/BfmeConv1380.cpp`: 4/4 byte matches, 18 literals,
  zero skips; float and import checks pass.
* `find_declared_unmatched.py` accepts both edited Python files before and
  after the change; `git diff --check` passes.

Scratch maps, comparison details and instruction receipts were kept under
`build/fesl-tu-anchor/`; they are not ledger inputs or committed evidence.
