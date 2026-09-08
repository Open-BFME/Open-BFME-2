// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "rendobj.h"
#include "scene.h"

// Compare IEEE754 encodings exactly; negative zero is not an identity entry.
static inline bool Check_Is_Transform_Identity(const Matrix3D& m)
{
	const float zero=0.0f;
	const float one=1.0f;

	unsigned d=
		((unsigned&)m[0][0]^(unsigned&)one) |
		((unsigned&)m[0][1]^(unsigned&)zero) |
		((unsigned&)m[0][2]^(unsigned&)zero) |
		((unsigned&)m[0][3]^(unsigned&)zero) |
		((unsigned&)m[1][0]^(unsigned&)zero) |
		((unsigned&)m[1][1]^(unsigned&)one) |
		((unsigned&)m[1][2]^(unsigned&)zero) |
		((unsigned&)m[1][3]^(unsigned&)zero) |
		((unsigned&)m[2][0]^(unsigned&)zero) |
		((unsigned&)m[2][1]^(unsigned&)zero) |
		((unsigned&)m[2][2]^(unsigned&)one) |
		((unsigned&)m[2][3]^(unsigned&)zero);
	return !d;
}

// ?Set_Transform@RenderObjClass@@UAEXABVMatrix3D@@@Z present-unmatched
void RenderObjClass::Set_Transform(const Matrix3D &m)
{
	Transform = m;
	IsTransformIdentity=Check_Is_Transform_Identity(m);
	Bits &= ~BOUNDING_VOLUMES_VALID;
	if (Scene && !Container) {
		Scene->Register(this, (SceneClass::RegType)3);
	}
}

void RenderObjClass::Set_Position(const Vector3 &v)
{
	Transform.Set_Translation(v);
	IsTransformIdentity=Check_Is_Transform_Identity(Transform);
	Bits &= ~BOUNDING_VOLUMES_VALID;
	if (Scene && !Container) {
		Scene->Register(this, (SceneClass::RegType)3);
	}
}

