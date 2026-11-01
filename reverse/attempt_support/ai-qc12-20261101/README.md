# AI: native decisions complete; canonical parent virtual surface missing

Queue5096 has one verified donor, SubsystemNameGetters3.cpp. Its row count0
is stale: current ledger owns GetSnapshotName@AI at2FEB2C/6B in that source.
Frozen check passes. The donor's one-slot private AI view is not a complete
native class. It emits no AI table; byte matching alone cannot justify using
another incomplete parent.

## All four automatic decisions resolved by hand

| Attribute | Target decision and evidence |
| --- | --- |
| inherited@0 | SubsystemInterface primary base,12bytes, ctor1B4E63 on this; primary vptrC073D0. |
| inherited@4 | Native byte flag at4 and string at8 are inside that base, not a second derived field/array. Base ctor/dtor establish them. |
| inherited@C | Four-byte Snapshot secondary base, vptrC073C0; native ctor first stores BBB554 atthis+C, then replaces with the derived table. |
| field@0 | The primary inherited vptr; opaque16/24/36-byte partial views are not additional fields. |

Extent is24hex, replacing the automatic20decimal majority: GameEngine::init
pushes24 at22F3A9, calls operator new2FDA0, then AI ctor2FEA85 at22F3BE.
Constructor167B independently establishes pathfinder10, nontrivial list14,
AIData18 and two IDs1C/20. Its114 and1D200 allocations are CHILD objects,
not the AI extent. Semantic member labels are donor facts retained from the
existing matched constructor; target offsets/lifetimes/calls are independent.

Native primary tableC073D0 has14slots, Snapshot secondaryC073C0 has4, not a
single-slot getter shape. Full raw tables and every address-selected AI/base
provider are attached. Primary overrides0/1/9/10 are2FED37/2FD7D7/2FEB3A/
2FD7DC; the other ten entries are identical to native SubsystemInterface
BD77A0. Secondary slots are deleting adjustor2FEB32, emptyB3FD0, the actual
AI name getter2FEB2C and xfer2FE799. No null/default getter is permissible.

## Real prerequisite

The registered Code/Libraries/Source/subsystem/SubsystemInterface.h exposes
only the virtual destructor. Its native table has14slots. Deriving an AI
header from that canonical surface would put reset/update in the wrong slots;
using the separate full private subsystem shim would add a noncanonical parent
view. Neither is admitted. A concrete caller-header proposal is banked with
#error outside Code; no AI header is registered and no source changes.

First establish the canonical parent's full native14-slot surface and prove
its dependent virtual-provider closure, including inherited defaults. Then
use the measured AI bases/extent/18table entries here to adopt the getter.
This blocker is class:SubsystemInterface, not unresolved AI contract attributes.
No BehaviorModuleBase/UpdateModule or other root is edited. Shared obstacle
register is claimed elsewhere; this is its proposed prerequisite entry.

Read-only baseline: getter plus existing constructor unit30/30rows and1data row pass. Existing constructor AI tables are recorded separately and retain their full legacy parent surface; no constructor or getter is modified here. Native default-target representatives are attached even where several unrelated classes share the same short body.
