### LINK-434: version-record clear bound the other record destructor
Status: Repair verified for the clear row; wider consumer audit awaiting verification. Updated: 2026-11-05; inspected revision: `10918f451d`.
Evidence / affected units: `StlportVectorGrowthFootprints.cpp` clear `0x004282EF` now calls `VersionDestructor.cpp`'s `destroyVersionRecords` at `0x002385E6`, preserving all 81 rows and retiring one identity key; [checks and remaining audit scope](../../reverse/attempt_support/version-clear-identity-20261105-codex5.md).
Remaining / next check: the batch audit has an older index and stops at missing current receipt for `Common/0CreateAHeroManager21FE49.cpp`; include the provider and affected consumers in the next scheduled census/current-receipt audit.
Clearance: zero wrong bindings in the edited source; both explicit providers predict LINKS, 7,759 authored bytes unchanged. Wider consumer selection unverified.
Census confirmation: awaiting; no headline gain claimed.
