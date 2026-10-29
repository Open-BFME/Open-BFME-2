# Narrow ostringstream STLport 4.6 link repair, 2026-10-29

Inspected base: `addc18930ae4caf5e401b752b66ebc74fe01f7da`.
Source: `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostringstream_dtor.cpp`.
Scope: six existing rows (429 bytes), no new function, pin or source path.

## Current blocker and history

The default link picker served 0x001F66C6. The current 4.5.3 object has just
one unresolved name in ordinary preview:
`?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z`.
Refreshing the published index retains 85f6b7f40c (2026-10-29 15:08 UTC).
Overriding all three former providers with their current objects still leaves
this consumer unresolved; those three providers themselves LINK.

LINK-140's earlier repair at 462c52b2f7 made the stringbuf overflow/setbuf
unit provide the otherwise unrowed helper. That unit subsequently moved to
4.6 in 5cea349adb and stopped emitting it, just as the prior float/money
migrations had. The earlier repair is therefore no longer sufficient.
The 2026-10-23 uninitialized_copy/assign C1001 trials were read, not repeated.

## Repair and identity evidence

Move the consumer to the pristine STLport 4.6 headers and existing BFME patch
layer with the supported stlport46 marker. Remove its obsolete declaration-only
proxy<char>::allocate specialization: 4.6 inherits allocator::allocate rather
than defining that proxy member. Keeping the specialization with just the
marker change fails C2244/C1506. All other suppression declarations remain.
The migrated object no longer requires the missing 4.5.3 helper.

The compiler-local cleanup label changes from $L14625 to $L13322. The complete
parent graph is EH EXACT and independently places $L13322 at retail 0x0076B44E.
The row already records the correct parent. Through add_match --replace-existing,
classify it as gen-funclet so the existing verifier uses this parent-graph
identity instead of trusting the old compiler ordinal. The row's name, RVA,
extent and source remain unchanged. All six rows gain migrated=stlport-4.6
through that same verified tool. No object-symbol alias or local-label rename
is introduced. This is compiler-cleanup metadata, not new recovered coverage.

A preliminary 4.5.3 trial removing only the proxy specialization also
renumbered the label, but emitted a different helper family (including node
allocation), not the old fbdef5e80d3e helper. It was restored before the
successful 4.6 trial. No unsuccessful source is retained.

## Checks and remaining scope

- Supported whole-file verification passes 6/6 rows, zero string/float/import
  references; frozen-file checking passes. The parent EH graph is EXACT.
- Strict current provider preparation passes after the final ledger update.
- Ordinary preview now LINKS this unit for 418 authored bytes. The six rows
  still total 429 bytes; the preview excludes the 11-byte gen-funclet row from
  its authored count. This is classification, not a removed or uncovered body.
- Joint preview with the current overflow/setbuf, float-format and narrow
  money-put objects is clean for all four units: 5,457 -> 6,442 authored bytes
  in that preview. It also includes the pre-existing stringbuf repair. These
  are predictions, not headline census measurements.
- The object changes from 662 to 127 external COMDAT definitions, 703 to 169
  external symbol records, retaining five weak externals. The six owned rows
  remain exact. Some unreferenced helper diagnostics remain in preview;
  broader consumers and provider selection require the scheduled census.
- The staged-tree batch audit exits 2 at base 86058c40c8: the older index
  lacks current receipts for 34 sources in the affected scope, first
  Common/Rva003A5DA0Write.cpp. Carry this cohort into the next scheduled
  census. The four-unit preview does not clear those broader consumers.

The other historical LINK-140 consumers still need current-object revalidation
and migration or a proven provider repair. This commit clears only the selected
consumer's missing-helper dependency, pending census confirmation. It does not
restore the old link-wide helper or claim the entire obstacle closed.

Scratch evidence under build/snapshot-msheaders-codexb4/: original source and
object, ostringstream-stlport46{-no-proxy.log,-eh.json,-facts.json},
ostringstream-strict-final.log, ostringstream-batch-final.log and
ostringstream-batch-audit.log.

## Preserved targets handoff during preparation recovery

The shared targets document was claimed by another worker at recovery. Its
upstream content is retained; the original handoff is preserved here:

Narrow ostringstream destructor follow-up (2026-10-29, inspected
`addc18930a`, LINK-140): the previous helper provider moved to STLport 4.6
and the selected consumer again lacked proxy<char>::allocate. Migrate this
consumer too and remove the obsolete proxy specialization. All 6/6 rows
remain exact; the exact parent graph binds its renumbered cleanup. Strict
preparation passes and joint preview with the three former providers is
4/4 LINKS (6,442 authored bytes, including 418 in this consumer). The other
historical consumers still need revalidation/repair. No census gain is claimed.
The older-index batch audit lacks current receipts for 34 affected sources,
first Common/Rva003A5DA0Write.cpp; carry that cohort into the next census.
[Evidence and scope](ostringstream-stlport46-link-20261029-codexb4.md).

