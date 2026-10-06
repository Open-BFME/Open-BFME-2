// cl: /DNDEBUG /MD
// ?rva00262C53@Rva00262C53@@UAEXABUCoord3D@@@Z @0x00262C53 72B. Slot 133 of 8
// AIUpdate vtables: if (m_1FC != 4) delete Path at +0x140 via rowed
// ??1Path@@QAE@XZ plus rowed ??3@YAXPAX@Z and null it; set m_1FC=4; copy 12B
// Coord3D arg to +0x200 via 3x movsd. Prev setLocomotorGoalPositionExplicit.
struct Coord3D {
	float x;
	float y;
	float z;
};
class Path {
public:
	~Path();
};
class Rva00262C53 {
public:
	virtual void rva00262C53(const Coord3D &p);
private:
	char m_pad00[316];
	Path *m_140;
	char m_pad144[184];
	int m_1FC;
	Coord3D m_200;
};
void Rva00262C53::rva00262C53(const Coord3D &p)
{
	if (m_1FC != 4) {
		delete m_140;
		m_140 = 0;
	}
	m_1FC = 4;
	m_200 = p;
}
