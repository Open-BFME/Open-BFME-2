// cl: /O1 /Oy- /MD
//
// TRoadSegInfo::operator=, retail 0x000D69D3, 108 bytes. Dedicated TU so
// W3DRoadBuffer.cpp keeps its matched bodies. Leading Vector2 members copy
// as dwords; corners[4] is a counted Vector2 assign loop; then the three
// floats.

class Vector2
{
public:
	float X;
	float Y;

	Vector2 &operator=(const Vector2 &v)
	{
		X = v[0];
		Y = v[1];
		return *this;
	}

	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
};

enum { NUM_CORNERS = 4 };

struct TRoadSegInfo
{
	Vector2 loc;
	Vector2 roadNormal;
	Vector2 roadVector;
	Vector2 corners[NUM_CORNERS];
	float uOffset;
	float vOffset;
	float scale;

	TRoadSegInfo &operator=(const TRoadSegInfo &that);
};

TRoadSegInfo &TRoadSegInfo::operator=(const TRoadSegInfo &that)
{
	loc = that.loc;
	roadNormal = that.roadNormal;
	roadVector = that.roadVector;
	for (int i = 0; i < NUM_CORNERS; ++i)
		corners[i] = that.corners[i];
	uOffset = that.uOffset;
	vOffset = that.vOffset;
	scale = that.scale;
	return *this;
}
