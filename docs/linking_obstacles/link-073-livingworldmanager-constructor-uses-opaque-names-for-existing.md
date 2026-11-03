### LINK-073: LivingWorldManager constructor uses opaque names for existing container and lifetime owners

Status: Blocked on constructor-class and member-type reconciliation. Updated: 2026-10-26; inspected revision: `2a45addda1806342ac5c52757f63be902dcd428e`.

Evidence / affected unit: `LivingWorld/LivingWorldManagerCtor.cpp` remains U5 against `d1f046749a`. Native calls reach the existing 31-byte `hash_map<int,Rva00213E11Element>` constructor at 0x00213E11 and 25-byte map constructor at 0x0033C432; the private member types instead reference `Rva002130CA`, `Rva00212379` and `Rva00211FA3` constructors. Its 0x0076DE66 cleanup reaches the seven-byte 0x00210CC5 setter under a destructor spelling. Native primary table slot 0 reaches the deleting destructor whose 691-byte lifetime owner is already `LivingWorldManager` at 0x00214405, while the constructor row retains `Rva0022B12DSubsystem`.

Completed: diagnosis only; all 19 assigned rows pass the byte gate. The named lifetime owner, both container providers and the setter provider remain LINKS in the same current-provider preview. Raw native calls and pin/owner lookups are in `build/c136-gui-w2/native-all.log`, `dependencies.log` and `final-all-with-providers.log`.

Remaining / next check: rename/reconcile the existing constructor row to `LivingWorldManager`, establish the actual container member types with their destructor owners, and reconcile the listener lifetime with the existing setter owner. Existing pins do not supply definitions to the census; adding another pin cannot resolve these names. No missing native body is established. Clearance: pending. Census confirmation: not claimed.
