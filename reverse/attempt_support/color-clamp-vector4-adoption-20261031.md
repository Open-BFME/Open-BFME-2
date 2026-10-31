# DX8 color clamp: canonical Vector4 with native store order

Base `b56e8fa90`; claimed Vector4 and file scopes. Replace the private
four-float Vector4 class in `WW3D2/DX8WrapperConvertColorClamp.cpp` with the
existing `../WWMath/Vector4Data.h`. Native component offsets and the
existing contract agree on the 16-byte X/Y/Z/W storage. Vector3's separate
private view and the existing, justified inline assembly remain unchanged.

The complete source retains its three rows: Has_CMOV_Instruction at
`00126071` (6 bytes), Clamp_Color at `00126082` (250 bytes), and
Convert_Color_Clamp at `0012617C` (399 bytes). Every byte and relocation of
all five retained external code functions, including the existing conversion
helper and anchor, is identical. Their two pre-existing honest unmatched
markers are retained; no marker, pin, alias, data row, flag, header or source
path is added or moved.

Direct pointer-based component expressions change Clamp_Color's SSE
store/compare order. Per-component local references also fail this row.
A TU-local static force-inline reference accessor using `(&color.X)[index]`
preserves the old member-access expression shape and restores all rows.
The first compile's missed alpha subscript is corrected through the same
accessor; no failed source remains. Useful controls are preserved.

The old shared mutable Vector4 subscript definition disappears. Its only
incoming edge was a `.debug$F` relocation. The local replacement does emit
one internal code copy, also referenced only by `.debug$F`: all five retained
runtime functions and their relocation lists are unchanged, and no new
runtime call is introduced. The internal helper is an implementation detail,
not a new native identity or matched-byte claim. The separate equality
adoption emits no replacement helper.

Normal/frozen gates, fresh two-source strict preparation and owning Vector4
acceptance pass, retiring exactly this file's one queue key. Together with
the comparison adoption, the normal gate passes 5/5 rows, and two Vector4
keys are retired through the owning acceptance tool. Bounded preview against
`3c7a254a38` (2026-10-31 13:43) retains LINKS/654 for this source and
LINKS/131 for comparisons, cohort 785 -> 785. These are the tool's authored
preview counts, distinct from summing the three listed row extents. No new
census-linked bytes or runtime improvement is claimed.

The comparison commit's shadow code-identity check reports a divergent
`Matrix3D::operator[] const` copy. The before/after COFF comparison proves
that existing body and every relocation unchanged, so this is not a newly
changed implementation; reconciling the separate Matrix3D class/provider
remains open. Scoped LINKS does not establish broader provider selection.
The outgoing affected-consumer audit and scheduled census remain separate.

Original/intermediate/final source and object controls, compiler failures,
actual-object comparisons, debug-only incoming-edge inventory, acceptance,
strict receipts and preview logs are retained in ignored
`build/two-each-no-qwen-20261031-1707` and the matching diagnostic package.
Qwen and other local inference remain off; the shared ten-worker cap remains
in place without changing an Unreal process.

## Outgoing consumer audit

After fresh strict preparation of both owned sources, the audit at explicit
base `9a6314fbcd8230b1e516d039768f806bfad158d6`, tip `979c4576f`, with
the NUL-delimited two-source list returns INCONCLUSIVE, exit 2. Index
`3c7a254a38` predates that base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. The changed providers themselves have fresh receipts.
Full affected-consumer loss clearance remains unproven; carry the provider
scope and consumer into the next scheduled census. The publisher hook
audits the final rebased outgoing range again.
