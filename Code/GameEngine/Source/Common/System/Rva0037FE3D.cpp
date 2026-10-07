// cl: /ICode/Libraries/Include /O1 /arch:SSE /G7 /DNDEBUG /MD
// Target 0x0037FE3D-0x0037FEA3, 102B, independent Ghidra boundary.
// Empty-list guard: the first pointer names a circular sentinel whose next
// pointer equals itself for an empty list; only this accessed prefix is claimed.
// Initialize start/rally coordinates to (0,0,0)/(1,0,0), ask the 189B
// 0x0037F62D helper for player 0's named start/rally waypoints, then forward
// the nonempty list and resulting coordinates to the 613B 0x0037FAC6 body.
// Target waypoint helper literals Player_%d_Start / Player_%d_Start_Rally
// establish its coordinate output role. The receiver identity, list payload,
// second argument meaning and forwarding operation remain unresolved.
#include "Lib/Coord3D.h"
struct Rva0037FE3DNode { Rva0037FE3DNode* next; };
struct Rva0037FE3DList { Rva0037FE3DNode* head; };
bool __stdcall Rva0037F62DGet(int,Coord3D*,Coord3D*);
class Rva0037FE3D {
public:
    void rva0037FE3D(const Rva0037FE3DList&,int);
    void rva0037FAC6(const Rva0037FE3DList&,const Coord3D*,const Coord3D*,int,int);
};
void Rva0037FE3D::rva0037FE3D(const Rva0037FE3DList& list,int value) {
    if(list.head->next==list.head) return;
    Coord3D first={0.0f,0.0f,0.0f};
    Coord3D second={1.0f,0.0f,0.0f};
    Rva0037F62DGet(0,&first,&second);
    rva0037FAC6(list,&first,&second,value,0);
}
