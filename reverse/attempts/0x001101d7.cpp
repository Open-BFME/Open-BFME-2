// ?Rva001101D7Draw@@YIXPAXPAURva001101D7@@ABUV2@@2MK@Z
// partial score=0.9805 date=2026-10-09
// cl: /DNDEBUG /MD /EHs-c- /Oy- /O1 /arch:SSE
extern "C" double __cdecl fabs(double);
class WWMath { public: static float __fastcall Inv_Sqrt(float); };
struct V2 {float X,Y; void Scale(double k) {X*=k;Y*=k;} };
struct Vertex {float X,Y,Z; unsigned long Color; char rest[16];};
struct Rva001101D7 {Vertex *Next;};
void __fastcall Rva001101D7Draw(void *unused,Rva001101D7 *sink,const V2 &a,const V2 &b,float width,unsigned long color)
{
 if(!sink->Next) return;
 V2 offset; offset.X=a.Y-b.Y; offset.Y=b.X-a.X;
 float len2=offset.X*offset.X+offset.Y*offset.Y;
 if(fabs(len2<=0.0001f)!=0.0) {offset.X=0.0f;offset.Y=0.0f;}
 else {double k=WWMath::Inv_Sqrt(len2)*width*0.5f;offset.Scale(k);}
 sink->Next->X=a.X-offset.X; sink->Next->Y=a.Y-offset.Y; sink->Next->Z=0.0f; sink->Next->Color=color; ++sink->Next;
 sink->Next->X=a.X+offset.X; sink->Next->Y=a.Y+offset.Y; sink->Next->Z=0.0f; sink->Next->Color=color; ++sink->Next;
 sink->Next->X=b.X-offset.X; sink->Next->Y=b.Y-offset.Y; sink->Next->Z=0.0f; sink->Next->Color=color; ++sink->Next;
 sink->Next->X=b.X-offset.X; sink->Next->Y=b.Y-offset.Y; sink->Next->Z=0.0f; sink->Next->Color=color; ++sink->Next;
 sink->Next->X=a.X+offset.X; sink->Next->Y=a.Y+offset.Y; sink->Next->Z=0.0f; sink->Next->Color=color; ++sink->Next;
 sink->Next->X=b.X+offset.X; sink->Next->Y=b.Y+offset.Y; sink->Next->Z=0.0f; sink->Next->Color=color; ++sink->Next;
}
