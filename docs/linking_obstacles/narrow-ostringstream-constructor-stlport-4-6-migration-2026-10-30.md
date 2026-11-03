### Narrow ostringstream constructor STLport 4.6 migration (2026-10-30)

At base `cd1e14b147`, the constructor TU selects 4.6 and drops the obsolete
proxy<char>::allocate declaration; its deallocate declaration remains valid.
All nine rows and both EXACT EH graphs pass. All 30 retained external COMDATs
are unchanged, 540 old definitions disappear, and undefined/weak bindings
stay identical. Final strict three-source preparation passes 22/22 rows.
Joint preview retains 3/3 LINKS and 1,963 authored bytes against index
`12b9e7a7c0` (constructor 978, destructor 418, overflow/setbuf 567).
The file leaves the owning migration queue. LINK-140's wider cohort remains.

The staged outgoing audit is INCONCLUSIVE on the older index and 33 objects
without current receipts, first Common/Rva003A5DA0Write.cpp. Carry the migrated
provider, removed helper/constants and affected consumers into the next
scheduled census; full consumer selection/loss verification remains open.
No census gain or debt retirement is claimed.
[Checks and scope](../../reverse/attempt_support/ostringstream-ctor-stlport46-20261030-codexb4.md).
