// cl: /DNDEBUG /MD /O1
//
// Drawable::findClientUpdateModule (0x0027449C, 43B), ported from the Zero
// Hour donor (GameClient/Drawable.cpp). Retail walks the null-terminated
// client update module array at Drawable+0x150 and advances the cursor each
// pass, which the donor's loop omits. getModuleNameKey is module vtable slot
// +0x10 (retail call [eax+0x10]). W3DLaserDraw::doDrawModule 0x000C93B1
// calls it with key_LaserUpdate. Retail is frameless with the key compared
// in memory: /O1, not the /Oy- of the other Drawable units.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ClientUpdateModule
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual NameKeyType getModuleNameKey() const;
};

class Drawable
{
public:
	ClientUpdateModule *findClientUpdateModule(NameKeyType key);
	ClientUpdateModule **getClientUpdateModules() { return m_clientModules; }

private:
	char m_pad[0x150];
	ClientUpdateModule **m_clientModules; // +0x150
};

ClientUpdateModule *Drawable::findClientUpdateModule(NameKeyType key)
{
	ClientUpdateModule **clientModules = getClientUpdateModules();
	if (clientModules)
	{
		while (*clientModules)
		{
			if ((*clientModules)->getModuleNameKey() == key)
			{
				return *clientModules;
			}
			++clientModules;
		}
	}
	return 0;
}
