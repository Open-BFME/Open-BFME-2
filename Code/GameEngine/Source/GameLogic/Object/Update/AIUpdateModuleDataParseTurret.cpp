// cl: /GX /DNDEBUG /MD
//
// ?parseTurret@AIUpdateModuleData@@CAXPAVINI@@PAX1PBX@Z, retail 0x002623C1
// (117B). Zero Hour's AIUpdateModuleData::parseTurret (AIUpdate.cpp) in its
// BFME 2 form: a second turret throws INIException "Only one turret to a
// customer, for now" (argument count 3) instead of INI_INVALID_DATA, and the
// TurretAIData comes from plain operator new (0x70 bytes, rowed ctor
// 0x004D7E6C, unwound on a throwing ctor) rather than its memory pool. The
// record is filled through the rowed initFromINIMultiProc with
// TurretAIData::buildFieldParse (0x004D7F9C). Target evidence: FieldParse
// rows Turret / AltTurret (0x00BF9378 / +0x10) point here. Split from the Zero
// Hour port in AIUpdate.cpp.

class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &p));
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

class TurretAIData
{
public:
	TurretAIData();
	static void buildFieldParse(MultiIniFieldParse &p);
private:
	unsigned char m_unreconstructed_00[0x70];
};

class AIUpdateModuleData
{
private:
	static void parseTurret(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseTurret@AIUpdateModuleData@@CAXPAVINI@@PAX1PBX@Z
void AIUpdateModuleData::parseTurret(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	if (*(TurretAIData **)store)
		throw INIException(3, "Only one turret to a customer, for now");

	TurretAIData *td = new TurretAIData;
	ini->initFromINIMultiProc(td, TurretAIData::buildFieldParse);
	*(TurretAIData **)store = td;
}
