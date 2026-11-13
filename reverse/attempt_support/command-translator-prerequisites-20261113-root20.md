# Remaining CommandTranslator cohort prerequisites

The claimed cohort comprises Common/Rva00428EEBIssueFireWeapon.cpp, GameClient/GameClientDrawableTOC.cpp and GameClient/MessageStream/CommandXlat.cpp. Ordinary checks pass 147/147 rows. The separate shared-view change removes the GameInfo/RecorderClass private declarations, integrates canonical UnicodeString, makes the existing SubsystemInterface dependency explicit and retires five owning queue rows. Everything below remains queued; no failed trial is applied.

## Primary class

The frozen CommandTranslator header is a fieldless, nonvirtual three-method view. Native constructor RVA4296C2 installs table83C6AC and initializes storage through+2C; GameClient allocates30bytes. The table has translateGameMessage42B0DE and deleting destructor4296EE. Destructor429191 restores base GameMessageTranslator's table7DBA74. The two full consumers already model this inheritance/lifetime, and the common command source reads team state at+8.

Ordinary adoption refuses Common because the header lacks rva00428EEB and other defined methods; DrawableTOC because it lacks the nested CommandEvaluateType, construction and base conversion surface. CommandXlat also encounters an unresolved osdep.h include in the conservative field-analysis closure. This requires an evidenced full header/API contract, including current already-adopted consumers; adding a local data projection or preserving another private full class is not a repair.

## Other inspected views

Every unique queued pair in the three files was preflighted. Prepared candidates used the ordinary adopter; failures restored their source. Machine evidence preserves exact diagnostics and held scopes. Principal prerequisites are:

- Missing APIs: AnimationSoundModuleManager::init, AudioManager::addAudioEventInfo, BfmeAptWindowManager::vf14, LanguageFilter::init, Thing::isKindOf, and GameWindowTransitionsHandler's distinct rva001DC5EC wait routine and inherited reset. Do not substitute isFinished for the wait.
- Data/layout: Display's base prefix; Drawable's shroud counter; GameClient's drawable-hash element identity; FrustumClass's byte-array versus Matrix3D representation; ParticleSystemManager's local-player field; PlayerTemplate's beacon at+E4 versus canonical+17C; StatsCollector's counters+10/+14; and Rva002390CB's incompatible member type.
- Byte failures: Mouse adoption changes GameClient::init; SphereClass and Vector3 adoption change PlaneClass::In_Front. The existing matching views remain intact.
- Conditional include proof: GlobalData/Shell reach unresolved Unix pthread.h and CommandTranslator reaches the osdep.h branch. No include allowlist or compiler-setting guess was added.
- MiscAudio's native+F0 handle matches its shared field. The earlier CommandButton name collision is gone, but the guard cannot prove ownership through TheAudio->getMiscAudio()->special. A const typed local plus handle reference compiles but matches only7/9 common-source rows: issueSpecialPowerCommand and its cleanup differ. Native argument staging pushes0 before the virtual call at byte displacement138h (slot78). No wrapper, manual field rename or artificial argument staging was used; the original expression remains.
- Drawable and FreelistPool had foreign logical claims and were not edited. FreelistPool already includes its shared header, but its queue row was not retired under another worker's scope.
- UserPreferences no longer has a private source body or a spelled use, but ordinary acceptance still refuses the missing direct shared-header relationship. No unused include was added merely to retire the row. SubsystemInterface's active transitive relationship was instead made explicit after MessageStream.h and passed ordinary acceptance.

## Existing shadow identity findings

The verified source commit reports eight shadow keys. Saved complete pre-change objects establish all eight are unchanged: three GameClient binding rows ($L13380/$L13914 hash-map cleanup and the constructor's list-base call) have identical bounded body digests and external relocation lists; five divergent COMDAT definitions retain identical fingerprints. No baseline or whitelist changed. The native template helpers added by canonical Unicode are reviewed separately in the source-change evidence and are unrelated to those eight keys.

Native source commit `616ae61b38e` passes138/138 changed-source rows and15EXACT EH graphs. Strict reusable provider receipts pass; whole-link closure remains unchecked. Latest completed authoritative run43449493373 at c9d82e95 remains38unresolved,0duplicates,noimage,468initializer bridges and3331vtable bridges/50310slots. The extra unsigned/void* tree-constructor unresolved source is unchanged and foreign-held by ancalgonn-swarm-seat6; stale old provider objects are not repair evidence.

[Exact attempts, current queue scope and shadow comparison](command-translator-prerequisites-20261113-root20/proof.json). The MiscAudio scratch text is diagnostic evidence only. t=65min model=gpt-6.1-sol.
