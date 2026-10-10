// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// Native3FE1DB52B and3FE25D229B share unchanged receiver in WB1074010
// named LivingWorldArmyIcon::continueMoving. Rehome both already-published
// methods and give the queue helper its actual enclosing owner. Its original
// method name remains unknown. Current18/1C, queue3C anddestination50/54 are
// separate native accesses. Queue returns the verified16B Snapshot record.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "Coord2D.h"
struct Rva00538E43Coord : Coord2D {
 Rva00538E43Coord(){x=0;y=0;}
 Rva00538E43Coord(const Rva00538E43Coord &v){x=v.x;y=v.y;}
};
class Rva00318B5C : public Snapshot {
public:
 Rva00318B5C();
 Rva00318B5C(const Rva00318B5C&);
 virtual ~Rva00318B5C(){}
 virtual void loadPostProcess(){}
 virtual const char* GetSnapshotName() const;
 virtual void xfer(Xfer*);
 Rva00538E43Coord coordinate;int command;
};
struct Rva00538E22 {
 Rva00318B5C *begin,*end,*capacity;int value;
 Rva00318B5C rva00538E43();
};
struct Rva00538E43Pair {
 float x,y;
 Rva00538E43Pair(float a,float b):x(a),y(b){}
 ~Rva00538E43Pair(){}
};
extern "C" double __cdecl sqrt(double);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva003FE13E {public:float rva003FE13E();};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class Vector3 {public:float X,Y,Z;};
class Rva002B4C09 {public:bool rva002B4C09();};
class Rva003FDEAD {public:void rva003FDFFB();};
class Rva003FDE8C {public:void rva003FDE8C(unsigned char);};
class Rva002BF4F3 {public:bool rva002BF5B0(const Vector3*,Vector3*);};
class Rva003FE342Virtual {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5(Vector3*);};
class LivingWorldArmyIcon {
public:
 void rva003FE1DB();
 void rva003FE342();
 void continueMoving(Coord2D *out);
private:
 char unknown0[0x18];Coord2D current;
 char unknown20[0x3C-0x20];Rva00538E22 queue;
 char unknown4C[4];Coord2D destination;
 char unknown58[4];bool active;
};
void LivingWorldArmyIcon::rva003FE1DB() {
 Rva00538E22 *vec=&queue;
 unsigned count=vec->end-vec->begin;
 if(0u<count){Rva00318B5C front=queue.rva00538E43();destination=front.coordinate;}
 else active=false;
}

// Complete native 229B RET4 and WB1074010 establish this movement step.
// The speed helper and queue advance retain their address-derived names.
// Ordered current reads preserve retail's loads after displacement construction.
// The output barrier retains the native x reload; newY stays a local because
// the native subtraction reuses its value rather than loading out->y again.
void LivingWorldArmyIcon::continueMoving(Coord2D *out)
{
	Coord2D d;
	d.x = destination.x - current.x;
	d.y = destination.y - current.y;
	float squared = d.x * d.x + d.y * d.y;
	if (squared > 0.001) {
		float inverse = 1.0f / (float)sqrt(squared);
		d.x *= inverse;
		d.y *= inverse;
	}
	float step = ((Rva003FE13E *)this)->rva003FE13E();
	Rva00538E43Pair displacement(step * d.x, step * d.y);
	out->x = *reinterpret_cast<const volatile float *>(&current.x) + displacement.x;
	float newY = *reinterpret_cast<const volatile float *>(&current.y) + displacement.y;
	out->y = newY;
	_ReadWriteBarrier();
	d.x = destination.x;
	d.y = destination.y;
	d.x -= out->x;
	d.y -= newY;
	if (d.length() < 1.0f)
		rva003FE1DB();
}


// Native 192B step: while the world logic gate allows it, latch the next
// queued destination, then advance toward it and report the new position
// through virtual slot 5. Names are address-derived; the gate, the point
// helper on 0xDFEF18 and the slot-5 callee are rowed or read from retail.
void LivingWorldArmyIcon::rva003FE342()
{
	if (((Rva002B4C09 *)TheLivingWorldLogic)->rva002B4C09()) {
		bool was=active;
		if (!was) {
			Rva00538E22 *vec=&queue;
			if (0u<(unsigned)(vec->end-vec->begin)) {
				Rva00318B5C front=queue.rva00538E43();
				destination=front.coordinate;
				active=true;
				((Rva003FDEAD *)this)->rva003FDFFB();
				((Rva003FDE8C *)this)->rva003FDE8C(0);
			}
		}
		if (active) {
			Coord2D step;
			continueMoving(&step);
			Vector3 v;
			v.X=step.x;
			v.Y=step.y;
			v.Z=0.0f;
			((Rva002BF4F3 *)g_00DFEF18)->rva002BF5B0((const Vector3 *)&step,&v);
			((Rva003FE342Virtual *)this)->s5(&v);
		}
	}
}
