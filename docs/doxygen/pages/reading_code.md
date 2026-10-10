# How to read this source {#page_reading_code}

The code under `Code/` is not an original source tree. It is a reconstruction,
written one function at a time and checked against the retail `game.dat`, and
it carries the marks of that process: placeholder names, classes declared
differently in different files, one-function files and comments written for
tools. This page explains those marks, what each one tells you about how far
to trust what you read, and how to look things up.

## The ledger and what matched means {#page_reading_code_ledger}

`reverse/functions.csv` is the ledger: one row per retail function that has
source. Its columns are the decorated name, an export address when retail
exports the function, the address and size of the body in `game.dat`, the
source file that compiles it, a status, and free-form notes. The file is large;
search it with `rg` rather than opening it.

- **A row means matched.** A row enters the ledger only when its source
  builds to retail's bytes at that address: compiled C or C++, assembled
  MASM, or a prebuilt library member. The commit hooks re-check every row a
  change touches. `./build.sh` re-runs the check.
- **Matched is about bytes, not names.** The byte check proves the code, not
  the name or the class layout behind it. Two names for the same bytes would
  pass equally well; the section on names below says what backs each one.
- **Matched is not linked.** Each file is also checked for whether it would
  link with the rest of the tree: its names must resolve, with no duplicate or
  wrong copy. `reverse/link_status.csv` records the last result per file.
  Many matched files do not link yet, commonly because of the private class
  views and hard-coded addresses described below.
- **Addresses.** The ledger's `target_rva` is an offset from the start of the
  loaded `game.dat` image. Tools also print virtual addresses (the offset plus
  the image base in the baseline manifest). Addresses in source comments and
  ledger notes may be virtual addresses, or addresses in another binary: BFME
  1's executable (notes often prefix those with `b1`) or `worldbuilder.exe`.
  Only the ledger columns are `game.dat` offsets.

## Names, and how far to trust them {#page_reading_code_names}

Names are MSVC decorated names, as the compiler emits them: for example
`?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z` is `Bridge::isPointOnBridge`.
They fall into three groups. `reverse/name_tiers.csv` lists the evidence
names and the address-derived placeholders (`Rva`, `Gen`, `d_` and `dup_`
names and Ghidra's labels). It leaves out almost all `uw_` funclets, and
`Bfme`-coined names unless they also embed an address.

- **Evidence names** are proven independently of any contributor: retail's
  export table names the function, or the row is vendored third-party code, or
  the body is a member of a prebuilt library.
- **Placeholder names** claim no identity at all; the next section lists their
  forms.
- **Everything else is a reconstruction.** Most real-looking names are here.
  They come from the Zero Hour or BFME 1 function with the same body, from
  callers and callees whose names are known, from assert strings retail kept,
  and from the WorldBuilder twin. The row's notes say which, and the evidence
  ranges from conclusive to a single lead.

**Placeholder forms.** None of these is a real name, and the guide does not
document them.

- `Rva` or `rva` followed by an address, in a class, function or file name.
  A partial name such as `?rva<address>@Win32GameEngine@@...` knows the class
  but not the method.
- `Bfme` and `bfme` prefixes on files, classes and functions coined during
  conversion, for example the numbered `BfmeConv` files.
- `Gen` and `gen` names; `?d_<address>@@...` byte dumps; `?dup_<address>@@...`
  bodies the linker folded together with identical functions, so that their
  own name is unknown (both usually end `@@YAXXZ`); and `uw_` unwind
  funclets.
- Ghidra's own labels (`FUN_`, `Unwind@`) in `reverse/ghidra_functions.csv`.

A placeholder file name does not make its functions placeholders: a
numbered `BfmeConv` staging file can hold a row whose name is backed by a
donor body.

**WorldBuilder leads.** `worldbuilder.exe` is an unoptimised build of the
same engine, built months before the 1.06 `game.dat`, with assert strings that
name source files and lines. `tools/wb_match.py` pairs its functions with
`game.dat` functions by shared strings, imports and constants, by call graph
and call sites, by vtable slot, or by their order between already-paired
neighbours, and some names come only from such a pairing. The ledger notes tag them `wb-name-unverified`
or `wb-lead` (with the match score), and `reverse/wb_name_leads.csv` lists the
name WorldBuilder suggests for each paired function. Treat these names as
provisional; the guide skips them.

## Private class views {#page_reading_code_views}

Most files declare the classes they use themselves, instead of including a
shared header. Such a declaration is a *view*: just enough of the class for
the functions in that file to compile to retail's bytes.

- **Padding stands in for unknown members.** A view lists the members its
  bodies touch and fills the gaps with padding arrays sized to reach retail's
  offsets. Virtual functions it calls but cannot name appear as numbered slots.
- **Views disagree.** Two files can name the same field differently, or give
  the class different members. Read a member name in a view as one
  contributor's label for a role, and check another view or the Zero Hour
  class before relying on it.
- **Only touched members are confirmed.** The bytes confirm the offsets a
  matched body reads or writes, not the rest of the view.
- **Views are temporary.** Two views of one class in two files can keep
  them from linking: an inline member the views compile differently becomes
  a conflicting copy, and a member one view leaves out is unresolved. When
  a class gets a shared header, it is registered in
  `reverse/canonical_classes.csv`, and a hook then refuses new private copies.
  `python3 tools/class_views.py --class Bridge` lists the current views of a
  class and which of their files link.
- **Shim headers.** `reference/shims/` holds headers that only some files
  include, selected per file by include directories in its compiler flags.
  Two files can therefore see different declarations of a class with the same
  name.

## One function per file, and the original files {#page_reading_code_files}

The ledger records where a body sits in this tree, and that is usually a file
holding one function and named after it, such as
`BridgeIsPointOnBridge.cpp`. Retail was linked from the original
translation units, whose paths survive in its assert strings, and a unit's
functions sit next to each other in the binary.

`reverse/tu_map.csv` recovers that structure: for each function it names the
original file, how sure the assignment is (`approved`, `proposed`, or
`displaced` when the evidence points outside the unit's address range, as it
does for shared inline copies) and the evidence letters behind it, which the
header of `tools/tu_map.py` explains. For example, `tu_map.csv` proposes
`TerrainLogic.cpp`, the Zero Hour file that defines it, as the home of
`Bridge::isPointOnBridge`. Tools then move bodies home:
`tools/tu_skeleton.py` assembles an approved unit, `tools/rehome_rows.py`
moves a row to a home file that already compiles the same body, and
`tools/merge_cluster.py` gathers marked siblings into their destination.

So treat a file name as a current location, not an identity. Files are merged
and deleted as this happens, and two functions in neighbouring files need not
be related.

## Why some bodies look odd {#page_reading_code_shaping}

A body has to reproduce retail's exact instructions, which sometimes takes
code a person would not write.

- **Codegen shaping.** Small inline wrappers, a particular statement order, a
  temporary instead of a re-read, or a condition split in two can be what makes
  the compiler emit retail's branch layout or register choice.
  `docs/matching.md` and `docs/recipes.md` collect these patterns with worked
  cases.
- **Per-file compiler settings.** Files differ in optimisation, include
  directories and defines, all chosen by the first-line flags comment (see
  below).
- **Hard-coded addresses.** Some bodies reach a global or vtable through its
  retail address because its owner has no source yet. `tools/name_globals.py`
  replaces those with named globals as owners land.
- **Escape hatches.** MASM, or inline assembly, is allowed only for a proven
  codegen blocker such as compiler machinery, x87 floating-point shape or
  exception handling (see `Code/masm_dumps/`). Raw-byte emission belongs in
  generated files under `Code/gen_small/`; `tools/conversion_gate.py`
  refuses new raw-byte emission, and new naked functions, anywhere else in
  `Code/`, though a few older ones remain. `reverse/hatch_baseline.tsv` is a
  shrink-only register of every way around the byte check that remains.

Read such code for what it does, and do not tidy it in this tree: the byte
check will refuse the change.

## Comments that belong to tools {#page_reading_code_tool_comments}

Several comment forms are data that repository tools read and write. They
explain nothing about the game, and you can skip them when reading. Do not
copy them into new code or edit them by hand.

- **The flags comment** on the first line of most files lists the compiler
  switches for that file: include directories, defines and optimisation. The
  build reads it. A similar comment near the top switches a file to the
  STLport build.
- **Ledger annotations.** A comment holding just a decorated name (which
  starts with a question mark), directly above a definition, ties that
  definition to its ledger name; the same form followed by a status word
  declares a definition that is known but not yet tied to an address, or one
  that retail removed. `tools/find_declared_unmatched.py` reads these and
  refuses a file whose definitions are neither rowed nor declared. The
  ledger itself matches a definition to its row by name. One-function files
  often also open with a line giving the decorated name with the retail
  address (and sometimes the size); that line is a note for readers.
- **Cross-links.** A function sometimes exists twice: a readable port of the
  donor body, declared as not yet matched, and a byte-exact reconstruction
  that holds the ledger row. `tools/crosslink.py` writes a comment into each
  half naming the other, and a third form above a class view names the Zero
  Hour header that declares the class. The half that holds the row is the
  verified one.
- **Skeleton placeholders.** Units assembled by `tools/tu_skeleton.py` mark
  each function they do not hold yet with a placeholder comment.
- **Matcher notes.** Evidence lines, member offset notes and Doxygen-style
  member comments in `Code/` and `reference/` are notes for byte matching.
  They often cite addresses from other binaries; the guide's input filter
  removes every source comment, so none of them appears here.

## Staging areas and generated placeholders {#page_reading_code_staging}

Some directories hold code that exists to pin bytes, not to be read.

- `Code/gen_asm/`: assembler dumps of functions that have no C++ yet, many
  per file, each procedure named after its address. The function boundary is
  proven, the identity is not.
- `Code/gen_small/`: generated C++ for small bodies, chiefly the exception
  unwind funclets (`uw_` rows) that `tools/gen_uw.py` owns, and template
  instances over placeholder types.
- `Code/masm_dumps/`: hand-kept assembler for compiler machinery that C++
  cannot reproduce, such as exception-handling helpers.
- **Address-named staging files**, mostly under
  `Code/GameEngine/Source/Common/`: `Rva...`, `BfmeConv...` and the
  family files of deleting destructors. They hold bodies that landed before
  their home file or their name was known, and they shrink as rows move home.
- `reverse/attempts/`: banked near misses. Nothing compiles them; they are
  starting points for the next contributor, not progress.
- **Vendored code**: upstream sources such as Lua, zlib, ATL and the GameSpy
  SDK at the paths BFME 2 built them from (mostly `Code/Libraries/Source/`;
  the GameSpy SDK under `Code/GameEngine/Source/GameNetwork/GameSpy/`), and
  prebuilt runtime libraries under `vendor/`. Their rows carry a `vendored=`
  tag naming the release, and their documentation is upstream's.

A generated row yields to a real one: when someone writes the C++ for a dumped
function, the row is repointed to the new file and the dump is left unused.

## Looking things up {#page_reading_code_lookup}

Run these from the repository root. None of them compiles anything.

| Question | Command |
|---|---|
| Which row, file and notes does a function have? | `rg -n "isPointOnBridge" reverse/functions.csv` |
| Which functions does a file hold? | `rg -F "/File.cpp," reverse/functions.csv`, with the file's name |
| Who calls it? | `python3 tools/callers_of.py` followed by the row's address |
| What does the debug build's body look like? | `python3 tools/wb_show.py` followed by the decorated name or address; add `--gd` for retail's body too |
| Is the name proven? | `rg -F "isPointOnBridge" reverse/name_tiers.csv` (no line means the name is not independently proven: a reconstruction, or a `uw_` or `Bfme` placeholder by its form) |
| Where is its original file? | `rg -F "/File.cpp" reverse/tu_map.csv`, with the current file's name |
| Does the file link? | `rg -F "/File.cpp," reverse/link_status.csv` |
| Which views of a class exist? | `python3 tools/class_views.py --class Bridge` |
| What did Zero Hour do? | `rg -n "Bridge::isPointOnBridge" reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code` |
| What did BFME 1 do? | `rg -n "isPointOnBridge" reference/open-bfme-1/game` |

`tools/wb_show.py` also marks each callee as a real, partial or placeholder
name, which is a quick way to judge a neighbourhood. `docs/agent_tools.md`
lists the Ghidra database queries contributors use for deeper questions.

## Modding notes {#page_reading_code_modding}

- **A matched body states shipped behaviour.** Every build checks a matched
  body's instructions, and the string and float literals it references
  directly, against retail, so a limit or a magic number written in that
  code is what 1.06 does. Data tables are not covered yet: the INI field
  tables that map field names to parsers, and other initialised globals, are
  not byte-checked, so field names and values read from them are unverified.
  Nor are a view's padding and member names.
- **Directory is a first hint at determinism.** Zero Hour keeps the
  simulation under `GameLogic` and per-machine presentation under
  `GameClient`, and retail's assert paths show BFME 2 using the same
  directories. Staging files sit outside that split, so check the class, not
  just the path, before assuming a change is safe for multiplayer.
- **Prefer evidence and settled names.** Before building a mod on a function,
  read its row's notes and name tier; a WorldBuilder lead or a placeholder can
  be renamed or re-identified.

## Remastering notes {#page_reading_code_remastering}

- **Views encode a 32-bit layout.** Padding arrays are sized from retail's
  offsets, which assume 4-byte pointers and MSVC 7.1 alignment. A port to
  another compiler or to 64-bit needs real class declarations first; the
  shared headers in `reverse/canonical_classes.csv` are where that work
  collects.
- **Shaped code is semantically ordinary.** The wrappers and orderings that
  exist for the byte match can be simplified in a fork once byte identity no
  longer matters, but keep the behaviour, including retail's odd cases. The
  `Xfer::XferRawBytes` note in `docs/matching.md` is an example: the obvious
  guard condition is not the one retail tests.
- **Hard-coded addresses only work in retail's image.** Any body that still
  reaches data by address must be converted to named globals before the code
  can run anywhere else.
