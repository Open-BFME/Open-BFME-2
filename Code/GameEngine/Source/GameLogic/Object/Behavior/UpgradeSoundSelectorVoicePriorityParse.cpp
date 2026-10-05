// cl: /O1 /DNDEBUG /MD
//
// ?parseVoicePriority@UpgradeSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z,
// retail 0x004CB104, 33 bytes. VoicePriority INI parse callback for
// UpgradeSoundSelector entries (table 0x00C5F1F0 record 0x00C5F210, offset
// 0x37C). Sets the entry presence flag at +0x380 then delegates the integer
// parse to rowed INI::parseInt 0x0002EF56 (store = entry+0x37C).
//
// Identity/layout/provenance (target evidence, not bytes alone):
// - Field table at RVA 0x85F1F0 (VA 0x00C5F1F0): record at 0x85F210 carries
//   token "VoicePriority", proc VA 0x008CB104 (this body), userdata 0,
//   offset 0x37C. Table stride 16B (FieldParse { token, proc, userdata,
//   offset }); terminator at 0x85F240 (null record). Dumped from game.dat.
// - Record stride 0x384 proven by consumer 0x004CB51C (matched slot 2 in
//   UpgradeSoundSelectorClientBehaviorSlot2.cpp): loop adds 0x384 per entry
//   over [begin,end) at ModuleData +0x08/+0x0C.
// - Layout int at +0x37C / bool at +0x380 proven both by this body (mov byte
//   [eax+0x380],1 + forward to parseInt which stores int at store) and by
//   consumer 0x004CB51C (copies [esi+0x37C] to out, tests [esi+0x380]).
// - Dispatch ABI: __cdecl (INI*, void* instance, void* store, const void*
//   userData) forwarding all four to parseInt; caller 0x004CB638 builds the
//   MultiIniFieldParse with this table via rowed add 0x0002BC6E then
//   initFromINIMulti RVA 0x0002D7A8. No EH, no frame, add esp,0x10.
// - Reference-first: ZH/GeneralsMD has no UpgradeSoundSelector (BFME-only
//   family) and no VoicePriority source; BFME1 game source has no
//   VoicePriority parser (narrow grep clean). Nearest transferable pattern
//   is the push-order + delegate shape of rowed WeaponSet siblings
//   (parsePreferredAgainst 0x002C8C7B family) and BFME1 TurretAI
//   parseTurretSweep repair note (Real* at +0x10). This body is
//   target-evidence reconstruction, not a donor copy.

class INI
{
public:
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

struct UpgradeSoundSelectorEntry
{
	unsigned char m_pad000[0x37C];
	int m_voicePriority; // +0x37C (store = entry+0x37C via table offset)
	bool m_voicePresent; // +0x380
	unsigned char m_pad381[0x384 - 0x381];
};

class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	static void parseVoicePriority(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseVoicePriority@UpgradeSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z @0x004CB104
void UpgradeSoundSelectorClientBehaviorModuleData::parseVoicePriority(INI *ini, void *instance, void *store, const void *userData)
{
	((UpgradeSoundSelectorEntry *)instance)->m_voicePresent = true;
	INI::parseInt(ini, instance, store, userData);
}
