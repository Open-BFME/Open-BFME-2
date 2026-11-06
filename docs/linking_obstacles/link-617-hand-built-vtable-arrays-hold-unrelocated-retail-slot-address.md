### LINK-617: hand-built vtable arrays hold unrelocated retail slot addresses
Status: Blocked (class identity). Updated: 2026-11-06; inspected revision: 35c0259989 (image 0a36813ed0, image_iso 35c0259989).

Evidence / affected units: `tools/image_iso.py` flags each word below as an `unrelocated_retail_address`
(`defects.tsv`, swarm packet P7b). Each constructor installs a vptr to an address-named `int`/`void *`/`char`
array whose initializer is retail's vtable as plain numbers. The bytes match retail, which loads at
0x400000 with no relocations. At our base (0x10000000) every slot points at the wrong memory, so any
virtual call through these objects jumps into garbage. The slot bodies are matched rows, but each is
rowed under a different placeholder class in another file, so no one class owns the vtable.

| Source | Array (retail VA) | Slots flagged | Slot rows (target facts) |
|---|---|---|---|
| Common/Bfme5ThirtyTwo.cpp | g_bfmeVtableCZ (0x00CE4A10, 19 slots + string bytes) | 19 | 0x68A160 BfmeThingVIH::bfmeDelVIH (BfmeConv1374.cpp), 0x7244B0 ICF twin, 16x __purecall, 0x68A130 Rva0068A130::rva0068A130 (Rva0068A130Cluster.cpp). Ctor 0x68A0E0 Gen_0081E480 here, dtor body 0x68A110 |
| Common/Rva000A217FCtor.cpp | g_00BC9020 (0x00BC9020) | 11 | GameWindow-family slots (??_GRva0008FF3E, Rva000A260AWindow::input/system, Rva000A261CWindow::draw, GameWindow::vslot6/8/9, Xfer::IsCRC twin, ...) |
| Common/Rva004F599EClear.cpp | g_00C63254 (0x00C63254) | 4 | ??_GObjectModule twin 0x4A10FD, ~Region2D twin 0xB3FD0, Rva004F59ACNamed::name, Rva004F599E::xfer |
| Common/Rva005C44A3Ctor.cpp | g_00C745D4 (0x00C745D4, char blob with trailing strings) | 4 | 0x5C4537 (rowed ??_GRva004FA830), Rva005C44DF, Rva005C44C3::getName, Rva005C4352 |
| Common/R2ZeroingConstructors.cpp | R2Data010EC784 (0x00C61CA8), R2Data01085DBC (0x00C61C30) | 2 | ??_GRva004E194E, ??_GRva004E18A2; the ledger already lists ??_7Rva004E194E and ??_7Rva003B8610Record at 0x00C61CA8 |
| Common/R3ScalarFieldConstructors1.cpp | Gen00C1F470 (0x00C1F470) | 1 | ??_GRva003B4100 |
| Common/Rva007EB310Destroy.cpp | vftable_01129CB4 (0x00CE1514) | 1 | Rva007EB310Owner::destroy (ledger: ??_7Rva007EB2C0Object) |
| GameNetwork/Rva007EBAA0Create.cpp | g_bfmeVftTDA (0x00CE157C) | 1 | Rva007EB8B0Log::setFields_007EB760 |
| GameNetwork/Rva00800920FeslCtor.cpp | vftable_0112B89C (0x00C1C780) | 1 | __purecall (ledger: ??_7SecondaryModuleBase@FXParticleSystem; data row ??_7Rva003F498ACallback) |
| GameNetwork/ServiceHubImpl.cpp | vftable_01129CB0 (0x00CE1510), vftable_01129AF4 (0x00CE1354) | 2 | ??_GGen007EB140 (ledger: ??_7ServiceHubImpl), ??_GRva00657670 |
| GameNetwork/ServiceHubImpl_ctor.cpp | vftable_011296B0 (0x00CE0F20) | 1 | ??_GBfmeMsgVJH (ledger: ??_7Rva00808CB0LanGameEntry and six more) |
| WWLib/HordeMeleeAmoeba.cpp | g_00C6FF28 (0x00C6FF28) | 1 | ??_GRva00587752Record, then 0x587F11 and 0x587217 |

ServiceHubImpl has four private class copies (ServiceHubImpl.cpp, ServiceHubImpl_ctor.cpp,
createServiceHubImpl.cpp, BuddyThreadClassThreadFunction.cpp). None is registered in canonical_classes.csv.

Completed: none of the arrays is fixed. They were checked and left as they are. Function references
cannot replace them: the slots are deleting destructors and members of other placeholder classes. No C++
spelling takes the constant address of a `??_G` or of another class's member without a hatch, and
hand-adding `/alternatename` or `object-symbol=` rows is forbidden.

Remaining / next check: for each array, reconcile the class. Give the constructor's class its real
virtual functions in retail slot order (a header via `tools/header_adopt_lane.py` where one exists),
rename the slot rows into that class with `tools/rename.py`, and let the compiler emit `??_7`, so the
vptr store relocates. Then delete the address-named array and its ledger alias. Verify with
`./build.sh` on every touched source and the next image_iso run (the words must leave `defects.tsv`).

Not pointers (left as they are):
- Huff.cpp `LZHLEncoderStat::symbolTable0`: henc.tbl packed {nBits, code} shorts (0x00B70008,
  0x00C30008, 0x00C70008).
- decodembs.cpp `defaultModeProbs`: byte probabilities (00 00 40 00).
- Two unattributed words: image RVA 0xA10ED0 is UTF-16 `L"LM"` after "Multiplayer_Human", and
  0xAD3EB4 sits in a run of int16 values (0x4D, 0x50, ...).

Clearance: pending.
Census confirmation: not claimed.
