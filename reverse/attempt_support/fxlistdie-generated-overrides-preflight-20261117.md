# FXListDie generated override preflight

Served primary table 0084AD04 has twelve slots, with purecall instead of the
native loadPostProcess, name getter, xfer and module-key implementations in
slots 1-4. The constructor already includes canonical Common/FXListDie.h.
That generated header declares the destructor and onDie only; it is not a
unit-local stand-in that can be replaced by another private class.

LINK-668 already records this exact producer. Current
header_adopt_lane.base_slot_signatures still visits direct registered bases
only, dropping overrides inherited through the longer Module base chain.
The generator file is claimed by codex-root20-dock-padding-tool at this check;
BehaviorModule is held by another contributor as well. No generator, generated
header, contract or game-source edit is attempted. The normal unchanged
constructor build passes its code and reference checks.

The owning tool lane must repair the transitive override detection with its
regression coverage, then reproducibly regenerate the header and reconcile
the native slot providers. In particular the existing static module-key row
and placeholder getter/transfer owners need correct actual declarations;
adding duplicate names or a private FXListDie copy would not repair that
contract. Table/file/class scopes are released. The bridge pass test remains
open until the generated declarations and a fresh real link verify it.
