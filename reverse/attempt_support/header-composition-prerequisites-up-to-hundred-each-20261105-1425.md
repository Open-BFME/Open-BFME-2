# Header composition prerequisites from restored trials

The trial replaces only the selected private declaration. The resulting source was rejected
by the normal verifier. Every modified source was restored and its normal build passed.

Trial base: `a31785a66f2fbd1b89c5bbc2271d9876fc6ddde8`.
InGameHeroSelectInterface: the outer declaration is token-identical, but the header also defines
the nested Impl class. The selected units retain their own Impl views. Including the header
produces duplicate members (C2535). Reconcile the complete nested view before adopting it.

- `Code/GameEngine/Source/Common/Rva0052557EPlay.cpp`: after-build-left.
- `Code/GameEngine/Source/Common/Rva005255E2SetFaction.cpp`: after-build-right-left.
- `Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/InGameHeroSelectInterfaceShowSelectAllHeroesBttn.cpp`: after-build-right-right.

Trial base: `a31785a66f2fbd1b89c5bbc2271d9876fc6ddde8`.
Coord3DBase: the identical storage declaration is coupled to the header’s Coord3D include.
Coord3DCopy.cpp needs the existing rva006016AC member and class-key migration.
DeflectSpecialPower.cpp loses the existing PBVCoord3D onCollide spelling in the object;
prove and coordinate the class-key/provider migration before retrying.
The previously refused coord3d_crossproduct.cpp trial was skipped before any edit.

- `Code/Libraries/Source/WWVegas/WWMath/coord3d_crossproduct.cpp`: before-proof.
- `Code/GameEngine/Source/Common/Coord3DCopy.cpp`: after-build-left.
- `Code/GameEngine/Source/GameLogic/Object/SpecialPower/DeflectSpecialPower.cpp`: after-build-right.

The restored normal gates verify 7/7 rows in the three hero-selection sources and 18/18
in the two Coord3DBase trials. No provider, ledger, header or source changes from these
trials are retained. The corresponding before, rejected candidate and restore logs live
under build/up-to-hundred-each-20261105-1425/ in this checkout.

