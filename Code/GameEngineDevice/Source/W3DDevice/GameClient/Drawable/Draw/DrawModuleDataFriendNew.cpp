// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Draw modules. Each one's identity is
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

class W3DHordeModelDrawModuleData
{
public:
	W3DHordeModelDrawModuleData();
	virtual ~W3DHordeModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C4 - 4];
};

// ?friend_newModuleData@W3DHordeModelDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DHordeModelDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DHordeModelDrawModuleData *data = new W3DHordeModelDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DHordeModelDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DTreeDrawModuleData
{
public:
	W3DTreeDrawModuleData();
	virtual ~W3DTreeDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x64 - 4];
};

// ?friend_newModuleData@W3DTreeDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTreeDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DTreeDrawModuleData *data = new W3DTreeDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DTreeDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DFloorDrawModuleData
{
public:
	W3DFloorDrawModuleData();
	virtual ~W3DFloorDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x30 - 4];
};

// ?friend_newModuleData@W3DFloorDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DFloorDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DFloorDrawModuleData *data = new W3DFloorDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DFloorDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DPropDrawModuleData
{
public:
	W3DPropDrawModuleData();
	virtual ~W3DPropDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@W3DPropDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DPropDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DPropDrawModuleData *data = new W3DPropDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DPropDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DBuffDrawModuleData
{
public:
	W3DBuffDrawModuleData();
	virtual ~W3DBuffDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@W3DBuffDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DBuffDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DBuffDrawModuleData *data = new W3DBuffDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DBuffDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DStreakDrawModuleData
{
public:
	W3DStreakDrawModuleData();
	virtual ~W3DStreakDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x34 - 4];
};

// ?friend_newModuleData@W3DStreakDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DStreakDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DStreakDrawModuleData *data = new W3DStreakDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DStreakDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DSailModelDrawModuleData
{
public:
	W3DSailModelDrawModuleData();
	virtual ~W3DSailModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x194 - 4];
};

// ?friend_newModuleData@W3DSailModelDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DSailModelDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DSailModelDrawModuleData *data = new W3DSailModelDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DSailModelDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DBoatWakeModelDrawModuleData
{
public:
	W3DBoatWakeModelDrawModuleData();
	virtual ~W3DBoatWakeModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@W3DBoatWakeModelDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DBoatWakeModelDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DBoatWakeModelDrawModuleData *data = new W3DBoatWakeModelDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DBoatWakeModelDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DProjectileStreamDrawModuleData
{
public:
	W3DProjectileStreamDrawModuleData();
	virtual ~W3DProjectileStreamDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@W3DProjectileStreamDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DProjectileStreamDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DProjectileStreamDrawModuleData *data = new W3DProjectileStreamDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DProjectileStreamDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class W3DTornadoDrawModuleData
{
public:
	W3DTornadoDrawModuleData();
	virtual ~W3DTornadoDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x44 - 4];
};

// ?friend_newModuleData@W3DTornadoDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTornadoDrawModuleData::friend_newModuleData(INI *ini)
{
	W3DTornadoDrawModuleData *data = new W3DTornadoDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DTornadoDrawModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
