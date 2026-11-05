# QueueProductionExitUpdate: canonical seed headers

Inspected base: `c17b5df8c3e0a7f9e50be56ce5c7f311b1c008a2`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdate.cpp`.

The seed imported Zero Hour's `PreRTS.h`, module hierarchy and `Coord3D`
through a large private include environment. Its approved donor files use
BFME2 views, so the prior merge attempts reported conflicting declarations.
The seed now includes the existing BFME2 `Thing`, `Coord3D`, `UpdateModule`,
`ExitInterface`, `AIUpdateInterface` and `NameKeyGenerator` headers directly.
It keeps a TU-local Queue view and the existing inline-provider anchor.

Target facts: the constructor row at `0x004A010E` and xfer row at
`0x004A0057` place the ExitInterface vptr at `+0x20` and Queue fields at
`+0x24..+0x40`. The existing canonical bases have these extents. The native
body at `0x004A0670`, currently owned by `Rva004A0670Copy.cpp`, reads Object's
AI pointer at `+0x258`, calls `Object::rva0028B511() const` with an int return,
and reads the module-data exit-delay field at `+0x20`. Those facts bound the
small views needed by the seed's existing unclaimed donor body; that body is
still marked present-unmatched and is not claimed as recovered code.

Donor facts: Zero Hour supplies the Queue callback and field spellings already
used in the seed. It does not establish the BFME2 hierarchy or these offsets.
No external donor path is claimed as a recovered BFME2 source path.

Verification:

- `./build.sh <seed>`: 9/9 matched rows, including the parent-EH-verified
  renumbered funclet at `0x0078DABF`; string, float and import checks pass.
- `find_declared_unmatched.py <seed>`: all definitions accounted for by
  existing rows/markers; no new unmatched marker.
- `class_gate.py <seed>`: pass.
- `link_check.py <seed>`: LINKS, 205 -> 205 bytes. Constructor and destructor
  previews also retain LINKS, 106 and 60 bytes respectively. The index is
  `c95fcfcfcd`, census `2026-11-05 05:17`; these are previews, not a new census.

`tu_skeleton.py --merge <seed> --dry-run` now accepts the destructor donor:
11 rows survive together under the winning compiler flags and the census
LinkGuard passes. The other six donor files remain rejected. In particular,
xfer's private view is incompatible with the composed Xfer expression,
constructor vftable declarations have different type modifiers, and the
remaining donors disagree on Object's fields/methods. The mixed module-name
getter file stays separate. The full output is reproducible by this command;
scratch output is `build/queueproductionexit-canonical-dryrun.txt`.

No pin, alias, protected-register key or ledger source was changed by this
prerequisite repair. Next: apply the verified destructor merge through
`tu_skeleton.py`; reconcile the remaining donors in separate changes.
