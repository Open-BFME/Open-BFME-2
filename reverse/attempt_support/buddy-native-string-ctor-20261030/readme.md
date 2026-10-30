# BuddyThread native string constructor, 2026-10-30

Base `89295774fff397085f32363ee64d1bc0e216ba21`, reference
`1d5131d3f193cdf01a99da66ccd6828639585650`, index `12b9e7a7c0` (10:11).

The complete 220-byte BuddyThreadClass constructor at 0x00550F01 already
calls the rowed narrow-string default constructor at 0x00007850 for its five
string members. Its unnecessary local constructor copy emitted an allocator
proxy that conflicted with the existing narrow-ios-imbue provider. A
declaration-only specialization uses the native constructor directly and
suppresses that instantiation chain. No layouts, identities or call targets
are changed; no pins, rows or hatches are added.

All 17 retained Buddy COMDAT fingerprints are unchanged; 11 helper copies
are removed, with no additions. Every removed name has another provider in
the published index. The constructor owner and allocator-proxy provider are
included in the ordinary paired verification, rather than assumed from that
older index. All 23 rows across Buddy, the native string constructor,
narrow-ios-imbue and BuddyThreadStartThread pass. Four EH graphs are EXACT,
the frozen-source check passes, and four strict object receipts match their
raw object hashes. Two legacy receipts without object hashes were discarded
with their generated objects and rebuilt through normal strict preparation;
the repeated link and EH checks preserve the result.

The bounded live preview improves from 3/4 to 4/4 linking units, 540 to 770
authored bytes: Buddy gains 230 preview bytes, while the three support units
retain their 540 bytes. This is a preview, not a new census measurement.

The staged outgoing audit is INCONCLUSIVE on the older index and affected
consumer Common/0CreateAHeroManager21FE49.cpp without a current strict receipt.
Carry the constructor, removed helper copies, existing constructor/proxy
providers and affected consumers into the next scheduled census; no full
consumer-closure claim is made. LINK-140's other migration work remains open.

Local logs are under `build/buddy-live-20261030/`. The narrower allocator-only
declaration trial also passed, but changed an unrowed constructor copy; the
chosen declaration preserves all retained copies instead. Durable
[object and verification evidence](proof.json) accompanies this handoff.
No link cycle, nightly measurement or smoke runner was started.
