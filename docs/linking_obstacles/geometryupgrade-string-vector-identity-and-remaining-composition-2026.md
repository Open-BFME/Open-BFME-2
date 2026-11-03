### GeometryUpgrade string-vector identity and remaining composition (2026-10-30)

At base `6d6ae2f4d537`, the constructor donor's integer-vector views are
corrected to the existing parser/destructor-supported AsciiString vectors at
`+0x118/+0x124`. The full 131-byte constructor body is unchanged; two callee
spellings retain native target `0x00211E58`. The seed and behavior-destructor
objects are unchanged; all 72 scoped bindings retain their native targets.
Strict six-source checks pass 101 code rows, 60 data rows and seven EXACT EH
graphs. The three claimed units and two existing vector providers retain
LINKS/1,935 authored bytes against `ccafe54d1d`; no census gain is claimed.

The supported merge still accepts no donor: module-data constructor C2600
(missing declaration in the seed view), behavior destructor bytes. The
Snapshot/opaque versus address-derived base and behavior vtable/view
prerequisites remain; the mixed getter source is untouched. No move is applied.
The table consumer separately fails on two INI parser names; the original
constructor reproduces the identical failure. The batch audit is INCONCLUSIVE
on its older index and missing current CreateAHeroManager receipt. Carry the
removed integer helpers, corrected constructor/providers and parser-table
consumer into the next scheduled census; full consumer selection/loss checks
remain unverified.
[Target evidence, controls and remaining scope](../../reverse/attempt_support/geometry-upgrade-string-vectors-20261030-bce2/README.md).
