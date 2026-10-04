// cl: /O1 /DNDEBUG /MD
//
// ModelConditionAudioLoopClientBehavior's two condition-change entries, both
// running the class's 0x004CBFC7 (pinned by address) on the primary this
// with a set of condition flags:
//   +0x0C interface slot 0 (table 0x00C5F450), retail 0x004CC07B (18 bytes):
//         with the owner's current flags at +0x258;
//   +0x10 interface slot 0 (table 0x00C5F44C), retail 0x004CC06C (15 bytes):
//         with the flags it is handed (its other two arguments unused).
// Named by address.
class Rva000CF0D6
{
public:
	unsigned int m_bits[19];
};
class Drawable
{
public:
	unsigned char m_pad000[0x258];
	Rva000CF0D6 m_conditionFlags;	// +0x258
};
class ModuleData;
class ClientModuleBase
{
public:
	virtual ~ClientModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;		// +0x08
};
class Rva00C5F450Iface
{
public:
	virtual void rva004CC07B() = 0;
};
class Rva00C5F44CIface
{
public:
	virtual void rva004CC06C(const Rva000CF0D6 *flags, int a2, int a3) = 0;
};
class ModelConditionAudioLoopClientBehavior : public ClientModuleBase,
	public Rva00C5F450Iface, public Rva00C5F44CIface
{
public:
	virtual void rva004CC07B();
	virtual void rva004CC06C(const Rva000CF0D6 *flags, int a2, int a3);
	void rva004CBFC7(const Rva000CF0D6 *flags);
};
void ModelConditionAudioLoopClientBehavior::rva004CC07B()
{
	rva004CBFC7(&m_drawable->m_conditionFlags);
}
void ModelConditionAudioLoopClientBehavior::rva004CC06C(const Rva000CF0D6 *flags, int a2, int a3)
{
	rva004CBFC7(flags);
}
