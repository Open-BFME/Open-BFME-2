#pragma once
// Target BC745C/BC74F4 and their RET4/RET24 slots establish this dispatch
// order. Owner8990C/89971 establishes two 20B owning-element arrays (255/4)
// starting at2C/1418. Cleanup4F82B reaches StringBase<char>::releaseBuffer
// at36410 from element+C. The initializer accesses through2070. These are
// observed prefixes; original names and complete sizes remain unknown.
// The destructor TU uses novtable solely to reproduce retail's absent entry
// vptr store. This does not claim a historical source annotation.
typedef float Real;

class ParabolicEase
{
public:
	void rva0030E51F(Real easeInTime, Real easeOutTime, Real duration);
	ParabolicEase(Real easeInTime = 0.0f, Real easeOutTime = 0.0f, Real duration = 1.0f);
	Real operator()(Real param) const;
private:
	Real m_in;
	Real m_out;
};

class Rva000851F3
{
public:
	Rva000851F3();
	virtual ~Rva000851F3() {}
	virtual void rva00047A69C(int) = 0;
	virtual void rva00086B2C(int, int, Real, Real, int, int) = 0;
protected:
	friend class Rva00086761CameraMove;
	friend class W3DView;
	int m_04;
	int m_08;
	int m_0C;
	ParabolicEase m_10;
	float m_18;
	float m_1C;
	int m_20;
	bool m_24;
	int m_28;
};


#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
// The three-float prefix is read/stored by177B86761; original point name
// remains unknown. This trivial value preserves complete12B copies.
struct Rva00089894Point
{
 float x, y, z;
};

class Rva00089894ArrayElement
{
public:
 Rva00089894ArrayElement();
 ~Rva00089894ArrayElement();
private:
 friend class Rva00086761CameraMove;
 friend class W3DView;
 Rva00089894Point m_position;
 AsciiString m_0C;
 int m_10;
};

#ifndef BFME_ARRAY_OWNER_ATTRIBUTES
#define BFME_ARRAY_OWNER_ATTRIBUTES
#endif
class BFME_ARRAY_OWNER_ATTRIBUTES Rva0089971 : public Rva000851F3
{
public:
 Rva0089971();
 virtual ~Rva0089971();
 virtual void rva00047A69C(int) {}
 virtual void rva00086B2C(int, int, Real, Real, int, int);
private:
 friend class Rva00086761CameraMove;
 friend class W3DView;
 Rva00089894ArrayElement m_arr255[255];
 Rva00089894ArrayElement m_arr4[4];
 // moveAlongWaypointPath (0x00086F56) reads these as floats: per-waypoint
 // angles at +1468, segment lengths at +1864, the total distance at +1C68
 // and the eased ground endpoints at +1C6C/+1C70.
 float m_cameraAngles[255];
 float m_values[257];
 float m_totalDistance;
 float m_groundStart;
 float m_groundEnd;
 int m_filled[255];
 int m_numValues;
};

#undef BFME_ARRAY_OWNER_ATTRIBUTES

// Target primary-table slots32/39/59 and unchanged-this call88F2E->86CDA
// associate these methods. Constructor8B7CF embeds the owning prefix at280.
// The target-proven parent prefix ends2358; full size/original names unknown.
class Rva00086761CameraMove
{
public:
 void rva00086761(Rva00089894Point *pLoc);
 void rva0008690A(int value);
 // Primary vftable BC7568 slot33, target86812/248/RET4; exact name unknown.
 void rva00086812(int value);
 // Primary vftable BC7568 slot60, target88F38/190/RET16; exact name unknown.
 void rva00088F38(float finalPitch, int milliseconds, float easeIn, float easeOut);
 void rva00088EB4(float finalValue, int milliseconds, float easeIn, float easeOut);
 void rva00086CDA();
private:
 char m_padding0000[0x3C];
 float m_3C;
 char m_padding0040[0x1DC-0x40];
 bool m_doingRotateCamera;
 char m_padding1dd[0x208-0x1DD];
 int m_208, m_20C;
 float m_210, m_214;
 char m_padding218[8];
 ParabolicEase m_220;
 unsigned char m_228;
 char m_padding229[0x280-0x229];
 Rva0089971 m_cameraPath;
 char m_padding22f4[0x2354-0x22F4];
 int m_cameraMovementMode;
};
