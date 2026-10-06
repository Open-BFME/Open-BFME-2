// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037AF88@Rva0037AF88@@QAEXHPAVGameMessage@@@Z @0x0037AF88 446B: recorder game-message arg reader via IAT fread plus rowed GameMessage appends 0-10. Evidence: FILE at +0x10 early dispatch plus fread sizes 4 1 12 8 16 2 plus appendInteger Real Boolean ObjectID DrawableID TeamID Location Pixel PixelRegion Timestamp WideChar; same FILE+0x10 family as Rva0037ADB6Write and Rva0037B287Write; caller 0x0037B94D.
struct FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buf, unsigned int size, unsigned int count, FILE *stream);

enum ObjectID;
enum DrawableID;
struct Coord3D
{
	float x;
	float y;
	float z;
};
struct ICoord2D
{
	int x;
	int y;
};
struct IRegion2D
{
	int loX;
	int loY;
	int hiX;
	int hiY;
};
class GameMessage
{
public:
	void appendIntegerArgument(int v);
	void appendRealArgument(float v);
	void appendBooleanArgument(bool v);
	void appendObjectIDArgument(ObjectID v);
	void appendDrawableIDArgument(DrawableID v);
	void appendTeamIDArgument(unsigned int v);
	void appendLocationArgument(const Coord3D &v);
	void appendPixelArgument(const ICoord2D &v);
	void appendPixelRegionArgument(const IRegion2D &v);
	void appendTimestampArgument(unsigned int v);
	void appendWideCharArgument(const unsigned short &v);
};
enum ObjectID
{
	OID_ZERO = 0
};
enum DrawableID
{
	DID_ZERO = 0
};

class Rva0037AF88
{
public:
	void rva0037AF88(int type, GameMessage *msg);
private:
	char m_pad00[0x10];
	FILE *m_file10; // +0x10
};

void Rva0037AF88::rva0037AF88(int type, GameMessage *msg)
{
	if (type == 0) {
		fread(&type, 4, 1, m_file10);
		msg->appendIntegerArgument(type);
		return;
	}
	if (type == 1) {
		fread(&type, 4, 1, m_file10);
		msg->appendRealArgument(*(float *)&type);
		return;
	}
	if (type == 2) {
		fread(&type, 1, 1, m_file10);
		msg->appendBooleanArgument(*(bool *)&type);
		return;
	}
	if (type == 3) {
		fread(&type, 4, 1, m_file10);
		msg->appendObjectIDArgument((ObjectID)type);
		return;
	}
	if (type == 4) {
		fread(&type, 4, 1, m_file10);
		msg->appendDrawableIDArgument((DrawableID)type);
		return;
	}
	if (type == 5) {
		fread(&type, 4, 1, m_file10);
		msg->appendTeamIDArgument((unsigned int)type);
		return;
	}
	if (type == 6) {
		Coord3D loc;
		fread(&loc, 12, 1, m_file10);
		msg->appendLocationArgument(loc);
		return;
	}
	if (type == 7) {
		ICoord2D pix;
		fread(&pix, 8, 1, m_file10);
		msg->appendPixelArgument(pix);
		return;
	}
	if (type == 8) {
		IRegion2D reg;
		fread(&reg, 16, 1, m_file10);
		msg->appendPixelRegionArgument(reg);
		return;
	}
	if (type == 9) {
		fread(&type, 4, 1, m_file10);
		msg->appendTimestampArgument((unsigned int)type);
		return;
	}
	if (type == 10) {
		fread((char *)&type + 2, 2, 1, m_file10);
		msg->appendWideCharArgument(*(unsigned short *)((char *)&type + 2));
		return;
	}
}
