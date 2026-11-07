### LINK-073: LivingWorldManager constructor uses opaque names for existing container and lifetime owners

Status: Blocked on constructor-class and member-type reconciliation. Updated: 2026-10-26; inspected revision: `2a45addda1806342ac5c52757f63be902dcd428e`.

Evidence / affected unit: `LivingWorld/LivingWorldManagerCtor.cpp` remains U5 against `d1f046749a`. Native calls reach the existing 31-byte `hash_map<int,Rva00213E11Element>` constructor at 0x00213E11 and 25-byte map constructor at 0x0033C432; the private member types instead reference `Rva002130CA`, `Rva00212379` and `Rva00211FA3` constructors. Its 0x0076DE66 cleanup reaches the seven-byte 0x00210CC5 setter under a destructor spelling. Native primary table slot 0 reaches the deleting destructor whose 691-byte lifetime owner is already `LivingWorldManager` at 0x00214405, while the constructor row retains `Rva0022B12DSubsystem`.

Completed: diagnosis only; all 19 assigned rows pass the byte gate. The named lifetime owner, both container providers and the setter provider remain LINKS in the same current-provider preview. Raw native calls and pin/owner lookups are in `build/c136-gui-w2/native-all.log`, `dependencies.log` and `final-all-with-providers.log`.

Remaining / next check: rename/reconcile the existing constructor row to `LivingWorldManager`, establish the actual container member types with their destructor owners, and reconcile the listener lifetime with the existing setter owner. Existing pins do not supply definitions to the census; adding another pin cannot resolve these names. No missing native body is established. Clearance: pending. Census confirmation: not claimed.


**2026-11-07 wall: the constructor's member types (swarm Link lane).** Real link `f98a8da771` still
reports `??1Rva0022B12DSubsystem@@UAE@XZ` (LivingWorldManagerCtor.cpp), and it is item 7 of LINK-627's
boot path. `rename.py class --fold Rva0022B12DSubsystem --into LivingWorldManager --dry-run` passes the
retail vftable proof and refuses only because LivingWorldManager is registered: GameEngineInit.cpp,
LivingWorldManagerCtor.cpp and SubsystemInterface.cpp must come in as `--prepared` units on the
canonical `LivingWorldManager.h` (rename.py accepts `--prepared` for a registered NEW). The prepared
constructor unit is what cannot be written yet:

- The constructor (0x00213EEF, 355 B, 17 rowed funclets and its `__ehhandler`) builds its members
  through private STL shims that exist only in LivingWorldManagerCtor.cpp: an `_STL::vector` whose
  default constructor always calls the folded `_Vector_base<GameWindow*>` constructor at 0x00211E58, and
  `_STL::hash_map` / `_STL::map` declarations whose constructors are the pinned bodies 0x00213E11 and
  0x0033C432. Those shims are what give each member's construction its exact callee and EH state.
- The canonical header cannot host them: it has 20+ consumers that include real STLport, which would
  see `_STL::vector`, `hash_map` and `map` redefined. With real STLport member types instead, each
  member's construction changes (its own `_Vector_base<T>` instantiation, inline hash/map
  construction), so the constructor body and its EH graph no longer match. The only precedent for the
  vector half is the ICF fold pins at 0x00211E58 in `symbols.csv`; pins are hatches and do nothing for
  the real link, and they would not cover the hash/map members, so they are not the route.
- LivingWorldManagerDtor.cpp compiles its own private `LivingWorldManager` view, whose third base is
  `LivingWorldObserver` (the canonical header's is `Rva00210CC5`); it defines the three
  `??_7LivingWorldManager` tables from that view. Its destructor (0x00214405) destroys the same members,
  so a full reconciliation brings the destructor unit onto the canonical header as well.

Candidate design (not tried): give the header the member types as wrapper classes that expose only
out-of-line or `dllimport __forceinline` constructors and destructors bound to the existing rows
(0x00212AEF/0x00212ED3, 0x00213E11 with 0x002130CA and 0x00212379, 0x0033C432 with 0x00211FA3, the
0x00211E58 vector base with 0x0021397C), so the STL shims stay private to the constructor unit and real
STLport consumers see only the wrappers. Then the prepared fold of the three units, then the destructor
unit's view. Claims released; nothing edited.
