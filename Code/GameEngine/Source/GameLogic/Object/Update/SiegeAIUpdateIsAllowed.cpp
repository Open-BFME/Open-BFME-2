// cl: /O1 /DNDEBUG /MD
//
// SiegeAIUpdate::isAllowedToRespondToAiCommands, retail 0x004905D1 (60
// bytes): primary slot 148 of vtable 0x00C4D330, the slot the rowed
// AIUpdateInterface::isAllowedToRespondToAiCommands 0x0026734C fills in the
// base. After the base allows the command, a siege unit whose special power
// of type 0x2D exists but is not ready (interface slot 1, isReady in the Zero
// Hour order) only takes command 0x1B (AICMD_EVACUATE in the Zero Hour
// numbering).
typedef bool Bool;
class Object;
enum AICommandType
{
	AICMD_BFME_1B = 0x1B
};
struct AICommandParms
{
	AICommandType m_cmd;	// +0x00
};
enum SpecialPowerType
{
	SPECIAL_BFME_2D = 0x2D
};
class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual Bool isReady() const = 0;
};
class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};
class ModuleData;
class AIUpdateInterface
{
public:
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const;
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class SiegeAIUpdate : public AIUpdateInterface
{
public:
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const;
};
Bool SiegeAIUpdate::isAllowedToRespondToAiCommands(const AICommandParms *parms) const
{
	if (!AIUpdateInterface::isAllowedToRespondToAiCommands(parms))
		return false;
	SpecialPowerModuleInterface *sp = getObject()->findSpecialPowerModuleInterface(SPECIAL_BFME_2D);
	if (sp && !sp->isReady())
		return parms->m_cmd == AICMD_BFME_1B;
	return true;
}
