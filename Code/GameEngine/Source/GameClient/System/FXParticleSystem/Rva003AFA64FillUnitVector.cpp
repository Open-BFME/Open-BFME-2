// cl: /MD
// ?Rva003AFA64FillUnitVector@@YAPAUCoord3D@@PAU1@@Z @ 0x003AFA64 198B
// Random unit vector in fxpsemittervolumemodule.cpp (__FILE__ at 0x0081D7C0
// lines 31-33): GetGameClientRandomValueReal(-1.0f at 0x007BB9AC, 1.0f) thrice
// retry while all zero then normalize and store to out. Callees rowed:
// GetGameClientRandomValueReal 0x00234111 and Coord3D::normalize 0x000035B6.
// Donor BFME1 Rva005FAD00FillUnitVector same file same lines same range.
// Callers 0x0055CAAC 0x0055D48C 0x00564AB8 become ready. Sibling
// Rva005EE317RandomDir same shape same flags.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

float __cdecl GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

Coord3D *__cdecl Rva003AFA64FillUnitVector(Coord3D *out)
{
	Coord3D tmp;
	do {
		tmp.x = GetGameClientRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittervolumemodule.cpp", 31);
		tmp.y = GetGameClientRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittervolumemodule.cpp", 32);
		tmp.z = GetGameClientRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittervolumemodule.cpp", 33);
	} while (tmp.x == 0.0f && tmp.y == 0.0f && tmp.z == 0.0f);
	tmp.normalize();
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
	return out;
}
