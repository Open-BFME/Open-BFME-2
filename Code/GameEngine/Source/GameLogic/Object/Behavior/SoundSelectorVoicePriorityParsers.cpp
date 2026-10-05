// cl: /O1 /DNDEBUG /MD
//
// Two more VoicePriority FieldParse procs of the shape already rowed for
// UpgradeSoundSelectorClientBehaviorModuleData::parseVoicePriority
// (0x004CB104): set the record's presence flag, then delegate the integer
// parse to the rowed INI::parseInt with the arguments unchanged.
//   0x004CBBD3 (33B) RandomSoundSelectorClientBehaviorModuleData table
//       0x00C5F318 (its buildFieldParse 0x004CBC09): VoicePriority 0x00C5F348,
//       store +0x1D8, flag +0x1DC.
//   0x004CAB3D (33B) table 0x00C5F114 read by the unrowed sound-state parse
//       0x004CB047: VoicePriority 0x00C5F124, store +0x218, flag +0x21C. The
//       record's owner is unproven, so the name stays address-derived.

class INI
{
public:
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004CAB3D_ParseVoicePriority(INI *ini, void *instance, void *store, const void *userData);
};

class RandomSoundSelectorClientBehaviorModuleData
{
public:
	static void parseVoicePriority(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_000[0x1D8];
	int m_voicePriority;		// +0x1D8
	bool m_voicePresent;		// +0x1DC
};

struct Rva004CAB3DSoundState
{
	unsigned char m_unreconstructed_000[0x218];
	int m_voicePriority;		// +0x218
	bool m_voicePresent;		// +0x21C
};

// ?parseVoicePriority@RandomSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void RandomSoundSelectorClientBehaviorModuleData::parseVoicePriority(INI *ini, void *instance, void *store, const void *userData)
{
	((RandomSoundSelectorClientBehaviorModuleData *)instance)->m_voicePresent = true;
	INI::parseInt(ini, instance, store, userData);
}

// ?Rva004CAB3D_ParseVoicePriority@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004CAB3D_ParseVoicePriority(INI *ini, void *instance, void *store, const void *userData)
{
	((Rva004CAB3DSoundState *)instance)->m_voicePresent = true;
	INI::parseInt(ini, instance, store, userData);
}
