// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@QueueProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025424F, 49 bytes. Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/
// QueueProductionExitUpdateFriendNewModuleDataThunk.cpp (1281192f68; donor
// flags /DNDEBUG /MD /GX- with BFME 2's /O1 in place of /O2 /Ob2). Compiled
// that way the body places uniquely on unclaimed .text by masked whole-.text
// search (tools/donor_sweep.py).
//
// Identity is retail's own: ModuleFactory's registration at 0x00259827
// pushes "QueueProductionExitUpdate" with this data factory and the rowed
// QueueProductionExitUpdate::friend_newModuleInstance (0x0024E969). The
// factory news 0x34 bytes, runs the rowed ctor at 0x002541FA, and hands the
// parse proc at 0x0025423E to INI::initFromINIMultiProc (rowed 0x0002DEB5).
// As in Zero Hour's MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA, the
// factory is a static of the module class.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
    static void parseCoord3D(INI *, void *, void *, const void *);
    static void parseAngleReal(INI *, void *, void *, const void *);
    static void parseDurationUnsignedInt(INI *, void *, void *, const void *);
    static void parseBool(INI *, void *, void *, const void *);
    static void dup_002EF72(INI *, void *, void *, const void *);
};

class QueueProductionExitUpdateModuleData
{
public:
	QueueProductionExitUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	unsigned char m_bytes[0x34];
};

class QueueProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@QueueProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *QueueProductionExitUpdate::friend_newModuleData(INI *ini)
{
	QueueProductionExitUpdateModuleData *data = new QueueProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, QueueProductionExitUpdateModuleData::buildFieldParse);
	return (ModuleData *)data;
}

// Retail table VA 0x00BF1E48: all ten 16-byte records were read from game.dat.
// ZH's buildFieldParse provides the add(table) source pattern; target data
// supplies BFME-specific fields and offsets rather than inheriting ZH's layout.
struct FieldParse
{
    const char *name;
    void (__cdecl *parse)(INI *, void *, void *, const void *);
    const void *userData;
    unsigned offset;
};
class MultiIniFieldParse
{
public:
    void add(const FieldParse *, unsigned);
};

void QueueProductionExitUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    static const FieldParse fields[] = {
        { "UnitCreatePoint", INI::parseCoord3D, 0, 0x08 },
        { "PlacementViewAngle", INI::parseAngleReal, 0, 0x2C },
        { "NaturalRallyPoint", INI::parseCoord3D, 0, 0x14 },
        { "ExitDelay", INI::parseDurationUnsignedInt, 0, 0x20 },
        { "AllowAirborneCreation", INI::parseBool, 0, 0x24 },
        { "InitialBurst", INI::dup_002EF72, 0, 0x28 },
        { "NoExitPath", INI::parseBool, 0, 0x30 },
        { "CanRallyToSlaughter", INI::parseBool, 0, 0x31 },
        { "UseReturnToFormation", INI::parseBool, 0, 0x32 },
        { 0, 0, 0, 0 }
    };
    parse.add(fields, 0);
}
