# Apt name-entry unit: remove unused Laser donor methods

Base: 81510a474f. Seat: halilkkaya-codex.

Remove four unrowed Zero Hour methods: updateStartPos, updateEndPos,
setDecayFrames and the seven-argument initLaser. The index and current source
search find no outside call under these exact spellings. The actual native
four-argument initLaser is already recovered at 36355C in the GameLogic
LaserUpdate TU and is untouched.

The unit retains all eleven rows, including the 32-byte constructor currently
named ClientUpdateModule, the native Apt constructor and its funclets. All
587 common external COMDAT fingerprints are identical; 35 obsolete definitions
disappear and no external definition is added. No outside reference loses its
last provider in the dated index audit. No flag, header, pin, ledger identity
or source path changes.

These three original artifact undefined names disappear from this consumer:

- ParticleSystemManager::createParticleSystem(ParticleSystemTemplate const*,bool)
- ParticleSystemManager::findParticleSystem(ParticleSystemID)
- Object::getShroudedStatus(int) const

Three unresolved base-view names remain: Rva006DCD20's destructor, crc and
xfer. They come from the preserved constructor/virtual context. The native
32-byte constructor calls 6DCD20 and installs CE8BA0, a fifteen-slot Apt table
beginning AddRef/Release; the source still uses a renamed DrawableModule/
Snapshot hierarchy. Correct the complete constructor/base/table identity
cohort before deleting that context. This patch does not claim that the old
ClientUpdateModule spelling is a native Apt class.

Normal verification passes 29 function rows across AptValueNameEntry,
AptValueConstructorBFME2 and the actual LaserUpdate. The Apt parent has one
EXACT EH graph. Scoped DIR32 checks 29 rows and 35 current witnesses (209
symbols), without new or whitelisted conflicts. find_declared_unmatched is
clean. True source-restored base/tip previews retain both linking peers
unchanged while this consumer stays blocked, with unresolveds reduced six
to three. The index is 984a4cdc4d, November 2 08:35; no current whole-image,
census-linked or runtime gain is claimed. Logs: build/seat-link/apt-nameentry/.
