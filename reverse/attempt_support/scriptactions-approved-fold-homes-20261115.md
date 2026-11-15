# ScriptActions approved-home fold-row check, 2026-11-15

Result: blocked before row admission. No source, ledger, TU approval, pin or fold-proof note changed.

At `a7a5f73b31b95f3e7627eca7fb7a2d15b70b2549`, the current map approves 0x001F4206 to `Code/GameEngine/Source/GameClient/System/ParticleSys.cpp` and 0x0007FAB3 to `Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp` (C). The requested aliases currently belong to `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_playerOwnershipOfTypeCounter.cpp` and already carry explicit `fold-proof=` notes. The donor holds seven rows; neither fold row was moved.

`./build.sh` on all three units passes **196/196 rows** (ParticleSys 132, W3DWater 57, donor 7), with 49 renumbered funclet pins, two STLport fold proofs, four literals plus two empty strings and ten floats verified. CSV and frozen-source checks pass. A fresh index fetched in this exact tree has SHA256 `eb2e605304fb2f7c2f9cdf2a78a87187f0c4f7a8b0f48e4f38babc30b9c63a17`, update 2026-11-15 06:58 at a7a5f73b31, census 2026-11-15 05:50 at 077f8535da.

The supported per-row verifier `rehome_rows.all_exact([row], ParticleSys.cpp)` returns false for `??1ObjectTypesTemp@@QAE@XZ`, 21 bytes at 0x001F4206. Explaining the same comparison against the existing, current build.sh object gives `ValueError: symbol not found in object: ??1ObjectTypesTemp@@QAE@XZ`. No build.compile_source call or alternate-name substitution was used. ParticleSys already matches its differently named `?rva001F4206@Rva001F4206@@QAEXXZ` at that address; those bytes do not supply the missing destructor symbol.

Per the coordinator's stop rule, the W3DWater fold-row probe and all row admissions stopped at that first failure. W3DWater's own 57 rows passed the baseline build; that is not a successful home probe for its proposed vector alias. There is no row-move commit, Sol review or publication go request. All five source/address claims were released. No Boat sandbox or merge search started; lane spend remains 122.473611/150 credit-hours.

Runtime/link clearance is not claimed. The approved homes remain unchanged. Any exclusion/flags-from change to `tools/tu_skeleton.py` belongs to toollane3, not this seat. The original ScriptActions verified plan and frozen binary patch remain intact.

Raw evidence on srv1: `~/bfme2-ops/swarm/sweeps/merge-climb/scriptactions-fold-homes/`: `build-three-baseline.log`, `approved-map.json`, `home-exact-results.json`, `mismatch-0x001F4206.json`, `objects-before.json` and the archived `objects/`, `claims-release-on-stop.json`.
