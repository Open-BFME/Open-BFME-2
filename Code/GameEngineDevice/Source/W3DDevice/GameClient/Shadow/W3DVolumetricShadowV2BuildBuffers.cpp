// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native107B41..107D6E complete557 RET16; caller107E76 owns four arguments.
// BFME1 575ba2b04 BfmeVolumetricShadowBufferEntryRender supplies geometry
// semantics. Target modelC4 counts24/28 and polygon holder2C/data0C; receiver
// mesh0 transformed verts4 face flags8 edge8 recordsC and edge count10.
// Typed pointer/ref parameters preserve native argument liveness; original
// method name stays neutral. Existing integer-view pin and sole caller are
// replaced together with this native-supported signature.
/*
**	Command & Conquer Generals(tm)
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
#include "wwmath.h"
class Vector3 {public:float X,Y,Z;__forceinline Vector3(){} __forceinline Vector3(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;} __forceinline Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;} __forceinline void Normalize(){float len2=X*X+Y*Y+Z*Z;if(len2!=0.0f){float oolen=WWMath::Inv_Sqrt(len2);X*=oolen;Y*=oolen;Z*=oolen;}}__forceinline Vector3&operator*=(float k){X*=k;Y*=k;Z*=k;return *this;}};
__forceinline Vector3 operator+(const Vector3&a,const Vector3&b){Vector3 r;r.X=a.X+b.X;r.Y=a.Y+b.Y;r.Z=a.Z+b.Z;return r;}


// Scoped vector operations reproduce the donor header behavior and full557
// bytes while avoiding its divergent unused three-float constructor COMDAT.

struct BfmeShadowTriIndex
{
	unsigned short I;
	unsigned short J;
	unsigned short K;
};

struct BfmeShadowTriBuffer
{
	unsigned char m_pad[0xc];
	BfmeShadowTriIndex *m_data;
};

struct BfmeShadowMeshModel
{
	unsigned char m_beforeFlags[0x18];
	unsigned int m_flags;
	unsigned char m_betweenFlagsAndPolyCount[8];
	int m_polyCount;
	int m_vertexCount;
	BfmeShadowTriBuffer *m_poly;
};

class BfmeShadowMesh
{
public:
	virtual void v00();

	unsigned char m_beforeModel[0xc4-4];
	BfmeShadowMeshModel *m_model;
};

struct BfmeShadowEdge
{
	unsigned short m_vertex0;
	unsigned short m_pad02;
	unsigned short m_vertex1;
	unsigned short m_pad06;
};

struct Rva00107E76Elem
{
	BfmeShadowMesh *m_mesh;
	Vector3 *m_allocation0;
	unsigned char *m_allocation1;
	BfmeShadowEdge *m_allocation2;
	unsigned int m_reserved10;
	unsigned char m_reserved14;

	void rva00107B41(Vector3 *vertex, short vertexBase, unsigned short *index,
		const Vector3 &offset);
};

// Same thiscall ABI (four dwords, ret 0x10) as the erased declaration in
// BfmeVolumetricShadowBufferOwnerRender.cpp, which reaches this body through ILT 0x0003D253.
void Rva00107E76Elem::rva00107B41(Vector3 *vertex, short vertexBase,
	unsigned short *index, const Vector3 &offset)
{
	Vector3 dir = offset;
	dir.Normalize();
	dir *= 0.1f;
	int count = m_mesh->m_model->m_vertexCount;
	int i, j;
	for (i = 0; i < count; ++i)
		*vertex++ = m_allocation0[i] + dir;
	for (j = 0; j < count; ++j)
		*vertex++ = m_allocation0[j] + offset;

	BfmeShadowEdge *edge = m_allocation2;
	for (int e = m_reserved10; e > 0; --e, ++edge, index += 6)
	{
		index[0] = (unsigned short)(edge->m_vertex0 + count) + vertexBase;
		index[1] = edge->m_vertex1 + vertexBase;
		index[2] = edge->m_vertex0 + vertexBase;
		index[3] = edge->m_vertex1 + vertexBase;
		index[4] = (unsigned short)(edge->m_vertex0 + count) + vertexBase;
		index[5] = (unsigned short)(edge->m_vertex1 + count) + vertexBase;
	}

	unsigned char *front = m_allocation1;
	BfmeShadowTriIndex *tri = m_mesh->m_model->m_poly->m_data;
	int polyCount = m_mesh->m_model->m_polyCount;
	for (int t = 0; t < polyCount; ++t, index += 3, ++front, ++tri)
	{
		if (*front)
		{
			index[0] = tri->I + vertexBase;
			index[1] = tri->J + vertexBase;
			index[2] = tri->K + vertexBase;
		}
		else
		{
			index[0] = vertexBase + count + tri->I;
			index[1] = (unsigned short)(tri->J + count) + vertexBase;
			index[2] = (unsigned short)(tri->K + count) + vertexBase;
		}
	}
}
