# Army mover battle dependency audit

The WorldBuilder lead identifies LivingWorldAIArmyMover::WinTestBattle at retail 0x0059C15B, complete 1238 bytes ending at 0x0059C631. Its native call graph independently follows the two setup/simulation branches visible in the WorldBuilder body at 0x014FBC60. The return is EAX and the native method cleans seven stack words. Original parameter spellings remain unknown.

The body still requires substantive unrowed providers 0x0059BE1F (497 bytes), 0x002BC971 (843 bytes), 0x004FA3C9 (495 bytes), and destructor 0x004FA2E2 (231 bytes). Prior banks already record their independent ABI or shape blockers. No parent reconstruction or extra pin was admitted.

The suggested same-class existing home, LivingWorldAIArmyMoverDefendHomeTerritory.cpp, has a stale vector<int> return declaration for 0x00500659. The real 279-byte provider returns vector<ObjectID>; ObjectID is its existing stand-in for an unidentified four-byte enum. The proposed exact consumer correction and declaration-only use of the real 189-byte overflow provider retain the entire 331-byte existing body and all calls. All three sources pass strict preparation and normal byte verification.

The witnessed f739791d66 census (2026-10-10 15:55) and fresh scoped checks still refuse all three units: the consumer touches losing enum-vector helpers and a globally wrong-selected overflow definition, while the real providers retain their own unrelated COMDAT and selected-provider debt. The attached unchanged ordinary verdict is authoritative; neither the index nor any receipt was altered to claim closure. The consumer patch is evidence only and production Code was restored. There is no new C++ or LINK credit.
