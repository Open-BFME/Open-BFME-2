// cl: /O1 /DNDEBUG /MD /GX-
// Emotion threat-threshold parsers (retail 0x004DC64F 37 bytes and
// 0x004DC625 42 bytes). Both parse an int through the rowed dup_002EF72 at
// 0x002EF72 into a stack temp (instance and userData 0). The Above form
// stores {-1, value} (or-store, retail's 83 08 FF); the Below form stores
// {1, -value} (negated temp). Each body serves two table entries of the
// Emotion table at 0x861310 (Above: OnlyIfEnemyThreatAbove at +0x1C and
// OnlyIfFriendThreatAbove at +0x24; Below: the corresponding Below pair).
// The callback names stay address-derived; the owning struct is BFME2-new
// (no BFME1 donor).

class INI
{
public:
	static void dup_002EF72(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004DC64F_ParseThreatAbove(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004DC625_ParseThreatBelow(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva004DC64F_ParseThreatAbove@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004DC64F_ParseThreatAbove(INI *ini, void *instance, void *store, const void *userData)
{
	int value;
	INI::dup_002EF72(ini, 0, &value, 0);
	((int *)store)[0] |= -1;
	((int *)store)[1] = value;
}

// ?Rva004DC625_ParseThreatBelow@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004DC625_ParseThreatBelow(INI *ini, void *instance, void *store, const void *userData)
{
	int value;
	INI::dup_002EF72(ini, 0, &value, 0);
	value = -value;
	((int *)store)[0] = 1;
	((int *)store)[1] = value;
}
