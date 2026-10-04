// ?rva00094B08@@YAXPAURva00094B08FloatBlock@@@Z
// partial score=1.0 date=2026-10-05
// cl: /O2 /Ob1 /GX- /GS /arch:SSE /Fabuild/seat3/FieldInitialiser95.asm /Fdbuild/seat3/FieldInitialiser95.pdb
// Whole S3FieldInitialisers.cpp @5cc75ddda6455c338a5068307e587a793f96d6b3.
// Blob 584d838f233b527410f172b70f9e5b20678e16a7; no headers.
// Target witnesses sixteen float stores through one CDECL pointer.
// The original owner/name and a standalone target entry remain unproved.
struct Rva00094B08FloatBlock {float values[16];};
void rva00094B08(Rva00094B08FloatBlock *p)
{
 p->values[1]=p->values[2]=p->values[3]=
 p->values[4]=p->values[6]=p->values[7]=
 p->values[8]=p->values[9]=p->values[11]=
 p->values[12]=p->values[13]=p->values[14]=0.0f;
 p->values[0]=p->values[5]=p->values[10]=p->values[15]=1.0f;
}