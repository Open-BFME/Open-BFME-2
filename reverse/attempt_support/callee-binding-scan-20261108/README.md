# Callee-binding scan, 2026-11-08

Check this first when a boot stops. It compares a diagnostic image with retail by reading both; it runs nothing. The byte gate
masks call targets, so a row can match retail's bytes while its calls bind to a body retail never had. P31, P37, P38, P40, P43 and
P44 were that defect, and each cost a boot and a diagnosis.

Reference list: `callee-binding-master-f9b8b46525.tsv`, from the plain master diagnostic image at
`f9b8b465255add1f519b12329e8a6f76617c9158` (real link run 42489542040, 0 duplicates, no test-only commits) with the ledger at that commit.

**It predates the landing of P36, P47, P48 and P50**, and of anything else after `f9b8b46525`, so those fixes' entries are still listed: check
`git log f9b8b46525..origin/master` before chasing a row. It will be refreshed when a later master image has them. Rerun the scan on the
newest image before relying on a miss.

**A row's absence clears nothing**, for the reasons under "What it can't see". A test stack's image can also hide defects: on the earlier
list, from `swarm/scan/p36-boot` with its P29 diagnostic, P29's entries were missing; they are back on this plain image.

## Looking up a row

Addresses in the file are lowercase and unpadded: `0x2d07f4`, not `0x002D07F4`.

A pair is listed under the body that differs, which is usually the callee, not the row that calls it. So search `chain` as well as
`retail_rva`. On the control image P29's wrong binding is listed at 0x256fb5 and 0x2cfa6c, with 0x2d07f4 only in their chains, and
0x2d0b36 does not appear at all. `chain` holds the first path the walk found, so a row missing from it can still reach a listed body.

    grep -F '0x2d07f4' callee-binding-master-f9b8b46525.tsv    # matches retail_rva and chain

**A stop only counts as absent after searching by callee too.** Take the retail call targets of the row at the stop and of its callers,
and search each address the same way. Searching names is not enough: a row is listed under retail's name for the address, which can
differ from the image's. Crash triage found P49 this way, at order 1780 (`0x53f1ec`), a hash table's `resize` bound to the wrong body.

## Running it

    python3 callee_scan.py IMAGE_DIR LEDGER_DIR GAME_DAT OUT_PREFIX

`IMAGE_DIR` holds `image/exit.exe`, `image/exit.map`, `image/image_objects.json` and `stubbed.tsv`. `LEDGER_DIR` holds
`functions.csv` and `data_ledger.csv` from the image's own commit. Read-only; about 30 seconds. `cs_sample.py` prints a random sample,
or named retail addresses, from the result with the chain and the differing instructions; run it from a worktree at the image's commit.

## The walk

From each address whose row has one body in the image, it follows the image's calls and retail's calls in step, comparing each pair
of bodies with addresses masked. A template name parked on an address no real caller reaches in step never counts. A wrong stand-in
reached from a real caller does, even when a good name sits at the same address, which is how P40 and P43 hid.

## Classes

For each pair of (retail target, image target):

| Class | Meaning | Count here |
|---|---|---|
| `ok-named` | The image target carries a name the ledger gives retail's target, and the bodies match | 72,620 |
| `ok-identical` | Another name, but the same body with addresses masked | 8,056 |
| `ok-forwards` | A short image body that calls or jumps to a symbol the ledger gives retail's target: a wrapper around the real row | 19 |
| `named-body` (listed) | The image target has retail's name but a different body: another object's copy won, or a caller bound a local static copy | 267 |
| `other-body` (listed) | Another name and a different body | 333 |

`callee-binding-master-f9b8b46525.tsv` lists the 600 differing pairs in boot-walk order, with these columns to read them by:

- `layout`: compares the numbers a type's layout shows through (member offsets, shifts, pushed sizes, virtual call slots). `same`
  means none differ, `operands` means only operands differ in the same instructions, and the others mean a number exists on only one
  side. This ranks; it does not filter (see the controls).
- `only_retail`, `only_image`: those numbers.
- `tags`: `eh-flavor`, `frame-flavor` (compile differences), `alloc-family`, `operands-only`, `registers-or-operands`, `other`.
- `homes`: how many retail row bodies have this image body's shape. Common shapes have many, so it proves nothing about type.
- `root`, `chain`: where the walk came from, as `retail rva+offset` hops.
- `order`, `anchor`, `tier`: position in LINK-627's boot walk over retail's call graph.

| The 600 | On the boot walk | Not reached by the walk |
|---|---|---|
| A size or offset differs (`layout` not `same`) | 163 | 134 |
| None differs (`layout` `same`) | 150 | 153 |

## How far to trust a row

Read each one beside retail before acting; a row here is a lead, not a defect. My rough estimate from two small hand samples, taken
on the earlier test-stack list, is that about half are real, and not all of the real ones would crash. From the boot-walk rows: 15 with a differing number gave 4 wrong
element or body (5 rows, one type twice), 3 allocator or destructor differences, 4 harmless compile differences (one unsure), 1 P45,
1 scanner bug since fixed and 1 forwarding wrapper the scan now recognises. 8 with no differing number gave 2 real, 1 unsure, 5 harmless.

## Controls

On image `02843f3a5308cba94743f7e7cd707fc54a59e55c`, from before the P31 fix: P29, P31, P37, P38, P40, P43, P44 and P45 all appear.
P33 is missed, because its wrong binding goes through a function table in data.

Filters tried and thrown out because they lost a real crash: "a sibling name at the address binds correctly" and "retail holds this
body's shape somewhere" both drop P40 and P43. The `layout` test drops P37, P38 and P44, so it only ranks.

## What it can't see

- Indirect and virtual calls, and function pointers in data tables (P33's kind).
- Funclets, about 31,000 addresses, because their names aren't unique.
- 724 rows with no body in the image.
- Wrong globals, because data addresses are masked.
- Folds: "identical body" only means the bytes match with addresses masked, not that the type is right.
- Reachability: the boot walk is only a ranking. It marked P43's path unreached even though P43 crashed during boot, so "not reached"
  excludes nothing.
