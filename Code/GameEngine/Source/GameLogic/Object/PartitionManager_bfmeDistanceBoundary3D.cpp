// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME's distance table at retail 0x00EDBD60 selects this function for the
// boundary-3D case.  BFME passes a position, a partition candidate, and an
// unused integer to the procedure.

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

// BfmeZeroRange is float 0.0 at 0x00BBAEAC (data_ledger literal); use 0.0f literal so the TU links.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeBoundaryGeometry3D
{
public:
	char m_prefix[0x14];
	float m_radius;
};

class Rva0073A1C0FloatField
{
public:
	float get(void) const;
};

class Object
{
public:
	virtual BfmeBoundaryGeometry3D *getGeometry(void) const = 0;
	virtual Coord3D *getPosition(void) const = 0;
};

// ?distCalcProc_BoundaryAndBoundary_3D@@YAMPBUCoord3D@@PBVObject@@H@Z
float distCalcProc_BoundaryAndBoundary_3D(
	const Coord3D *position,
	const Object *candidate,
	int unused)
{
	Coord3D *candidatePosition = candidate->getPosition();
	Coord3D delta;
	delta.x = candidatePosition->x;
	delta.y = candidatePosition->y;
	delta.z = candidatePosition->z;
	delta.x -= position->x;
	delta.y -= position->y;
	delta.z -= position->z;

	BfmeBoundaryGeometry3D *geometry = candidate->getGeometry();
	delta.z += ((Rva0073A1C0FloatField *)geometry)->get();

	BfmeBoundaryGeometry3D *geometry2 = candidate->getGeometry();
	float distanceSquared = delta.y * delta.y + delta.x * delta.x;
	distanceSquared += delta.z * delta.z;
	float distance = static_cast<float>(sqrt(distanceSquared));
	distance -= geometry2->m_radius;
	if (distance < 0.0f)
		return -distance * distance;
	return distance * distance;
}
