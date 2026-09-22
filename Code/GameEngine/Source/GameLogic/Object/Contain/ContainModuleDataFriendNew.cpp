// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Contain modules. Each one's identity is
// ModuleFactory's addModule registration, which pushes the module name with
// this factory. Every factory news its data class, runs the declared-only ctor
// and passes the class parse proc to INI::initFromINIMultiProc; both callees
// are pinned at the addresses the retail factory calls and pushes.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class HealContainModuleData
{
public:
	HealContainModuleData();
	virtual ~HealContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x9C - 4];
};

// ?friend_newModuleData@HealContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HealContainModuleData::friend_newModuleData(INI *ini)
{
	HealContainModuleData *data = new HealContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HealContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class HordeContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x274 - 4];
};

// ?friend_newModuleData@HordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeContainModuleData::friend_newModuleData(INI *ini)
{
	HordeContainModuleData *data = new HordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HordeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class AODHordeContainModuleData
{
public:
	AODHordeContainModuleData();
	virtual ~AODHordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x2BC - 4];
};

// ?friend_newModuleData@AODHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AODHordeContainModuleData::friend_newModuleData(INI *ini)
{
	AODHordeContainModuleData *data = new AODHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AODHordeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class TransportContainModuleData
{
public:
	TransportContainModuleData();
	virtual ~TransportContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18C - 4];
};

// ?friend_newModuleData@TransportContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TransportContainModuleData::friend_newModuleData(INI *ini)
{
	TransportContainModuleData *data = new TransportContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TransportContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SiegeEngineContainModuleData
{
public:
	SiegeEngineContainModuleData();
	virtual ~SiegeEngineContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1B8 - 4];
};

// ?friend_newModuleData@SiegeEngineContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeEngineContainModuleData::friend_newModuleData(INI *ini)
{
	SiegeEngineContainModuleData *data = new SiegeEngineContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SiegeEngineContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class HordeSiegeEngineContainModuleData
{
public:
	HordeSiegeEngineContainModuleData();
	virtual ~HordeSiegeEngineContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1B4 - 4];
};

// ?friend_newModuleData@HordeSiegeEngineContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeSiegeEngineContainModuleData::friend_newModuleData(INI *ini)
{
	HordeSiegeEngineContainModuleData *data = new HordeSiegeEngineContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HordeSiegeEngineContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class TunnelContainModuleData
{
public:
	TunnelContainModuleData();
	virtual ~TunnelContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD8 - 4];
};

// ?friend_newModuleData@TunnelContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TunnelContainModuleData::friend_newModuleData(INI *ini)
{
	TunnelContainModuleData *data = new TunnelContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TunnelContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class HordeTransportContainModuleData
{
public:
	HordeTransportContainModuleData();
	virtual ~HordeTransportContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18C - 4];
};

// ?friend_newModuleData@HordeTransportContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeTransportContainModuleData::friend_newModuleData(INI *ini)
{
	HordeTransportContainModuleData *data = new HordeTransportContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HordeTransportContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class RiderChangeContainModuleData
{
public:
	RiderChangeContainModuleData();
	virtual ~RiderChangeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x284 - 4];
};

// ?friend_newModuleData@RiderChangeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RiderChangeContainModuleData::friend_newModuleData(INI *ini)
{
	RiderChangeContainModuleData *data = new RiderChangeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RiderChangeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SlaughterHordeContainModuleData
{
public:
	SlaughterHordeContainModuleData();
	virtual ~SlaughterHordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xEC - 4];
};

// ?friend_newModuleData@SlaughterHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlaughterHordeContainModuleData::friend_newModuleData(INI *ini)
{
	SlaughterHordeContainModuleData *data = new SlaughterHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SlaughterHordeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class CitadelSlaughterHordeContainModuleData
{
public:
	CitadelSlaughterHordeContainModuleData();
	virtual ~CitadelSlaughterHordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x110 - 4];
};

// ?friend_newModuleData@CitadelSlaughterHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CitadelSlaughterHordeContainModuleData::friend_newModuleData(INI *ini)
{
	CitadelSlaughterHordeContainModuleData *data = new CitadelSlaughterHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CitadelSlaughterHordeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ProductionQueueHordeContainModuleData
{
public:
	ProductionQueueHordeContainModuleData();
	virtual ~ProductionQueueHordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE0 - 4];
};

// ?friend_newModuleData@ProductionQueueHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ProductionQueueHordeContainModuleData::friend_newModuleData(INI *ini)
{
	ProductionQueueHordeContainModuleData *data = new ProductionQueueHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ProductionQueueHordeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
