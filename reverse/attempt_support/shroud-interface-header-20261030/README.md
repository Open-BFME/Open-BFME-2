# Object shroud query interface, 2026-10-30

This establishes a shared **compatibility interface**, not a recovered original
class name, source header or complete inheritance hierarchy. All three query
units adopt it through `header_adopt_lane.py run --generate --apply`; the
generated header also has a forward declaration and explicit scope comments.
There were no existing ObjectShroudClient header-queue keys to retire.

## Target facts

Object's constructor at RVA 00298EA9 places the interface receiver at +64 and
installs table 007FC2D8. Its six entries target 00290EE0, 000B3FD0, 00290EFE,
002941EA, 0028E5E0 and 0028E775. The query methods occupy slots 3, 4 and 5,
not slots 0 or 1 as the previous private views claimed. Slot 1 is an empty
folded body; its original name and return type remain unknown. Its protected
opaque declaration is never called or defined by these views.

Object+68 is a **vbptr**, not another interface's vfptr. It points to table
007FC320 containing signed displacements -4 and +46C, reaching the virtual
base at Object+4D4. The existing 0028AADF constructor and Object lifetime
units already model virtual inheritance; they are unchanged. This corrects
the 2026-10-29 obstacle's mistaken +68 explanation and complete-size inference.

## Structural representation and verification

The four-byte shared interface describes only the six-slot primary surface.
Each query TU uses an eight-byte partial storage wrapper: that interface plus
four bytes reserving the observed vbptr. The receiver stays at Object+64 and
Partition stays at +6C. These units construct no object, perform no virtual-base
conversion and access no vbtable. Their local Object declarations remain
partial views; the separate Partition slot declaration is not repaired here.

Private original/corrected probes verify all five ledger bodies against retail
and preserve all ten external code definitions and their symbolic relocations.
The actual adopted objects must reproduce those definitions as well. Native
table bytes, constructor/destructor instructions, source hashes and actual
object comparisons are in `proof.json`; the original private-probe results are
in `private-probes.json`.

Strict preparation verifies five rows and seven compiler float literals.
The bounded link prediction conserves 1,622 bytes across all three units
(212 + 405 + 1,005). This is header/ABI cleanup, not a claimed linking gain.
No body, ledger identity, pin, hatch, data owner or source path is added/moved.
The contract's `bytes` slot labels report the compiler's consistent declarations;
independent retail evidence for their ordering is recorded separately here.

## Remaining work

Reconcile the full Object base hierarchy and the inferred BfmeCtor001B3A20
identity before sharing lifetime declarations. Recover the empty slot's original
signature and Partition's seven preceding slots. This header must not be used
as proof of a complete original four-byte base or for virtual-base operations.
The broader outgoing-batch audit remains qualified by the available census
index; only a new census can establish a headline change.
