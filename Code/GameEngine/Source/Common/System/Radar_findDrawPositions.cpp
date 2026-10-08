// cl: /DNDEBUG /MD
//
// Radar extent-ratio helper, retail 0x002D790A, 146 bytes.
// Radar.cpp owns findDrawPositions at 0x002D799C; keep only this unit
//'s verified ratio body here to avoid a second strong definition.

typedef int Int;
typedef float Real;

struct RadarExtent
{
	Real minX;
	Real minY;
	Int reserved;
	Real maxX;
	Real maxY;

	Real width() const { return maxX - minX; }
	Real height() const { return maxY - minY; }
};

class Radar
{
public:
	void rva002D790A(Real *widthRatio, Real *heightRatio);

private:
	char m_pad[0x1430];
	void *m_radarWindow; // +0x1430
	RadarExtent m_extent; // +0x1434..+0x1447
};

// ?rva002D790A@Radar@@QAEXPAM0@Z @0x002D790A 146B
// Target evidence: reads Radar extent fields at +0x1434..+0x1444, compares
// width and height, and writes two output ratios. Radar identity is inferred
// from the shared extent layout in this TU and neighboring Radar methods.
void Radar::rva002D790A(Real *widthRatio, Real *heightRatio)
{
	Real width = m_extent.maxX - m_extent.minX;
	Real height = m_extent.maxY - m_extent.minY;
	if (width > height) {
		*widthRatio = 1.0f;
		*heightRatio = (m_extent.maxY - m_extent.minY) /
			(m_extent.maxX - m_extent.minX);
	} else {
		*heightRatio = 1.0f;
		*widthRatio = (m_extent.maxX - m_extent.minX) /
			(m_extent.maxY - m_extent.minY);
	}
}
