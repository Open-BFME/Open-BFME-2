### LINK-616: `TheFXParticleEditor` defined with the loading constructor threw from a static initializer
Status: Repair landed / awaiting verification. Updated: 2026-11-06; inspected revision: 90e709c42b.
Evidence / affected units: diagnostic image from the P5 test branch (`28a2888789`, with the Link
lane's vtable bridge), receipt `2026-11-06T031429Z-boot_smoke-dbd104ed16ab`: second-chance C++
exception 0xe06d7363 (`boot_smoke.py` reports `crash` only for second chance) from
`DllHandle::DllHandle` (0x00204230) calling `LoadLibraryA("FXParticleEditorI.dll")`, reached from
`ScriptEngine_init.obj`'s `_$E1` via the loading constructor `BfmeDualVtableReleaseDtor(int)`
(0x0020429D). The retail game folder has no `FXParticleEditorI.dll`. `ScriptEngine_init.cpp`
defined `BfmeDualVtableReleaseDtor TheFXParticleEditor(0);` (from `03f6b48e19`). Retail's
initializer for the global (0x007AD7DD, table index 251; rowed as `rva007AD7DD` in
`Rva007AB81ACtorInits_Rva007ACC20.cpp`) calls the default constructor 0x00203618, which loads
nothing; only `ScriptEngine::init` builds a loading temporary inside try/catch. The image ran
both the bridged 0x007AD7DD (entry 140) and the throwing `_$E1` (entry 1,432). Retail's own
boot under the same harness logs 2 quiet first-chance exceptions and no second chance.
Completed: `ScriptEngine_init.cpp` declares the default constructor and defines the global with
it; `_$E1` is now 0x007AD7DD's shape (default constructor, `atexit`). `./build.sh` 4/4. Branch
test with the bridge (run 42156813405, receipt `2026-11-06T041525Z-boot_smoke-a9f9d6f34077`) gets
past every static initializer to `GameEngine::GameEngine` in `WinMain`.
Remaining / next check: the global is still constructed twice in a bridged image (bridged
0x007AD7DD and the unit's `_$E1`); harmless, since the default state holds no library, and it
ends when the bridge stops bridging 0x007AD7DD once a native registration covers it.
Clearance: pending a master receipt with this fix and the bridge.
Census confirmation: not claimed.
