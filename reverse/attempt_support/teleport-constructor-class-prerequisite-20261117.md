# Teleport constructor: class/table reconciliation prerequisite

Inspected at `bf617cdf1d`, published index `abb031eedf` (2026-11-16 23:13).
No source or ledger change was retained.

The picker serves Rva00492C59Ctor.cpp, constructor RVA 0x00492C59 (49
bytes), for its unresolved `??1Rva0044EF5E@@UAE@XZ`. The constructor's
complete native extent remains matched. Its private base view has only a
virtual destructor and opaque padding; its unrowed empty derived destructor
emits 11 bytes, and its own primary table is only four bytes.

Retail teardown at 0x00492C90 is 32 bytes: it restores tables at offsets
0, 0x0C, 0x10 and 0x20, then jumps to 0x00451F45. That complete body is
already rowed as `Rva00492C90::~Rva00492C90` in Rva00451F45Derived.cpp.
The actual base teardown is rowed as `SpecialAbilityUpdate::~SpecialAbilityUpdate`
in SpecialAbilityUpdateDtor.cpp. Neither existing provider supplies the
constructor view's missing base-destructor name.

Deleting the empty destructor alone would leave the compiler generating the
same incompatible single-vptr teardown; declaring it alone would instead
leave the derived name unresolved. Merely redirecting its base call would
retain nonmatching code and the truncated primary table.

The registered TeleportSpecialAbilityUpdate factory at 0x0024DBC5 calls
this constructor, but the supported command

    python3 tools/rename.py class --fold Rva00492C59 --into TeleportSpecialAbilityUpdate --dry-run

refuses: table 0x00C4E1A8 is named only
`??_7Rva00492C59@@6B@` and
`??_7Rva00492C90@@6BRva00451F45_Root@@@`, not a Teleport table.
The existing canonical SpecialAbilityUpdate header also declares a real-name
constructor whose current implementation is still rowed under Rva0044EF5E;
LINK-514 already records that family's broader reconciliation prerequisites.

Next: reconcile the ctor/dtor views and canonical Teleport table evidence
through the supported naming/header route, preserving all four native vptr
stores and checking both providers and all affected consumers together.
Do not add an alias, manufacture another pin, or retire the unique constructor
row to hide the failure. Current link_check still reports the one missing
base-destructor name; no link or runtime improvement is claimed.
