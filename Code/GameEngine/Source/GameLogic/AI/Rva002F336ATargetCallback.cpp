// cl: /O1 /G7 /arch:SSE /MD
// Native2F336A..2F3392: RET8 preserves AL from target query. Receiver
// fields and nine argument slots are measured, original context identity unknown.
struct Coord3D;
class Rva002CB35CObj;
class Pathfinder { public: bool CheckForTarget(void *,void *,void *,Rva002CB35CObj *,void *,void *,void *,void *,Coord3D *); };
class Rva002F336AOwner {
public: bool rva002F336A(int,int);
private:
 Pathfinder *pf;
 void *object;
 unsigned char mode;unsigned char pad[3];
 void *radius;
 Coord3D *out;
 void *target,*targetPosition;
 Rva002CB35CObj *weapon;
};
bool Rva002F336AOwner::rva002F336A(int x,int y) {
 typedef bool(Pathfinder::*Query)(void *,int,int,Rva002CB35CObj *,void *,void *,void *,unsigned char,Coord3D *);
 return (pf->*reinterpret_cast<Query>(&Pathfinder::CheckForTarget))(object,x,y,weapon,target,targetPosition,radius,mode,out);
}
