# Player one-argument donor cleanup

Base: 8e7d73b3a6. Seat: halilkkaya-codex. This closes LINK-175's donor-emission
obstacle in the stated scope; the getter's identity remains open.

The real-link artifact names Money::deposit(unsigned,bool) and
Money::withdraw(unsigned,bool). Their only calls in this unit occur in the
unrowed one-argument Zero Hour transferAssetsFromThat. Native BFME 2 has the
different, already recovered two-argument method in PlayerTransferAssets.cpp.
Current Code and index audits find no outside reference to the donor spelling.

Remove that donor body. Retain its otherwise sole getDefaultTeam emitter by
an ordinary TU-local const member pointer. That keeps the existing seven-byte
+160 getter exactly; it does not assert that this is native Player's default
team field (the canonical Player layout has a different offset). No flag,
header, pin, row, global address or source path changes.

Normal checks preserve twelve function rows and one data row. All 179 common
COMDAT fingerprints are identical. Eighteen external definitions disappear,
none is added. The three removed list<Object*> helpers have other providers;
paired selection moves from Player to the existing current pool-backed
LinearCampaignAddCarryover factory and the list-object insertion unit.

Ten-source checks pass 218 function rows and one data row, strings/floats and
imports. Sources: Player, PlayerTransferAssets, ArmySummary_LoadArmyEntry,
InGameUIIdleWorker, InGameUIUpdateFormationPreview, MoveToFormationGroupOrder,
HordeContainIface11CSlots, stlport_list_objectptr_construct,
stlport_list_objectptr_insert, LinearCampaignAddCarryover. Other-seat paths
are verified only. True base/tip A/B restores and normally builds each source
version: nine LINKS peers retain 29,415 bytes and Player adds its existing
112, giving 10/10 LINKS and 29,527 bytes. No LINKS-to-blocked transition.
Scoped DIR32 passes 218 rows and 68 current witnesses, 219 symbols without
new or whitelisted conflicts. find_declared_unmatched remains clean.

Whole real-link and census confirmation remain pending. The published index
is 984a4cdc4d (November 2 08:35); no global/runtime clearance is claimed.
Local snapshots and checks: build/seat-link/player/.

The normal commit gate reports six shadow identity diagnostics (iterator
constructor, TEST_KINDOFMASK_MULTI, TeamPrototype list begin/end, TeamsInfoRec
getNumTeams and PlayerTemplate isPlayableSide). All are retained among the179
identical common fingerprints. They remain outside the shadow register; no
identity debt was retired and this patch claims only donor/link scope.
