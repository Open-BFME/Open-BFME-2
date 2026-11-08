# Animal AI canonical command parameters, 2026-11-08

AnimalAIUpdate.cpp now includes the existing AICommandParms header instead
of private parameter and coordinate-vector structs. Its 101-byte command
helper retains the 0xC0 stack block and the object store at +0x14. The incoming
legacy void pointer is explicitly cast to the canonical Object pointer.

Target facts and existing ownership: the parameter constructor at 0x00351BD0
and the canonical header already establish the layout. Destructor 0x001E7E9F
is owned by AICommandInterfaceAttackCommands.cpp and frees the coordinate
buffer at +0x20. Animal already emitted that same 15-byte destructor. Its
TU-local inline definition now uses the canonical coordinate-start field,
preserving that body and its direct, non-imported _free binding. DamageInfo
has no virtual or declared destructor and needs no extra teardown. No donor
path, original spelling, new function identity or new coverage is claimed.

Verification: normal build.sh passes all 15 Animal rows, including the
2,916-byte update; both explicit provider sources also pass, 17/17 total.
All five parent EH graphs across those sources are exact, including all
three Animal graphs. Frozen-source checking passes before and after.
Owning-tool acceptance retires exactly the Animal AICommandParms queue row.
Paired new-variant checking passes. Ordinary link preview preserves
LINKS/3,167 bytes against index c885072a48 (2026-11-08 19:18); prediction
does not establish a full image or a runtime result.

All 63 retained code COMDAT bodies, relocation identities, flags and selection
policies agree, as do 30 named data allocations and all undefined references.
No definition is added. The only removed definition is the 14-byte
RvaCoords destructor copy. Its two order-specific replacement providers
have current strict receipts and the same complete body, _free relocation,
flags 0x60101020 and ANY policy. Census order promotes
Common/Rva00336B23AICommand.cpp; default real-link path order already selects
Common/AICommandInterface_aiMoveToObject.cpp. The 15-byte parameter destructor
emitted by Animal also verifies directly against its existing native row.
final-proof.json records the hashes, provider facts and boundaries.

The AICommandInterface, AIUpdateInterface and complete AnimalAIUpdate
header debts remain. Their secondary-receiver, hierarchy and constructor
contracts must be reconciled before source consolidation. No shared header,
row, source path, pin, alias or escape hatch changes in this package.

Published as 2058c08f50 on push.py attempt 3 (28.7 seconds for the
successful attempt). The first two lost races cost 33.5 and 27.8 seconds;
normal passed receipts were reused on retries. Required row, string,
float, import, EH, converged-data and scoped DIR32 checks pass. The broader
link audit remains INCONCLUSIVE: index c885072a48 versus outgoing base
0df57cd0463995f43ad7d3c8a644bba93732a988; Animal lacked a current strict
receipt after rebase. The pre-publication provider proof remains evidence
for its recorded source hash, not a full current-image clearance.
