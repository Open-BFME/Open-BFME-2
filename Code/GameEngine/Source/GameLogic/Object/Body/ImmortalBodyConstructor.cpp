// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

class Thing;
class ModuleData;
class DamageInfo;

class Xfer
{
public:
	void Version1();
};

template<typename T>
inline const T& max(const T& a, const T& b)
{
	if (a > b)
		return a;
	return b;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ActiveBody();

	virtual void slot0();

protected:
	virtual void xfer( Xfer *xfer );

public:
	virtual Real getHealth() const;
	virtual void slot3();
	virtual void slot4();
	virtual void internalChangeHealth( Real delta, DamageInfo *damageInfo );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h
class ImmortalBody : public ActiveBody
{
public:
	ImmortalBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ImmortalBody();

	virtual void internalChangeHealth( Real delta, DamageInfo *damageInfo );

protected:
	virtual void xfer( Xfer *xfer );
};

ImmortalBody::ImmortalBody( Thing *thing, const ModuleData *moduleData )
	: ActiveBody( thing, moduleData )
{
}

// ??1ImmortalBody@@UAE@XZ present-unmatched
ImmortalBody::~ImmortalBody()
{
}

// Open-BFME Zero Hour ImmortalBody::xfer (ImmortalBody.cpp:84-95) versions the
// transfer then extends ActiveBody::xfer; retail calls Xfer::Version1 and the
// 551-byte ActiveBody base body at 0x004BF1E8.
void ImmortalBody::xfer( Xfer *xfer )
{
	xfer->Version1();
	ActiveBody::xfer( xfer );
}

// BFME 2 passes the DamageInfo along: ImmortalBody's vftable slot at
// 0x00C5B520 holds this body where RespawnBody's slot at 0x00C5B970 holds its
// override that reads DamageInfo fields from the second argument (both are
// followed by 0x004BF186), and it calls through to ActiveBody's version at
// 0x004BF005 (ret 8).
void ImmortalBody::internalChangeHealth( Real delta, DamageInfo *damageInfo )
{
	delta = max( delta, -getHealth() + 1.0f );
	ActiveBody::internalChangeHealth( delta, damageInfo );
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot0@ActiveBody@@UAEXXZ=?Rva004C0898Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?getHealth@ActiveBody@@UBEMXZ=?rva004C08B7@ImmortalBody@@SA?AW4NameKeyType@@XZ")
#pragma comment(linker, "/alternatename:?slot3@ActiveBody@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot4@ActiveBody@@UAEXXZ=??1Coord2D@@QAE@XZ")
