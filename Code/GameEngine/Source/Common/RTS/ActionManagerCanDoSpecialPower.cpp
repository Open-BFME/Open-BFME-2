// cl: /O1 /DNDEBUG /MD /arch:SSE
// ActionManager::canDoSpecialPower, retail 0x0041CCD5 (305 bytes with its switch tables):
// ?canDoSpecialPower@ActionManager@@QAE_NPBVObject@@PBVSpecialPowerTemplate@@W4CommandSourceType@@I_N@Z
// Identity (target): WorldBuilder's debug ActionManager.cpp
// ActionManager::canDoSpecialPower; retail follows Zero Hour's body and
// callee order: Overridable::friend_getFinalOverride on the template,
// Object::hasSpecialPower (0x0028D8EB), the action manager's 0x0041BA61
// test, Object::getSpecialPowerModule and the module's ready queries, then
// a switch on the special power type.
// Body (target): with source requirements checked, the object must have
// the power, its module must be fully ready (slot 0x08 percent >= 1) and
// its slot 0x48 test (with 0) must pass. The final switch over the
// template's type (+0x1C) answers true for the types below; the table at
// 0x0081CD70 also lists explicit false cases separately from the default.
// The BFME 2 enumerator names are not recovered, so the cases are numeric.
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	__declspec(dllimport) __forceinline SpecialPowerType getSpecialPowerType() const
	{
		return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_type;
	}

private:
	unsigned char m_pad00[0x1C];
	SpecialPowerType m_type; // +0x1C
};

class SpecialPowerModuleInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual float getPercentReady() const; // slot 0x08
	virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06();
	virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17();
	virtual bool v18(int flags); // slot 0x48
};

class Object
{
public:
	bool hasSpecialPower(SpecialPowerType type) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *specialPowerTemplate) const;
};

class ActionManager
{
public:
	bool canDoSpecialPower(const Object *obj, const SpecialPowerTemplate *spTemplate, CommandSourceType commandSource, unsigned int commandOptions, bool checkSourceRequirements);
	bool rva0041BA61(const Object *obj);
};

bool ActionManager::canDoSpecialPower(const Object *obj, const SpecialPowerTemplate *spTemplate, CommandSourceType commandSource, unsigned int commandOptions, bool checkSourceRequirements)
{
	if (!spTemplate)
		return false;

	if (checkSourceRequirements)
	{
		if (!obj->hasSpecialPower(spTemplate->getSpecialPowerType()))
			return false;
	}

	if (rva0041BA61(obj))
		return false;

	SpecialPowerModuleInterface *spmInterface = obj->getSpecialPowerModule(spTemplate);
	if (!spmInterface)
		return false;

	if (checkSourceRequirements)
	{
		if (spmInterface->getPercentReady() < 1.0f)
			return false;
		if (!spmInterface->v18(0))
			return false;
	}

	switch (spTemplate->getSpecialPowerType())
	{
		case 27:
		case 37:
		case 39:
		case 40:
		case 41:
		case 43:
		case 44:
		case 46:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 58:
		case 60:
		case 61:
		case 62:
		case 66:
		case 76:
		case 78:
		case 79:
		case 81:
		case 88:
		case 92:
		case 98:
		case 102:
		case 105:
		case 108:
		case 109:
		case 110:
		case 114:
		case 116:
		case 117:
		case 119:
		case 121:
		case 122:
		case 125:
		case 127:
		case 128:
		case 131:
		case 133:
		case 135:
		case 136:
		case 137:
		case 141:
		case 143:
		case 152:
			return true;
		case 16:
		case 28:
		case 35:
		case 42:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 57:
		case 59:
		case 63:
		case 64:
		case 65:
		case 67:
		case 68:
		case 69:
		case 70:
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
		case 77:
		case 80:
		case 82:
		case 84:
		case 85:
		case 86:
		case 87:
		case 89:
		case 90:
		case 91:
		case 93:
		case 94:
		case 95:
		case 96:
		case 97:
		case 99:
		case 100:
		case 101:
		case 103:
		case 104:
		case 106:
		case 107:
		case 111:
		case 112:
		case 113:
		case 115:
		case 118:
		case 120:
		case 123:
		case 124:
		case 126:
		case 129:
		case 132:
		case 134:
		case 138:
		case 140:
		case 142:
		case 144:
		case 145:
		case 146:
		case 147:
		case 148:
		case 149:
		case 150:
		case 151:
		case 153:
			return false;
	}
	return false;
}
