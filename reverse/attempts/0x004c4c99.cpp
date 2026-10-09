// ?rva004C4C99@FreezingRainSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include
// The placement helpers FreezingRainSpecialPower 0x004C4C99 and
// DarknessSpecialPower 0x004C4E93 (137B each) that their
// doSpecialPowerAtLocation overrides call on the primary this with the
// location (AreaSpecialPowersAtLocation.cpp, which pins both names).
// Target facts: the two bodies are identical but for the weather test --
// nothing while TheGlobalWeatherSystem (VA 0x00E01CE4) +0x10 is 2 (RAINY,
// FreezingRain) or 1 (CLOUDY, Darkness) in GlobalWeatherSystem.cpp's
// TheWeatherNames order, or while the module data's +0x80 FX list is null.
// Otherwise the FX plays at the centre of the map extent (TheTerrainLogic
// slot 0x20 fills a Region3D) at the location's height through the rowed
// static FXList::doFXPos 0x00094C29. Both are /O1 EBP-frame bodies.

#include "Lib/Coord3D.h"

typedef float Real;
typedef int Int;

class Matrix3D;

struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	void getCenterPoint( Coord3D *center ) const
	{
		center->x = ( lo.x + hi.x ) / 2.0f;
		center->y = ( lo.y + hi.y ) / 2.0f;
		center->z = ( lo.z + hi.z ) / 2.0f;
	}
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void getExtent(Region3D *extent) const;
};
extern TerrainLogic *TheTerrainLogic;

enum WeatherType
{
	WEATHER_NONE = 0,
	WEATHER_CLOUDY = 1,
	WEATHER_RAINY = 2
};

class GlobalWeatherSystem
{
public:
	WeatherType getWeatherType() const { return m_weatherType; }

private:
	char m_unknown00[0x10];
	WeatherType m_weatherType; // +0x10
};
extern GlobalWeatherSystem *TheGlobalWeatherSystem;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary);
};

struct AreaSkySpecialPowerModuleData
{
	unsigned char m_unmodelled00[0x80];
	const FXList *m_fx; // +0x80
};

class SpecialPowerModule
{
protected:
	const AreaSkySpecialPowerModuleData *getData() const { return m_moduleData; }

private:
	void *m_vtable;
	const AreaSkySpecialPowerModuleData *m_moduleData;
};

class FreezingRainSpecialPower : public SpecialPowerModule
{
public:
	void rva004C4C99(const Coord3D *loc);
};

class DarknessSpecialPower : public SpecialPowerModule
{
public:
	void rva004C4E93(const Coord3D *loc);
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void FreezingRainSpecialPower::rva004C4C99( const Coord3D *loc )
{
	if( TheGlobalWeatherSystem->getWeatherType() == WEATHER_RAINY )
		return;

	const AreaSkySpecialPowerModuleData *data = getData();
	if( data->m_fx == 0 )
		return;

	Region3D extent;
	TheTerrainLogic->getExtent( &extent );

	Coord3D pos;
	pos.x = ( extent.lo.x + extent.hi.x ) * 0.5f;
	pos.y = ( extent.lo.y + extent.hi.y ) * 0.5f;
	pos.z = loc->z;
	Real speed = 0.0f;
	FXList::doFXPos( data->m_fx, &pos, 0, speed, 0 );
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void DarknessSpecialPower::rva004C4E93( const Coord3D *loc )
{
	if( TheGlobalWeatherSystem->getWeatherType() == WEATHER_CLOUDY )
		return;

	const AreaSkySpecialPowerModuleData *data = getData();
	if( data->m_fx == 0 )
		return;

	Region3D extent;
	TheTerrainLogic->getExtent( &extent );

	Coord3D pos;
	extent.getCenterPoint( &pos );
	pos.z = loc->z;
	FXList::doFXPos( data->m_fx, &pos, 0, 0.0f, 0 );
}
