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
class Vector3 {public:float X,Y,Z;__forceinline Vector3(){} __forceinline Vector3(float x,float y,float z){X=x;Y=y;Z=z;} __forceinline Vector3(const Vector3&vec){X=vec.X;Y=vec.Y;Z=vec.Z;} __forceinline Vector3&operator=(const Vector3&vec){X=vec.X;Y=vec.Y;Z=vec.Z;return *this;} __forceinline void Normalize(){float len2=X*X+Y*Y+Z*Z;if(len2!=0.0f){float oolen=WWMath::Inv_Sqrt(len2);X*=oolen;Y*=oolen;Z*=oolen;}}};
// LINK: file-static helpers replace operator*= and operator+ (identical inlined
// bytes); the TU no longer emits their loser COMDAT copies. No flags touched.
static __forceinline void bfmeScaleV3(Vector3&vec,float k){vec.X*=k;vec.Y*=k;vec.Z*=k;}
static __forceinline Vector3 bfmeSumV3(const Vector3&lhs,const Vector3&rhs){return Vector3(lhs.X+rhs.X,lhs.Y+rhs.Y,lhs.Z+rhs.Z);}
static __forceinline Vector3 bfmeAddV3(const Vector3&lhs,const Vector3&rhs){Vector3 sum;sum.X=lhs.X+rhs.X;sum.Y=lhs.Y+rhs.Y;sum.Z=lhs.Z+rhs.Z;return sum;}


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
	int m_vertex0;
	int m_vertex1;
};

struct Rva00107E76Elem
{
	BfmeShadowMesh *m_mesh;
	Vector3 *m_allocation0;
	unsigned char *m_allocation1;
	BfmeShadowEdge *m_allocation2;
	int m_reserved10;
	unsigned char m_reserved14;

	void rva00107B41(Vector3 *vertex, short vertexBase, unsigned short *index,
		const Vector3 &offset);
	int rva00106D56(int vertexBuf, short vertexBase, int indexBuf, void *block);
};

// Same thiscall ABI (four dwords, ret 0x10) as the erased declaration in
// BfmeVolumetricShadowBufferOwnerRender.cpp, which reaches this body through ILT 0x0003D253.
void Rva00107E76Elem::rva00107B41(Vector3 *vertex, short vertexBase,
	unsigned short *index, const Vector3 &offset)
{
	Vector3 dir = offset;
	dir.Normalize();
	bfmeScaleV3(dir,0.1f);
	int count = m_mesh->m_model->m_vertexCount;
	int i, j;
	for (i = 0; i < count; ++i)
		*vertex++ = bfmeAddV3(m_allocation0[i],dir);
	for (j = 0; j < count; ++j)
		*vertex++ = bfmeAddV3(m_allocation0[j],offset);

	BfmeShadowEdge *edge = m_allocation2;
	for (int edgesLeft = m_reserved10; edgesLeft > 0; --edgesLeft, ++edge, index += 6)
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
	for (int triIndex = 0; triIndex < polyCount; ++triIndex, index += 3, ++front, ++tri)
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

// Native106D56..106F71 complete539 RET16; the sole caller UpdateAndRender
// 0x00107D8A passes the vertex/index cursors as integers (the pinned
// spelling). WB 0x008DE7E0 (vector3.h operator+ asserts) gives the loop
// shapes: either two vertex rings plus six indices per edge, or four
// vertices per edge with packed index pairs, whichever needs fewer vertices.
int Rva00107E76Elem::rva00106D56(int vertexBuf, short vertexBase, int indexBuf,
	void *block)
{
	Vector3 *&vertex = reinterpret_cast<Vector3 *&>(vertexBuf);
	unsigned short *&index = reinterpret_cast<unsigned short *&>(indexBuf);
	const Vector3 &offset = *(const Vector3 *)block;
	int count = m_mesh->m_model->m_vertexCount;
	if (count * 2 < m_reserved10 * 4)
	{
		int i, j;
		for (i = 0; i < count; ++i)
			*vertex++ = m_allocation0[i];
		for (j = 0; j < count; ++j)
			*vertex++ = bfmeAddV3(offset, m_allocation0[j]);

		BfmeShadowEdge *edge = m_allocation2;
		for (int edgesLeft = m_reserved10; edgesLeft > 0; --edgesLeft, ++edge, index += 6)
		{
			index[0] = vertexBase + edge->m_vertex0 + count;
			index[1] = vertexBase + edge->m_vertex1;
			index[2] = vertexBase + edge->m_vertex0;
			index[3] = vertexBase + edge->m_vertex1;
			index[4] = vertexBase + edge->m_vertex0 + count;
			index[5] = vertexBase + edge->m_vertex1 + count;
		}
		return count * 2;
	}

	BfmeShadowEdge *edge = m_allocation2;
	for (int edgesLeft = m_reserved10; edgesLeft > 0; --edgesLeft, ++edge, vertex += 4)
	{
		vertex[0] = m_allocation0[edge->m_vertex0];
		vertex[1] = m_allocation0[edge->m_vertex1];
		vertex[2] = bfmeAddV3(m_allocation0[edge->m_vertex0], offset);
		// Re-reading the extrusion through the block pointer is what gives
		// retail's offset-first X add for the last vertex.
		const Vector3 &far1 = m_allocation0[edge->m_vertex1];
		vertex[3] = bfmeAddV3(*(const Vector3 *)block, far1);
	}

	edge = m_allocation2;
	unsigned int *pair = (unsigned int *)index;
	unsigned int base = ((unsigned short)vertexBase << 16) | (unsigned short)vertexBase;
	for (int q = m_reserved10; q > 0; --q, ++edge, pair += 3, base += 0x40004)
	{
		pair[0] = base + 0x10002;
		pair[1] = base + 0x10000;
		pair[2] = base + 0x30002;
	}
	return m_reserved10 * 4;
}
