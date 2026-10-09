// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1 f98983a7d W3DStatusCircle::updateScreenVB supplies the quad layout.
// Native 8E335..8E436 RET4 and W3DStatusCircle render caller 8E7A4 agree;
// target screen VB is +E4 and the shared dirty byte is VA DE207C. Earlier
// bank called this TerrainTracksRenderObjClass; the semantic donor identifies
// the status-circle subsystem. -1/+1 are compiler literals, independently
// verified in target .rdata; declaring them extern globals hoisted the load.
class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *b, int flags);
		~WriteLockClass();
		VertexBufferClass *m_buf;
		void *Vertices;
		char m_lock;
	};
};

struct StatusVert
{
	float x, y, z;
	unsigned int color;
	float u, v;
};




class W3DStatusCircle { public: int updateScreenVB(int); int updateCircleVB(); static int m_diffuse; char head[0xC4]; int m_numTriangles; char padC8[0x18]; VertexBufferClass *m_vb1,*m_vb2; };
extern unsigned char g_trackDirty;
int W3DStatusCircle::updateScreenVB(int color)
{
	VertexBufferClass *vb = (VertexBufferClass *)m_vb2;
	if (vb != 0)
	{
		g_trackDirty = false;
		VertexBufferClass::WriteLockClass lock(vb, 0);
		StatusVert *v = (StatusVert *)lock.Vertices;
		unsigned c = color;
		float a = -1.0f;
		v->color = c;
		float b = 1.0f;
		v->x = a; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = a; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = a; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f;
		return 0;
	}
	return -1;
}
#include "vector3.h"
int W3DStatusCircle::m_diffuse=255;
// BF1 f98983a7d W3DStatusCircle::updateCircleVB donor; native 8E623..8E7A4.
// Retain actual donor WWMath operators: a simplified local Vector3 preserves
// arithmetic but changes SSE register/scheduling and is not a byte match.
// Target circle buffer is E0 and triangle count C4; diffuse DB45C8 starts255.
int W3DStatusCircle::updateCircleVB(void)
{
	int i, k;
	float shade;
	VertexBufferClass	*pVB = m_vb1;
	if (m_vb1 )
	{
		g_trackDirty = false;
		VertexBufferClass::WriteLockClass lockVtxBuffer(pVB,0);
		StatusVert *vb = (StatusVert*)lockVtxBuffer.Vertices;
		
		const float theZ = 0.0f;
		const float theRadius = 0.02f;
		const int theAlpha = 127;
	  int diffuse = m_diffuse + (theAlpha<<24);	 // b g<<8 r<<16 a<<24.		 
		int limit = m_numTriangles;
		float curAngle = 0;
		float deltaAngle = 2*3.14159265358979323846f/limit;
		for (i=0; i<limit; i++)
		{
			
			shade=0.7f*255.0f;
			for (k=0; k<3; k++) {
				vb->z=  theZ;
				if (k==0) {
					vb->x=	0;
					vb->y=	0;
				} else if (k==1) {
					Vector3 vec(theRadius,0,theZ);
					vec.Rotate_Z(curAngle);
					vb->x=	vec.X;
					vb->y=	vec.Y;
				} else if (k==2) {
					float angle = curAngle+deltaAngle;
					if (i==limit-1) {
						angle = 0;
					} 
					Vector3 vec(theRadius,0,theZ);
					vec.Rotate_Z(angle);
					vb->x=	vec.X;
					vb->y=	vec.Y;
				}
				vb->color = diffuse; 
				vb->u=0;
				vb->v=0;
				vb++;
			}
			curAngle += deltaAngle;
			
		}
		return 0; //success.
	}
	return -1;
}

