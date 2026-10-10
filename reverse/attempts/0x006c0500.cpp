// ?rva006C0500@BfmeBoxF0@@QBE_NPBV1@@Z
// partial score=0.9598004546602676 date=2026-10-10
// ?rva006C0500@BfmeBoxF0@@QBE_NPBV1@@Z
// partial score=0.9502967921 date=2026-10-09
// cl: /I. /DNDEBUG /MD /EHsc
// SAT box overlap called by owned6C0630. Same32B box layout as owned
// CircleBoxTest's contains method. Native6C0500..6C0627 proves all four
// projection tests and evaluation order; no original method name claimed.
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
static __forceinline float dot(float ax,float ay,float bx,float by){return ax*bx+ay*by;}
static __forceinline float absf(float x){return (float)fabs(x); }
typedef float Real;
class BfmeBoxF0 {public:
 bool rva006C0500(const BfmeBoxF0 *) const;
 Real m_centerX,m_centerY,m_axisX,m_axisY,m_perpX,m_perpY,m_extentX,m_extentY;
};
bool BfmeBoxF0::rva006C0500(const BfmeBoxF0 *b) const {
 Real d[2];Real y=(this ? b->m_centerY : b->m_centerY);Real x=b->m_centerX;d[0]=x-m_centerX;d[1]=y-m_centerY;
 Real c[4];
 c[0]=(Real)absf(dot(b->m_axisX,b->m_axisY,m_axisX,m_axisY));
 c[1]=(Real)absf(dot(b->m_perpX,b->m_perpY,m_axisX,m_axisY));
 if(absf(dot(d[0],d[1],m_axisX,m_axisY))>c[1]*b->m_extentY+c[0]*b->m_extentX+m_extentX)return false;
 c[2]=(Real)absf(dot(b->m_axisX,b->m_axisY,m_perpX,m_perpY));
 c[3]=(Real)absf(dot(b->m_perpX,b->m_perpY,m_perpX,m_perpY));
 if(absf(dot(d[0],d[1],m_perpX,m_perpY))>c[3]*b->m_extentY+c[2]*b->m_extentX+m_extentY)return false;
 if(absf(dot(d[0],d[1],b->m_axisX,b->m_axisY))>c[0]*m_extentX+c[2]*m_extentY+b->m_extentX)return false;
 if(absf(dot(d[0],d[1],b->m_perpX,b->m_perpY))>c[1]*m_extentX+c[3]*m_extentY+b->m_extentY)return false;
 return true;
}
