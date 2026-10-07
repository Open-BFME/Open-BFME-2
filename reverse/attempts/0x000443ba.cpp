// ?rva000443BA@@YAXPBURva000443BARow@@MPAPAURva000443BALight@@@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
// Native443BA..4443E RET0; four 36-byte lighting records and nine light floats.
struct Rva000443BAVec {
 float x,y,z;
 Rva000443BAVec(float a,float b,float c) : x(a),y(b),z(c) {}
 Rva000443BAVec &operator=(const Rva000443BAVec &v) { x=v.x; y=v.y; z=v.z; return *this; }
};
struct Rva000443BALight {
 char pad[0xd4]; Rva000443BAVec ambient,diffuse,specular;
 void setAmbient(const Rva000443BAVec &v) { ambient=v; }
 void setDiffuse(const Rva000443BAVec &v) { diffuse=v; }
 void setSpecular(const Rva000443BAVec &v) { specular=v; }
};
struct Rva000443BARow { float ambient[3],diffuse[3],position[3]; };
static __declspec(noinline) void rva000443BA(const Rva000443BARow *rows, float scale, Rva000443BALight **lights)
{
 for (int i=0;i<4;++i) {
  if (!lights[i]) continue;
  lights[i]->setAmbient(Rva000443BAVec(0,0,0));
  lights[i]->setDiffuse(Rva000443BAVec(rows[i].diffuse[0]*scale,rows[i].diffuse[1] * *(const volatile float *)&scale,rows[i].diffuse[2]*scale));
  lights[i]->setSpecular(Rva000443BAVec(0,0,0));
 }
}
// ?rva000443BACaller absent-from-retail
void rva000443BACaller(const Rva000443BARow *rows,float scale,Rva000443BALight **lights)
{ rva000443BA(rows,scale,lights); }
