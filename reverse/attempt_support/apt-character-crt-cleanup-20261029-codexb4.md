# Apt character setter declaration cleanup

Base: `b98e313906`; preview index: `840db2d676` (2026-10-28 20:44).

The inherited working-tree trial replaced two local CRT prototypes with
`stdlib.h`. Its saved original agrees byte-for-byte with HEAD, and its existing
file claim belongs to this runner. Neither `atoi` nor `strtol` is used in this
TU. Remove the unused prototypes and omit the unnecessary trial header.
The owning Microsoft-header scanner's scoped `refresh_queue` removes exactly
this file's queue row; all unrelated queue records remain unchanged.

`./build.sh Code/Libraries/Source/Apt/AptCharacterSetMember.cpp` passes all
five rows, 21 string literals and 22 float literals. The three unwind labels
renumber naturally and verify through the parent's EH data. Frozen-source and
Microsoft-header checks pass. Comparing the original and final objects using
the census COFF reader preserves all 25 COMDAT digests/sizes, all 72 external
symbol records and all 68 external relocation target names. Strict current
preparation passes. Ordinary preview retains LINKS, 3,735 -> 3,735 authored
bytes. No census linking or image-ownership improvement is claimed.

The staged-tree batch audit is INCONCLUSIVE: the index predates the outgoing
base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and this provider into the next scheduled census.

## Default link pick

The picker claimed `TransitionDamageFX.cpp` through its default-constructor
closure at 0x00256646. Its census blocker is the selected
`vector<AsciiString>` copy constructor. Current source already declares that
copy constructor without defining it. LINK-135 records the separate
`CreateAHeroDataCopy.cpp` suppression repair. A paired ordinary preview with
the current CreateAHeroDataCopy and
`stlport_vector_asciistring_copy_backward.cpp` objects reports all three LINKS:
404, 167 and 1,134 authored bytes respectively. The lone target preview against
the saved provider objects still reports the old selected-copy blocker.
No source repair was attempted; await the normal census refresh rather than
repeating the existing fix. This is preview evidence, not a new census gain.

## Reference freshness

Official BFME 1 master was fetched at `326ef10249d19dd08940fbf18467af2c98a4305a`.
The update scope is held by `yasinschroeder-codexb`; keep the verified
`e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc` pin. Commit `db41f2b901` documents its
full verification. No new freshness success was recorded and no submodule
input changed in this cleanup.
