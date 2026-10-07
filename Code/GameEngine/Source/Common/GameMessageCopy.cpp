// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
//
// GameMessage copy constructor (retail 0x00311097) and its void twin
// (0x0031123E), the BFME 2 forms of BFME 1's GameMessage_copyConstructor.cpp
// pair (0x0008AF70 / 0x0008B2C0). Identity: the constructor installs the
// GameMessage vtable (0x00C09840, slot 0 the deleting dtor 0x0030F8E3 over
// dtor 0x0030F4AF), copies type +0x10 and player index +0x14, clears the
// argument list +0x1C/+0x20, count byte +0x18 and the list links +0x04/+0x08/
// +0x0C, then replays every source argument through the rowed type query
// (0x0030F50C) and the eleven rowed append methods. Unlike BFME 1, BFME 2
// calls getArgumentDataType and the append methods out of line instead of
// inlining allocArg. The twin is the same body without the vtable store; no
// caller of either survives in retail, so the twin keeps BFME 1's
// address-derived name. The location and pixel cases copy member-wise into
// the frame (movss / both words loaded first), as retail does, rather than
// by struct copy (rep movsd spills the index).

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

enum ObjectID {};
enum DrawableID {};

union GameMessageArgumentType
{
	int integer;
	float real;
	bool boolean;
	ObjectID objectID;
	DrawableID drawableID;
	unsigned int teamID;
	unsigned int squadID;
	Coord3D location;
	ICoord2D pixel;
	IRegion2D pixelRegion;
	unsigned int timestamp;
	unsigned short wideChar;
};

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER,
	ARGUMENTDATATYPE_REAL,
	ARGUMENTDATATYPE_BOOLEAN,
	ARGUMENTDATATYPE_OBJECTID,
	ARGUMENTDATATYPE_DRAWABLEID,
	ARGUMENTDATATYPE_TEAMID,
	ARGUMENTDATATYPE_LOCATION,
	ARGUMENTDATATYPE_PIXEL,
	ARGUMENTDATATYPE_PIXELREGION,
	ARGUMENTDATATYPE_TIMESTAMP,
	ARGUMENTDATATYPE_WIDECHAR,
	ARGUMENTDATATYPE_UNKNOWN
};

class GameMessageArgument;
class GameMessageList;

class GameMessage
{
public:
	GameMessage(const GameMessage &source);
	virtual ~GameMessage();
	void rva0031123E(const GameMessage &source);

	const GameMessageArgumentType *getArgument(int argIndex) const;
	GameMessageArgumentDataType getArgumentDataType(int argIndex);

	void appendIntegerArgument(int arg);
	void appendRealArgument(float arg);
	void appendBooleanArgument(bool arg);
	void appendObjectIDArgument(ObjectID arg);
	void appendDrawableIDArgument(DrawableID arg);
	void appendTeamIDArgument(unsigned int arg);
	void appendLocationArgument(const Coord3D &arg);
	void appendPixelArgument(const ICoord2D &arg);
	void appendPixelRegionArgument(const IRegion2D &arg);
	void appendTimestampArgument(unsigned int arg);
	void appendWideCharArgument(const unsigned short &arg);

private:
	GameMessage *m_next; // +0x04
	GameMessage *m_prev; // +0x08
	GameMessageList *m_list; // +0x0C
	int m_type; // +0x10
	int m_playerIndex; // +0x14
	unsigned char m_argCount; // +0x18
	GameMessageArgument *m_argList; // +0x1C
	GameMessageArgument *m_argTail; // +0x20
};

// ??0GameMessage@@QAE@ABV0@@Z @0x00311097
GameMessage::GameMessage(const GameMessage &source)
{
	m_playerIndex = source.m_playerIndex;
	m_type = source.m_type;
	m_argList = 0;
	m_argTail = 0;
	m_argCount = 0;
	m_list = 0;
	m_next = 0;
	m_prev = 0;

	for (int i = 0; i < source.m_argCount; ++i)
	{
		switch (const_cast<GameMessage &>(source).getArgumentDataType(i))
		{
		case ARGUMENTDATATYPE_INTEGER:
			appendIntegerArgument(source.getArgument(i)->integer);
			break;
		case ARGUMENTDATATYPE_REAL:
			appendRealArgument(source.getArgument(i)->real);
			break;
		case ARGUMENTDATATYPE_BOOLEAN:
			appendBooleanArgument(source.getArgument(i)->boolean);
			break;
		case ARGUMENTDATATYPE_OBJECTID:
			appendObjectIDArgument(source.getArgument(i)->objectID);
			break;
		case ARGUMENTDATATYPE_DRAWABLEID:
			appendDrawableIDArgument(source.getArgument(i)->drawableID);
			break;
		case ARGUMENTDATATYPE_TEAMID:
			appendTeamIDArgument(source.getArgument(i)->teamID);
			break;
		case ARGUMENTDATATYPE_LOCATION:
		{
			const Coord3D &from = source.getArgument(i)->location;
			Coord3D location;
			location.x = from.x;
			location.y = from.y;
			location.z = from.z;
			appendLocationArgument(location);
			break;
		}
		case ARGUMENTDATATYPE_PIXEL:
		{
			const ICoord2D &from = source.getArgument(i)->pixel;
			int x = from.x;
			int y = from.y;
			ICoord2D pixel;
			pixel.y = y;
			pixel.x = x;
			appendPixelArgument(pixel);
			break;
		}
		case ARGUMENTDATATYPE_PIXELREGION:
			appendPixelRegionArgument(source.getArgument(i)->pixelRegion);
			break;
		case ARGUMENTDATATYPE_TIMESTAMP:
			appendTimestampArgument(source.getArgument(i)->timestamp);
			break;
		case ARGUMENTDATATYPE_WIDECHAR:
			appendWideCharArgument(source.getArgument(i)->wideChar);
			break;
		}
	}
}

// ?rva0031123E@GameMessage@@QAEXABV1@@Z @0x0031123E
void GameMessage::rva0031123E(const GameMessage &source)
{
	m_playerIndex = source.m_playerIndex;
	m_type = source.m_type;
	m_argList = 0;
	m_argTail = 0;
	m_argCount = 0;
	m_list = 0;
	m_next = 0;
	m_prev = 0;

	for (int i = 0; i < source.m_argCount; ++i)
	{
		switch (const_cast<GameMessage &>(source).getArgumentDataType(i))
		{
		case ARGUMENTDATATYPE_INTEGER:
			appendIntegerArgument(source.getArgument(i)->integer);
			break;
		case ARGUMENTDATATYPE_REAL:
			appendRealArgument(source.getArgument(i)->real);
			break;
		case ARGUMENTDATATYPE_BOOLEAN:
			appendBooleanArgument(source.getArgument(i)->boolean);
			break;
		case ARGUMENTDATATYPE_OBJECTID:
			appendObjectIDArgument(source.getArgument(i)->objectID);
			break;
		case ARGUMENTDATATYPE_DRAWABLEID:
			appendDrawableIDArgument(source.getArgument(i)->drawableID);
			break;
		case ARGUMENTDATATYPE_TEAMID:
			appendTeamIDArgument(source.getArgument(i)->teamID);
			break;
		case ARGUMENTDATATYPE_LOCATION:
		{
			const Coord3D &from = source.getArgument(i)->location;
			Coord3D location;
			location.x = from.x;
			location.y = from.y;
			location.z = from.z;
			appendLocationArgument(location);
			break;
		}
		case ARGUMENTDATATYPE_PIXEL:
		{
			const ICoord2D &from = source.getArgument(i)->pixel;
			int x = from.x;
			int y = from.y;
			ICoord2D pixel;
			pixel.y = y;
			pixel.x = x;
			appendPixelArgument(pixel);
			break;
		}
		case ARGUMENTDATATYPE_PIXELREGION:
			appendPixelRegionArgument(source.getArgument(i)->pixelRegion);
			break;
		case ARGUMENTDATATYPE_TIMESTAMP:
			appendTimestampArgument(source.getArgument(i)->timestamp);
			break;
		case ARGUMENTDATATYPE_WIDECHAR:
			appendWideCharArgument(source.getArgument(i)->wideChar);
			break;
		}
	}
}
