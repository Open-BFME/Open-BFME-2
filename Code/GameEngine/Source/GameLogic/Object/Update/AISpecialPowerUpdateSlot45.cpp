// cl: /O1 /DNDEBUG /MD
//
// AISpecialPowerUpdate slot 45 of its +0x0C interface table 0x00C56D60,
// retail 0x004B33EB (18 bytes), so `this` is that subobject: with a non-null
// argument it runs the pinned private rva004B303F (the member the class xfer
// 0x004B3352 also runs on load) on the primary this. Named by address.
template <int N> class Rva004B33EBSlots : public Rva004B33EBSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004B33EBSlots<0>
{
};
class Rva00C56D60Iface : public Rva004B33EBSlots<45>
{
public:
	virtual void rva004B33EB(void *arg) = 0;
};
class ModuleData;
class Object;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class AISpecialPowerUpdate : public ModuleBase, public Rva00C56D60Iface
{
public:
	virtual void rva004B33EB(void *arg);
private:
	void rva004B303F();
};
void AISpecialPowerUpdate::rva004B33EB(void *arg)
{
	if (arg)
		rva004B303F();
}
