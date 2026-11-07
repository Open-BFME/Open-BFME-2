# ModelConditionFlags is BitFlags<591>, proven from its own name table (2026-11-07)

The code-identity survey left a tree-wide question open: `ModelConditionFlags` is spelled
three mutually inconsistent widths in this repo, two of them citing evidence, and nothing
could move until one was settled. It is settled. Nothing was changed here; this is the
proof and what follows from it.

## The proof

`reverse/data_rows.csv` holds `?ModelConditionNames@@3QBQBDB` at VA `0x00DBAA98`
(RVA `0x009BAA98`), **matched and owned**, in
`Code/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContain.cpp`. Its recorded
facts settle the count twice over:

- **size 2368 bytes.** The table is `const char *const[]`, so 2368 / 4 = 592 pointers, and
  the lookup loop is `for (name = list; *name; ++name)` - NULL-terminated - so 591 names.
- **"initializer equal to retail with 591 relocation(s) on target"**, from the row's own
  evidence note. One relocation per name pointer; the NULL terminator is not relocated.
  591 again, independently.

591 bits is `ceil(591/32) = 19` dwords = **76 bytes**, which is exactly the storage of
`Rva00049BE8` - `UnsignedInt m_bits[19]` - the class typedef'd `ModelConditionFlags` in
`W3DDisplayGatherAnimationDebuggingInfo.cpp`. Three facts agree.

The competing widths do not survive the same arithmetic. A name table for `BitFlags<304>`
would be (304+1)*4 = 1220 bytes, and for `BitFlags<117>` 472 bytes. The table is 2368.

## What this corrects

`Code/GameEngine/Source/Common/BitFlags304GetSingleBitFromName.cpp` asserts in its header
comment: "This BFME2 binary's ModelConditionFlags is BitFlags<304> (see the sibling
BitFlags304BuildDescription.cpp, already matched, which reads the same per-instantiation
extern array under the name ModelConditionNames)." The ledger row for its body carries the
same claim - "FRONTCRUSHED anchor; BitFlags<304>=ModelCondit...".

That identification is wrong, and the reasoning shows why it was easy to reach: the unit's
`getSingleBitFromName` body just walks a NULL-terminated name array and compares strings, so
it compiles to the same bytes for *any* bit count. Byte-matching at 304 proves the body, not
the width. The array it reads is the 591-entry `ModelConditionNames`.

The sibling `BitFlags304BuildDescription.cpp` reads the same array, so it is likely
misidentified the same way and should be checked with it.

## The repair, and why it is not a comment fix

Correcting only the comment would leave the code contradicting it. The unit instantiates
`BitFlags<304>` and its row name encodes that width - `?getSingleBitFromName@?$BitFlags@$0BDA@@@SAHPBD@Z`,
where `$0BDA@` is 304 - so the honest repair is to respell the instantiation and rename the
row together, in its own verified commit. The body should compile identically, since the
loop does not depend on the bit count, but that must be shown rather than assumed.

Also unblocked by this: the `W3DModelDraw.cpp` bindings recorded in
`reverse/attempt_support/code-identity-untried-20261107/`. Those three rows call a `__copy`
over a 24-byte element, and a `ModelConditionFlags` is 76 bytes, so whatever that vector
holds it is **not** a flag set of this type - which is a second, independent reason the
attempt log's "establish the real ModelConditionFlags count" step could not have resolved
them. The count is now established and it does not fit.

## Related, and not settled here

`KindOf` is proven `BitFlags<218>` by the same technique in
`KindOfGetSingleBitFromName.cpp`: a 218-entry table at `0x00DBBE18`, declared
`TheKindOfBitNames[0xDA + 1]`. Yet `BitFlags<116>` is used for KindOf masks elsewhere -
`extern BitFlags<116> KINDOFMASK_NONE` in two W3D units - and 116 bits is 4 dwords where 218
needs 7. So the same class of inconsistency exists for KindOf and is worth the same
treatment; the technique is to count the table, and the tables are already rowed.

## The repair has no tool path today (measured 2026-11-07, later the same day)

Respelling the instantiation is a source edit anyone can make. Renaming the row with it is the
part that has no supported mechanism, and both candidate tools were tried and refuse:

- `tools/rename.py function --rva 0x000B42CA --old '...$0BDA@...' --new '...$0CEP@...'` answers
  `refused: the new name is the old name`. The tool compares the *identifier* only, and the
  identifier is `getSingleBitFromName` on both sides, so a change confined to the class's
  template argument looks like no change at all. Its `--new` help says as much: "new identifier,
  or the full mangled name (identifier change only)". Running the same thing through
  `name_lane.py apply` reaches the same refusal, since apply lands through `rename.py`.
- `tools/add_match.py --replace-rva 0x000B42CA` is documented as the way to convert a row whose
  name really changes, but it "accepts scaffold rows only". These two rows are `matched`, not
  scaffolds, so it will not take them.
- `tools/rename.py class` respells a class *token* in every name and view. The token here is
  `BitFlags`; the argument is not a token, and respelling `BitFlags` would hit every width.

So the repair needs either a new capability - `rename.py function` accepting a mangled name whose
only difference is the class's template argument, rewriting `BitFlags<304>` to `BitFlags<591>` in
source and byte-verifying the result - or a maintainer's judgement on which existing tool should
own it. It is deliberately **not** done by hand: `add_match.py` exists because hand-edited rows
corrupted the ledger, and this change touches a `matched` row's name.

## How far the tree has already moved

The 591 spelling is not a proposal; it is already the majority of the tree, which makes the two
remaining rows stragglers rather than a convention to argue about:

- `reverse/functions.csv` holds **5** rows spelled `$0CEP@` (591) and **2** spelled `$0BDA@` (304).
  The two are `?getSingleBitFromName@...` at `0x000B42CA` and `?setBitByName@...` at `0x000B65CE`,
  in `BitFlags304GetSingleBitFromName.cpp` and `BitFlags304SetBitByName.cpp`.
- Under `Code/`, **20** files spell `BitFlags<591>` and **16** still spell `BitFlags<304>`.

A completed repair therefore also renames those two units (`tools/rename.py file` moves a unit
within its directory with its path-keyed rows), since `BitFlags304*.cpp` would then be misnamed.

## The unit disagrees with itself three ways

`BitFlags304GetSingleBitFromName.cpp` carries three different widths at once, which is worth
knowing before trusting any one of its comments:

- line 15 asserts "This BFME2 binary's ModelConditionFlags is BitFlags<304>";
- line 51's recorded symbol is `?getSingleBitFromName@?$BitFlags@$0IAB@@@SAHPBD@Z`, and `$0IAB@`
  decodes to **2049**, which matches neither the row nor the claim above it;
- line 52 instantiates `BitFlags<304>`, which is what the row name encodes.

The measured answer is 591, from the size of the table the body actually walks. All three
markers should move together when the row does.
