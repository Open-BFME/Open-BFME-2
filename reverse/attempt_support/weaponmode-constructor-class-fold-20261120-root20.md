# WeaponModeSpecialPowerUpdate constructor and destructor ownership

Inspected 2026-11-20 at `8123445bc09`. The constructor at `0x00494B38` and the destructor at `0x00494A97` install the same five vtables at offsets `0`, `0x0C`, `0x10`, `0x20` and `0x24`. The prepared `rename.py class --fold` reconciles the two 60-byte declarations in `WeaponModeSpecialPowerUpdate.cpp` and carries the destructor pair, `xfer` and two getters to `WeaponModeSpecialPowerUpdate`. All five rows retain their addresses, sizes and source files.

The constructor declaration uses the existing out-of-line destructor. Its previous 5-byte implicit destructor disappears from its object, leaving an external reference to the 39-byte rowed provider in `OpaqueScalarDeletingDtors.cpp`. The constructor still emits the same 28-byte deleting thunk with identical relocations and COMDAT selection. The primary table still has 48 bytes and its slot 0 uses the same compiler weak alias to that thunk. The independently inspected SiegeDeploy table reference keeps an exact provider.

The final seven-source build passes 105/105 rows with strict provider receipts and two exact exception graphs. The naming transaction also verified 8,907/8,907 rows and 204 data rows across 564 dependent sources.

| Offset | Table RVA | Retail slots | Remaining prerequisite |
| --- | --- | --- | --- |
| `0` | `0x0084EA54` | 13 | Canonical parent, existing Snapshot provider bindings and the UpdateModule phase slot |
| `0x0C` | `0x0084E998` | 47 | Resolve parent overrides at slots 8, 25 and 43 and inherit the canonical slot 9 provider |
| `0x10` | `0x0084E988` | 3 | Canonical UpdateModule ancestry. All three body providers exist |
| `0x20` | `0x0084E964` | 9 | Canonical `SpecialPowerUpdateInterface` and callback ownership |
| `0x24` | `0x0084E900` | 25 | Canonical `SpecialPowerModuleInterface` parent provider bindings, then the derived overrides at 19 and 20 |

The parent fold `Rva00589079` into `WeaponModeSpecialPowerUpdateBase` refuses duplicate declarations in `SiegeDeploySpecialPower.cpp`. The current compiler records agree on size and field offsets but identify different direct bases at `+0x20` and `+0x24`. Reconcile those views against the registered interfaces before retrying that fold. The served pass test remains open until a later published real link clears all five tables.

## Constructor Update interface

The constructor now inherits the existing `UpdateModule` interface and its fields at `+0x14` through `+0x1C`. Its `+0x10` table has 12 bytes and all three retail targets at `0x00494C18`, `0x00253376` and `0x0044DF8D`. Its wake call uses the existing `UpdateModule` row at `0x0044DF71`. Both constructor rows and its EH graph remain exact.

The destructor still emits a separate one-slot table at the same retail address. Including `UpdateModule.h` in its current mixed file collides with that file's private `ObjectModule` and its emission constructor. The official split confirms that the destructor rows are approved for `WeaponModeSpecialPowerUpdate.cpp`, then refuses the inline complete destructor because it finds no separately spelled definition. The three-source adoption trial was restored and the original 75 rows passed.
