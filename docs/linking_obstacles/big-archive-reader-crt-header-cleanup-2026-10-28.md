### BIG archive reader CRT header cleanup (2026-10-28)

Status: scoped cleanup verified; external consumer/census confirmation pending.
Inspected base `b3417cdde8`, published index `d92e7e6635`. The archive reader
uses the real CRT headers with its original imported/direct call forms.
All nine function rows, one data row and the EH graph remain exact; all
104 external COMDAT fingerprints and definition/reference sets are unchanged.
Strict preparation passes; ordinary preview retains LINKS for 606 authored
bytes. The header queue loses four local-declaration findings.
[Evidence and checks](../../reverse/attempt_support/bigarchive-ms-headers-20261028-codexb.md).
No census gain is claimed. Default-picker rechecks also confirm the existing
Rva00380200Getter and BfmeFVFDescriptorVertexDeclaration repairs (7/7 and 6/6
rows, previews LINKS for 914 and 1,820 bytes); LINK-132/LINK-133 census
confirmation remains pending.

The staged-tree batch audit is INCONCLUSIVE (exit 2): index `d92e7e6635`
predates the base and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
consumer and the unchanged archive-provider scope into the next scheduled
census. Full consumer closure is not claimed.

2026-10-30 follow-up: the owning Microsoft-header auditor finds no remaining
local-declaration or include-closure findings in the already repaired source.
Its scoped queue refresh removes the reappearing four-finding entry. Strict
preparation again verifies nine function rows, one data row and the three
parent-owned funclets; EH is EXACT and the ordinary preview retains LINKS for
606 authored bytes against index `12b9e7a7c0`. This is stale queue retirement,
with no new source repair or census gain. The broader consumer/census
prerequisites above remain pending.
[Follow-up checks](../../reverse/attempt_support/bigarchive-stale-msheaders-20261030-codexb4.md).
