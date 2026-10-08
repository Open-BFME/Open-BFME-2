// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/shims/w3droadbuffer /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// W3DRoadBuffer::loadLit4PtSection (retail 0x000D869C, 3491 B) lives in its own TU: it needs /G7
// while the rest of W3DRoadBuffer.cpp verifies without it. The older unclaimed ZH copy of
// this function was removed from W3DRoadBuffer.cpp; the ledgered helpers its calls used to
// emit there are now kept emitted explicitly.
//
// Basis. Structure, the ambient-written-into-diffuse-temporary quirk, the Int i,j,k
// ordering and the receiver idea come from the BFME1 donor (game/.../W3DRoadBuffer.cpp);
// the ZH source is the fallback for everything BFME1 lacks. Target-measured deltas
// against the donor: the road-ID compare reads this+0x2c (m_litUniqueID); the height query
// dispatches through TheTerrainRenderObject's vtable slot +0x248; the lit vertex is 0x24
// bytes with a normal; the light-slot NULL fill is min(numLights,8) shaped; the shade clamps
// are plain sequential ifs; the diffuse conversion is x87 (_ftol) with a float 255.0f pool
// constant, which this compiler only emits when the result is stored to an unsigned lvalue.
// Inference (not target-proven): the normal query is wrapped in a small inline helper that
// returns the vector by value. Only that spelling reproduces retail's scheduling of the
// normal loads (the caller's copy is not address-exposed) and the shared stack slot with the
// light loop's uninitialised `ambient`.
#define Matrix4x4 Matrix4  // BFME renamed it

#include "W3DDevice/GameClient/W3DRoadBuffer.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"

//#include "Common/GameFileSystem.h"

// BFME2-only pieces of loadLit4PtSection (retail-measured; identities open).
// Retail's lit road vertex is 0x24 bytes: x,y,z, a normal at +0xc..+0x14,
// diffuse at +0x18, u1 at +0x1c, v1 at +0x20 (ZH's VertexFormatXYZDUV1 is 0x18).
// The normal comes from a call at 0x0006AA45 on the dword at
// TheTerrainRenderObject+0x37C0 taking (x, y, Vector3 *out) with x and y the
// vertex position over MAP_XY_FACTOR rounded to Int, and the static diffuse is
// read through 0x0006B4CC with a constant 1 as third argument. Both are
// unclaimed bodies here, so they are declared as opaque one-method classes.
// Retail dispatches the terrain height query through TheTerrainRenderObject's
// vtable slot +0x248 (two floats in, x87 Real out); ZH has it non-virtual. Slots
// 0..145 below are placeholders that only position the entry.
class RoadTerrainVtbl
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void s131();
	virtual void s132();
	virtual void s133();
	virtual void s134();
	virtual void s135();
	virtual void s136();
	virtual void s137();
	virtual void s138();
	virtual void s139();
	virtual void s140();
	virtual void s141();
	virtual void s142();
	virtual void s143();
	virtual void s144();
	virtual void s145();
	virtual Real getMaxCellHeight(Real x, Real y) const;
};
class Rva0006AA45 { public: void call(Int x, Int y, Vector3 *out); };
// Inline wrapper the vertex loop reads the normal through (see the basis note above).
static __forceinline Vector3 RoadGetNormal(Rva0006AA45 *m, Int x, Int y)
{
	Vector3 n;
	m->call(x, y, &n);
	return n;
}
class Rva0006B4CC { public: Int call(Int x, Int y, Int z); };
struct RoadLitVertex {
	Real x, y, z;
	Real nx, ny, nz;
	unsigned diffuse;
	Real u1, v1;
};

//=============================================================================
// W3DRoadBuffer::loadLit4PtSection
//=============================================================================
/** Loads a section of road using a mesh that floats a little above the 
terrain.  The road is loaded into the quadrilateral defined by the
4 corners points.  loc specifies the point where u==uOffset && v==vOffset, and 
the road vector gives the direction of the road, and the road normal is perpendicular
to the road normal.  */
//=============================================================================
void W3DRoadBuffer::loadLit4PtSection(RoadSegment *pRoad, UnsignedShort *ib, VertexFormatXYZDUV1 *vb, RefRenderObjListIterator *pDynamicLightsIterator)
{
	
	const Real FLOAT_AMOUNT = MAP_HEIGHT_SCALE/8;
	const Real MAX_ERROR = MAP_HEIGHT_SCALE*1.1f;

	
	if (pRoad->m_uniqueID != m_litUniqueID) return;
	if (!pRoad->m_visible) {
		return;
	}
	Int i, j, k;
	Int numLights = 0;
	const Int maxLights = 8;
	LightClass *lights[maxLights];

	for (pDynamicLightsIterator->First(); !pDynamicLightsIterator->Is_Done(); pDynamicLightsIterator->Next()) {		
			LightClass *pLight = (LightClass*)pDynamicLightsIterator->Peek_Obj();
			SphereClass bounds = pLight->Get_Bounding_Sphere();
			if (Spheres_Intersect(pRoad->getBounds(), bounds)) {
				lights[numLights] = pLight;
				numLights++;
				if (numLights == maxLights) break;
			}
	}


	for (i=(numLights < maxLights) ? numLights : maxLights; i<maxLights; ++i) lights[i] = NULL;
	// Keep this declaration at retail's local-class ordinal (17).
	const int maxRows = 100;
	typedef struct {
		Bool collapsed;
		Bool deleted;
		Vector3 vtx[maxRows];
		Int diffuseRed;
		Bool lightGradient;
		Int vertexIndex[maxRows];
		Real uIndex;
	} TColumn;
	if (numLights == 0) return;

	TRoadSegInfo info;
	pRoad->GetRoadSegInfo(&info);
	Real roadLen = info.roadVector.Length();
	Real halfHeight = info.roadNormal.Length();
	info.roadNormal.Normalize();
	info.roadVector.Normalize();
	Vector2 curVector;
	Int uCount = (roadLen/MAP_XY_FACTOR)+1;
	Int vCount = (2*halfHeight/MAP_XY_FACTOR)+1;



//	const Int DIFFUSE_LIMIT = 25; // if more than that, we tesselate :) jba.

	if (vCount>maxRows) vCount = maxRows;
	TColumn prevColumn, curColumn, nextColumn;
				
	prevColumn.deleted = true;
	curColumn.deleted = true;
	Vector2 v2 = info.corners[bottomLeft];
	Vector3 origin(v2.X, v2.Y, 0);
	v2 = info.corners[bottomRight] - info.corners[bottomLeft];
	Vector3 uVector1(v2.X, v2.Y, 0);
	v2 = info.corners[topRight] - info.corners[topLeft]; 
	Vector3 uVector2(v2.X, v2.Y, 0);
	v2 = info.corners[topLeft];
	Vector3 origin2(v2.X, v2.Y, 0);
	v2 = info.corners[topLeft] - info.corners[bottomLeft];
	Vector3 vVector1(v2.X, v2.Y, 0);
	v2 = info.corners[topRight] - info.corners[bottomRight];
	Vector3 vVector2(v2.X, v2.Y, 0);
	uVector2 += (vVector1 - vVector2);
	for (i=0; i<=uCount; i++) {
		Real iFactor = ((Real)i / (uCount-1));
		Real iBarFactor = 1.0f-iFactor;
		if (i<uCount) {
			nextColumn.collapsed = false;
			nextColumn.deleted = false;
			nextColumn.lightGradient = false;
			nextColumn.uIndex = i;

			// BFME height samples are 16-bit and use a 0.0390625 scale.
			Real minHeight=65535.0f*(MAP_HEIGHT_SCALE/16);
			Real maxHeight = m_map->getMinHeightValue()*MAP_HEIGHT_SCALE;
			for (j=0; j<vCount; j++) {
				Real jFactor = ((Real)j / (vCount-1));
				Real jBarFactor = 1.0f-jFactor;
				nextColumn.vtx[j] = origin +  (uVector1 * jBarFactor * iFactor) + (uVector2 * jFactor * iFactor) +
													(vVector1 * iBarFactor * jFactor) + (vVector2 * iFactor * jFactor) ;	
				Real z = ((RoadTerrainVtbl *)TheTerrainRenderObject)->getMaxCellHeight(nextColumn.vtx[j].X, nextColumn.vtx[j].Y);
				if (z<minHeight) minHeight = z;
				if (z>maxHeight) maxHeight = z;
				nextColumn.vertexIndex[j] = -1;
				nextColumn.vtx[j].Z = z;
				Int k;
				for (k=0; k<numLights; k++) {
					Vector3 offset = nextColumn.vtx[j] - lights[k]->Get_Position();
					Real range = lights[k]->Get_Attenuation_Range();
					// for culling, expand one cell radius.
					range += MAP_XY_FACTOR;
					if (offset.Length2() < range*range) {
						nextColumn.lightGradient = true;
					}
				}
			}
			if (!nextColumn.lightGradient) {
				nextColumn.collapsed = true;
				nextColumn.vtx[0].Z = maxHeight;
				nextColumn.vtx[1] = nextColumn.vtx[vCount-1];
				nextColumn.vtx[1].Z = maxHeight;
			}	else {
				for (j=0; j<vCount; j++) {
					nextColumn.vtx[j].Z = maxHeight;
				}
			}
			if (i<2) {
				curColumn = nextColumn;
			} else {
				if (prevColumn.collapsed && curColumn.collapsed && nextColumn.collapsed) {
					Bool okToDelete = false;

					Real theZ = prevColumn.vtx[0].Z * (curColumn.uIndex-prevColumn.uIndex) + 
										nextColumn.vtx[0].Z * (nextColumn.uIndex-curColumn.uIndex);
					theZ /= nextColumn.uIndex-prevColumn.uIndex;
					if (theZ >= curColumn.vtx[0].Z && theZ < curColumn.vtx[0].Z + MAX_ERROR) {
						theZ = prevColumn.vtx[1].Z * (curColumn.uIndex-prevColumn.uIndex) + 
											nextColumn.vtx[1].Z * (nextColumn.uIndex-curColumn.uIndex);
						theZ /= nextColumn.uIndex-prevColumn.uIndex;
						if (theZ >= curColumn.vtx[1].Z && theZ < curColumn.vtx[1].Z + MAX_ERROR) {
							okToDelete = true;
						}
					}
					if (okToDelete) {
						curColumn.deleted = true;
					}				
				}
			}
		}
		if (!curColumn.deleted && i!=1) {
			// Write out the vertices.
			for (j=0; j<vCount; j++) {
				Real U, V;
				if (m_curNumRoadVertices >= m_maxRoadVertex) {
					break;
				}
				curVector.Set(curColumn.vtx[j].X - info.loc.X, curColumn.vtx[j].Y - info.loc.Y);
				V = Vector2::Dot_Product(info.roadNormal, curVector);
				U = Vector2::Dot_Product(info.roadVector, curVector);
				Int diffuse = (255<<24)|((Rva0006B4CC *)TheTerrainRenderObject)->call(curColumn.vtx[j].X/MAP_XY_FACTOR+0.5, curColumn.vtx[j].Y/MAP_XY_FACTOR+0.5, 1);
				Real shadeR, shadeG, shadeB;
				shadeB = (diffuse & 0xFF)/255.0;
				shadeG = ((diffuse>>8) & 0xFF)/255.0;
				shadeR = ((diffuse>>16) & 0xFF)/255.0;
				Int k;
				for (k=0; k<numLights; k++) {
					Real factor;
					if (lights[k]->Get_Type() == LightClass::POINT) {
						Vector3 lightLoc = lights[k]->Get_Position();
						Vector3 vtx = curColumn.vtx[j];
						Vector3 offset = vtx - lightLoc;
						double range, midRange;
						lights[k]->Get_Far_Attenuation_Range(midRange, range);
						if (vtx.X < lightLoc.X-range) continue;
						if (vtx.X > lightLoc.X+range) continue;
						if (vtx.Y < lightLoc.Y-range) continue;
						if (vtx.Y > lightLoc.Y+range) continue;
						Real dist = offset.Length();
						if (dist >= range) continue;
						if (midRange < 0.1) continue;
	#if 1
						factor = 1.0f - (dist - midRange) / (range - midRange);
	#else
						// f = 1.0 / (atten0 + d*atten1 + d*d/atten2);
						if (fabs(range-midRange)<1e-5)	{
							// if the attenuation range is too small assume uniform with cutoff
							factor = 1.0;
						}	else  {
							factor = 1.0f/(0.1+dist/midRange + 5.0f*dist*dist/(range*range));
						}
	#endif
						factor = WWMath::Clamp(factor,0.0f,1.0f);
						Real shade = 0.5f; 
						shade *= factor;
						Vector3 diffuse;
						lights[k]->Get_Diffuse(&diffuse);
						Vector3 ambient;
						// Retail writes Ambient (+0xd8) to the diffuse temporary; ambient itself remains uninitialized.
						lights[k]->Get_Ambient(&diffuse);
						if (shade > 1.0) shade = 1.0;
						if(shade < 0.0f) shade = 0.0f;
						shadeR = (shadeR + shade*diffuse.X) + factor*ambient.X;
						shadeG = (shadeG + shade*diffuse.Y) + factor*ambient.Y;
						shadeB = (shadeB + shade*diffuse.Z) + factor*ambient.Z;
					}
				}
 				if (shadeR > 1.0) shadeR = 1.0;
				if(shadeR < 0.0f) shadeR = 0.0f;
				if (shadeG > 1.0) shadeG = 1.0;
				if(shadeG < 0.0f) shadeG = 0.0f;
				if (shadeB > 1.0) shadeB = 1.0;
				if(shadeB < 0.0f) shadeB = 0.0f;


			#ifdef _DEBUG
				//diffuse &= 0xFFFF00FF; // strip out green.
			#endif
				{
					Vector3 normal = RoadGetNormal(((Rva0006AA45 *)*(void **)((char *)TheTerrainRenderObject + 0x37C0)), curColumn.vtx[j].X/MAP_XY_FACTOR+0.5, curColumn.vtx[j].Y/MAP_XY_FACTOR+0.5);
					RoadLitVertex *lvb = (RoadLitVertex *)vb;
					lvb[m_curNumRoadVertices].u1 = info.uOffset+U/(info.scale*4);
					lvb[m_curNumRoadVertices].v1 = info.vOffset-V/(info.scale*4);	// Road is 1/16 texture height.
					lvb[m_curNumRoadVertices].x = curColumn.vtx[j].X;
					lvb[m_curNumRoadVertices].y = curColumn.vtx[j].Y;
					lvb[m_curNumRoadVertices].z = curColumn.vtx[j].Z+FLOAT_AMOUNT;
					lvb[m_curNumRoadVertices].diffuse = ((int)255 << 24) | ((unsigned)(shadeR*255.0f) << 16) | ((unsigned)(shadeG*255.0f) << 8) | (unsigned)(shadeB*255.0f);
					lvb[m_curNumRoadVertices].nx = normal.X;
					lvb[m_curNumRoadVertices].ny = normal.Y;
					lvb[m_curNumRoadVertices].nz = normal.Z;
				}
				curColumn.vertexIndex[j] = m_curNumRoadVertices;
				m_curNumRoadVertices++;
				if (j==1 && curColumn.collapsed) {
					break;
				}
			}
			if (m_curNumRoadVertices >= MAX_SEG_INDEX) {
				break;
			}
			if (i>1 && (!prevColumn.collapsed || !curColumn.collapsed)) {
				// Write out the triangles.
				j = 0;
				k = 0;
				while (j<vCount-1 && k<vCount-1) {
					if (m_curNumRoadIndices >= m_maxRoadIndex) {
						break;
					}
					UnsignedShort *curIb = ib+m_curNumRoadIndices;
					if (k==0 || !prevColumn.collapsed) {
						*curIb++ = prevColumn.vertexIndex[j+1];	
						*curIb++ = prevColumn.vertexIndex[j];		
						*curIb++ = curColumn.vertexIndex[k];		
						m_curNumRoadIndices+=3;
					}
					if (j==0 || !curColumn.collapsed) {
						Int offset = 1;
						if (curColumn.collapsed && !prevColumn.collapsed) {
							offset = vCount-1;
						}
						*curIb++ = prevColumn.vertexIndex[j+offset];	
						*curIb++ = curColumn.vertexIndex[k];		
						*curIb++ = curColumn.vertexIndex[k+1];	
						m_curNumRoadIndices+=3;
					}
					if (prevColumn.collapsed && curColumn.collapsed) {
						break;
					}
					if (!prevColumn.collapsed) {
						j++;
					}
					if (!curColumn.collapsed) {
						k++;
					}
				}
				prevColumn = curColumn;
			}	else if (i==0) {
				prevColumn = curColumn;
			}
			if (m_curNumRoadIndices >= MAX_SEG_INDEX) {
				break;
			}
		}
		curColumn = nextColumn;
	}
}
																 
