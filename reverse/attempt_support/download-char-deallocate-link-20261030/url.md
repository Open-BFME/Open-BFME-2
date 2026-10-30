# Downloader URL builder inline allocator cleanup

Inspected base `0deec88cb3`, provider index `ccafe54d1d` (2026-10-30 15:43).
The URL builder has the registry unit's same debug-only const allocator,
proxy and rebind copies. Its separate primary-proxy specialization preserves
the existing null check and throwing `_STL::free` operation directly, keeping
native inline behavior without emitting those three unused definitions.
No header, pin, row, alias, hatch, ABI or compiler-setting changes.

Private before/after verification passes all nine URL-builder rows and its
parent EH graph EXACT. All 42 retained external code bodies and symbolic
relocations are identical. Every removed definition has only `.debug$F`
incoming relocations; import symbols are unchanged. The actual strict object
reproduces the private candidate.
[Private comparison](url-comparison.json), [actual object](url-actual.json).

The unchanged first proxy and rebind providers remain selected. Both existing
proxy providers independently reproduce all 18 native bytes at `006892B0`;
the five-byte rebind has other identical providers and no executable global
reference. [Provider selection proof](provider-proof.json).

Literal build.sh, frozen checks and strict four-source preparation pass
38/38 rows. All eight cohort EH graphs are EXACT. The current ordinary preview
retains 4/4 LINKS, 942 -> 3,717 authored bytes, with the URL builder 0 -> 868,
registry 0 -> 1,907 and both providers unchanged. No census, full-image link
or new unique-byte gain is claimed. Full affected-consumer selection/loss
checks and scheduled census confirmation remain separate.

Ready-batch audit: INCONCLUSIVE on the older provider index versus
`0deec88cb3` and the missing current CreateAHeroManager consumer receipt.
Carry the full removed-helper/consumer scope into the next scheduled census.
