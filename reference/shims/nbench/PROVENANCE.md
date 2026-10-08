# BYTEmark / nbench-byte: retail is 2.1 (pre-Dierks); these headers are 2.2.3's

## What retail links

BFME 2's game.dat statically links **BYTE Magazine's BYTEmark** in Uwe F.
Mayer's Linux/Unix port `nbench-byte`, at release **2.1 (1997-12-11)** --
not 2.2.3 as this file said until 2026-10-08. Identity is not in doubt:
`calc_confidence`'s error string, the `wordcat.h` catalogue, the
`CPU:Stringsort` tag (`.rdata` 0x008E7778) and the 0.09 BETA constant in
nbench1.c's back-prop loop are all in the image, EA's own `Benchmark.dsp`
(Zero Hour) names the files, and `reverse/functions.csv` claims 88 rows
(24,734 bytes) against `Code/Libraries/Source/Benchmark/`, the BYTEmark
bodies running from `calc_confidence` 0x006B32E0 to `DoEmFloatIteration`
0x006B9C40, with EA's `RunBenchmark` replacement for `main` at 0x006B3640.

The release is decided by the one compiled-code change across Mayer's
releases that reaches the functions BFME links: Eike Dierks' assignment
stride fix, added in 2.2 (2003-02-19). 2.1 advances the array pointer by
`i*ASSIGNROWS*ASSIGNCOLS` in `DoAssignIteration` and
`LoadAssignArrayWithRand`; 2.2 and later fix it. Retail has the **pre-fix**
form in both bodies: `DoAssignIteration` 0x006B78B0 loops
`add esi,edi; call 0x006B6B20; add edi,0x9F64` and `LoadAssignArrayWithRand`
0x006B6AB0 (106 B) likewise, 0x9F64 = 101*101*4 = one array's stride times
`i`. Everything else Mayer changed between 2.1 and 2.2.3 is `nbench0.c`'s
`hardware()` hook (never compiled here: EA replaced `main`) and README/Changes
text; `emfloat.c`, `sysspec.c` and `misc.c` are byte-identical across
2.1..2.2.3. Measured on the two tarballs (2026-10-08): `nbench1.c` 2.1 vs
2.2.3 differs by 20 diff lines, all the Dierks sites; `nbench0.c` by 21, the
`hardware()` hook plus line breaks; the three others by 0.

"2.1" means Mayer's port, pre-2.2. Separating 2.1 from BYTE's original 1995
release rests on the ledger's byte-exact matches for bodies Mayer rewrote in
1996-97 (`calc_confidence`'s statistics, 1997-12-07); BYTE's original source
is no longer served, so that bound is from the matches, not from a diff.

## What this directory is

Headers only, copied unchanged from Open-BFME-1's `vendor/nbench`, which
extracted them from the **2.2.3** tarball:

    https://www.math.utah.edu/~mayer/linux/nbench-byte-2.2.3.tar.gz
    111791 bytes, SHA-256
    723dd073f80e9969639eb577d2af4b540fc29716b6eafdac488d8f5aed9101ac
    (LSM entered-date 12MAY2008, sources dated 1997-2004; matches the
    OpenEmbedded `nbench-byte_2.2.3` recipe; copying-policy "freely
    distributable")

Re-checked against that tarball on 2026-10-08: `emfloat.h`, `misc.h`,
`nbench0.h`, `nbench1.h`, `nmglobal.h`, `sysspec.h`, `wordcat.h` and
`hardware.h` are identical to its copies (CRLF aside). Two files are local
and in no tarball:

- `pointer.h` -- the Makefile generates this by compiling `pointer.c` and
  writing `#define LONG64` only when `sizeof(long) != 4`. Win32/MSVC 7.1 has
  32-bit longs, so the generated file is empty.
- `strings.h` -- MSVC 7.1 has no POSIX `<strings.h>`. nbench1.c includes it
  only for `bzero`; this header maps `bzero` to `memset`. Not a compile-shape
  lever.

`sysinfo.c` / `sysinfoc.c` are not vendored: nbench0.c includes them only
under `#ifdef LINUX`, which these TUs do not set.

### 2.2.3 headers against a 2.1 library: why that is inert

The 2.1 tarball (tux.org/~mayer/linux/nbench-byte-2.1.tar.gz, 195315 bytes,
SHA-256 d6cbe372e6096843a4fd7660841fd6dc40f773644f776db5519b83156d29dddd,
fetched through web.archive.org on 2026-10-08) differs from 2.2.3 in three
of these headers, none of which reaches a matched body:

- `nbench1.h`: 2.1 declares `long randnum(long)` / `unsigned long
  abs_randwc(unsigned long)`; 2.2.3 declares them as `int32` / `u32`. Both
  are 32-bit on this target and `misc.c` is not rowed; the call sites compile
  the same.
- `nbench0.h`: 2.2.3 sizes the global output buffers with `BUF_SIZ` (1024)
  where 2.1 uses 100. A `.bss` size; no matched body takes `sizeof` of either.
- `sysspec.h`: 2.2.3 adds an `OSX` guard beside `MAC`. Not defined here.
- `hardware.h` exists only from 2.2 on. The local `nbench0.c` includes it
  because that copy is 2.2.3-derived text (below); nothing in it is compiled
  into a rowed body.

Swapping these headers for 2.1's is therefore possible and not done: it would
be a `reference/shims/` change (scoped or full gate) for no byte and no claim.

## How the sources are actually compiled

The upstream `.c` files are **not** carried here: this repo admits sources
only under the official trees, and the Benchmark wrappers never compile the
upstream text anyway. `Code/Libraries/Source/Benchmark/{nbench0,nbench1,
emfloat}.cpp` are one-line `#include "nbench1.c"` wrappers; a quoted include
resolves to the sibling `Code/Libraries/Source/Benchmark/nbench1.c` first, so
the EA-adapted local copies compile and this directory supplies headers only
(each wrapper's `// cl:` line passes `-Ireference/shims/nbench`; `tools/build.py`
has no nbench hook).

Those local copies are 2.2.3-derived text carrying EA's deltas (`RunBenchmark`
in place of `main`, empty error contexts, printf removal, sscanf parsing of the
embedded NNET.DAT, forceinline levers -- each marked in place) **plus the
version delta hand-reverted**: the two Dierks sites in `nbench1.c` read
`abase.ptrs.p+=i*ASSIGNROWS*ASSIGNCOLS` with the comment "Retail predates
Eike Dierks fix", which is exactly 2.1's text. That revert is the release,
not an EA edit. Measured 2026-10-08: the local `nbench1.c` differs from
2.2.3's by 382 diff lines and from 2.1's by 390 -- the EA deltas either way;
at the two Dierks sites it carries 2.1's statement with a comment added above
it. `emfloat.c` differs by 55 against either (the two releases' copies are
identical).

## Local delta in nbench1.c that no Mayer release explains

`create_text_line` compares its running length unsigned (`jbe`/`jb`) where
every Mayer release declares `charssofar` / `tomove` / `nchars` as signed
`long` (`jle`/`jl`). The local copy casts in the comparison to reproduce
retail. Either BYTE's original differs here or EA edited it; unresolved.
`nbench1.cpp` also compiles with `/MD` so `strncmp` (inlined into `strsift`)
goes through the MSVCR71 IAT slot, matching retail.

## Ledger

The 88 Benchmark rows carry no `vendored=` tag; the version lives in free-text
notes. One note said "BYTEmark 2.2.3 DoBitops" and now says 2.1; the rest name
BYTEmark without a release. Re-derive the count:
`grep -c 'Libraries/Source/Benchmark/' reverse/functions.csv`.
