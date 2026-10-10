// Native1E685F..1E68D7 RET12; WB ADF040 and owned1E702E forwarder
// establish the same receiver and matrix-copy/turn/pivot sequence. The source
// matrix begins at object+08 and three16-byte rows populate receiver+68.
// Row setters copy four words each; whole-matrix assignment emits REP MOVS.
// The existing address-derived three-word signature is retained: objectWord
// is the first caller pointer and the other words are passed as pointer bits
// to the now-owned turn/pivot worker. Original API type spelling is unproven.
// Row storage/layout and complete calls are target evidence; no donor layout
// or class extent is claimed.
// cl: /O1 /DNDEBUG /MD
class Thing; class Object; struct Coord3D;
class Locomotor {public:float getMaxTurnRate(Object*)const;};
class Rva001E46E1 {public:void rva001E56DC(Object*,const Coord3D*,float,float*);};
struct MatrixRow{unsigned int a,b,c,d;__forceinline void set(const MatrixRow&r){a=r.a;b=r.b;c=r.c;d=r.d;}};
class Thing {public:char prefix[8];MatrixRow matrix[3];};
class Rva001E685F {public:void rva001E685F(int,int,int);char prefix[0x68];MatrixRow matrix[3];};
void Rva001E685F::rva001E685F(int objectWord,int a,int b){
Thing*obj=(Thing*)objectWord;
matrix[0].set(obj->matrix[0]);
matrix[1].set(obj->matrix[1]);
matrix[2].set(obj->matrix[2]);
float turn=((const Locomotor*)this)->getMaxTurnRate((Object*)obj);((Rva001E46E1*)this)->rva001E56DC((Object*)obj,(const Coord3D*)a,turn,(float*)b);}
