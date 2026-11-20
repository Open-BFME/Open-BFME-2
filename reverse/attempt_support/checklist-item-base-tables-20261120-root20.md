# StrategicHUD checklist item tables and second base

The item lifetime at 0x0057A2B0 now shares the existing native
Rva005D40A6 declaration with its owning constructor/destructor unit.
The second base begins at +8, has a 0x40-byte extent and keeps the
observer at complete-object offset +0x54. The old local view used
0x2C bytes for the base and a longer pad before the observer.

The canonical header uses the provider's complete member types and
five virtual declarations. The provider retains all 59 COMDAT
fingerprints, its reference graph and all five table relocations.
The build matched 227 function rows and two data rows across the five
prior header consumers and the two lifetime units. All 16 EH graphs
were exact. The seven-source preview retained 11,482 linked bytes
against census 179f73d302. The owning adoption tool retired the two
corresponding header queue rows.

## Native table identities

| Address | Retail shape |
| --- | --- |
| 0x00842518 | 52 bytes. Thirteen entries to __purecall. Shared by three base spellings. |
| 0x0086EEF8 | 20 bytes. 0x0057A44D adjustor followed by 0x0057B328, 0x0057A31B, 0x0057A330 and 0x0057A345. |
| 0x0086EF0C | 52 bytes. 0x0057B383, 0x002E067D, 0x0057A35A, 0x0057A362, 0x003F3FCE, 0x0057A471, 0x0057A36A, 0x0057A372, 0x00094AD8, 0x0057A4A3, 0x0057A4BA, 0x0057AD26 and 0x0057A37A. |

The dtor stores both derived tables, calls the observer at slot +0x18
and destroys the second base, then restores 0x00842518. The rowed
StrategicHUD::ChecklistUIImpl::Item ctor at 0x0057A748 installs the same
two table addresses and its separate inline dtor matches the 84-byte
body outside the same seven relocation fields. Slot 0 of the primary
table is the checklist deletion operation at 0x0057B383. The deleting
destructor adjustor is in the secondary table.

The pure-virtual destructor scratch variant passed all eight current
rows and emitted thirteen __purecall relocations in the base. It
left the deleting wrapper in slot 0 of the derived primary table.
The nonvirtual variant emitted a primary table without a deleting
wrapper and preserved the raw seven-byte first-base destructor and
its vtable relocation. It matched six rows under the current ledger.
The old UAE spelling and the EH cleanup bound to it account for the two
misses. The owning function respell rejected the special member.

Keep the folded setter and both existing first-base destructor owners
at 0x0057A23C during any ABI correction. It also has a consistent
generated pin. The two base constructors at 0x005F6871 and 0x005D1A6C
share a table but have distinct bodies. The latter zeroes +4 and the
Item ctor calls it. The registered Rva005D1A6C header still declares
one virtual destructor. SpawnBehaviorInterface already emits thirteen
pure slots in its constructor unit.

The next table work needs an owning nonvirtual lifetime transition and
the existing matched overrides in the Checklist Item facets. The
thirteen primary and four remaining secondary bodies already have rows.
The currently held bridge states require a fresh authoritative link.
