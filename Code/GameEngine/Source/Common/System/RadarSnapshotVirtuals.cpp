// cl: /O1 /DNDEBUG /MD
//
// Radar::loadPostProcess, retail 0x002D7ABF (12 bytes), and
// Radar::queueTerrainRefresh, retail 0x002D7AB0 (15 bytes): slots 1 and 5 of
// the W3DRadar vtable 0x00BC4E34 (slot-2 name getter returns "Radar"; slot 10
// is the rowed W3DRadar::clearShroud), in Radar's code range. Ported from
// Zero Hour's GameEngine/Source/Common/System/Radar.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): loadPostProcess
// refreshes the terrain from TheTerrainLogic through the refreshTerrain slot
// (4), and queueTerrainRefresh records the current frame.
// Layout (target evidence): m_queueTerrainRefreshFrame +0x1460 (the rowed
// Radar::refreshTerrain 0x002D7AA6 clears it).
typedef unsigned int UnsignedInt;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class Radar
{
public:
	virtual ~Radar(void);
	virtual void loadPostProcess(void);
	virtual void slot02();
	virtual void slot03();
	virtual void refreshTerrain(TerrainLogic *terrain);
	virtual void queueTerrainRefresh(void);
private:
	unsigned char m_pad04[0x1460 - 0x04];
	UnsignedInt m_queueTerrainRefreshFrame; // +0x1460
};

//-------------------------------------------------------------------------------------------------
void Radar::queueTerrainRefresh( void )
{
	m_queueTerrainRefreshFrame = TheGameLogic->getFrame();
}

//-------------------------------------------------------------------------------------------------
void Radar::loadPostProcess( void )
{

	//
	// refresh the radar texture now that all the objects (specifically bridges) have
	// been loaded with their correct damage states from save game file
	//
	refreshTerrain( TheTerrainLogic );

}
