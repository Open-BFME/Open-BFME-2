### W3DView Region3D output-storage adoption (2026-10-30)

At base `28a66c803b`, W3DViewGetAxisAlignedViewRegion.cpp adopts canonical
Region3D while retaining the existing Coord3DCtorView companion for the
corner array. Explicit float output storage for getExtent avoids the extra
member lifetime calls and unwind state that blocked the earlier trials.
All three rows, both literals and the parent EH graph remain exact; all
three external COMDAT fingerprints and definition/dependency sets are
unchanged. Strict preparation passes, and the owning header acceptance tool
retires one queue row. Ordinary preview retains LINKS, 389 -> 389 authored
bytes against `85f6b7f40c`. No census gain is claimed. Region.cpp's separate
Coord3D class-key/streamer-provider prerequisite and W3DView's remaining
composition work stay open. Carry the provider and affected consumers into
the next scheduled census; full consumer closure remains pending.
[Representation, verification and audit boundary](../../reverse/attempt_support/region3d-view-header-20261030-codexb4/README.md).

The staged outgoing-batch audit is INCONCLUSIVE: index `85f6b7f40c` predates
base `4bc55a5889`, and LinearCampaignManager.cpp lacks a current receipt
after a normal 35/35-row campaign build. Supported preparation stops at its uncacheable
include inventory (unknown macro/parent-traversing search roots). Carry the
campaign providers and their affected consumers into the next scheduled
census too; this does not clear their wider composition prerequisites.
