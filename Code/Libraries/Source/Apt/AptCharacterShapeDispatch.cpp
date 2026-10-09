// cl: /O2 /DNDEBUG /MD
// AptCharacter.cpp workers. Native entries and ret12 prove complete148B
// BD30..BDC3 and125B BDD0..BE4C extents. WB1780C70 guides dispatch semantics.
// Type values, ID+18 and rectangle+8 are target accesses; no class name
// or full layout is claimed. The callback is a private view of one gAptFuncs
// slot at VA E177A8 whose retail initial word is zero, not its original owner.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char*test,int line){g_bfmeAptAssertAtE17734(test,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
class AptRenderingContext {public:void pushVertexMatrix();void popVertexMatrix();};
class BfmeThingDXH {public:void bfmeGoDXH(void*);};
class BfmeThingXS {public:void bfmeApplyXS(void*,void*);};
static void (__cdecl *drawShapeCallback)(unsigned int,void*)=0;
struct Rva006EBD30 {int type;char unknown04[0x14];unsigned int shapeId;
 void render(AptRenderingContext*,void*,void*);
 void bounds(AptRenderingContext*,void*,void*);
};
void Rva006EBD30::render(AptRenderingContext *context,void *argument,void *matrix){
 if(matrix){context->pushVertexMatrix();((BfmeThingDXH*)context)->bfmeGoDXH(matrix);}
 switch(type){
 case 1:if(!shapeId)aptAssert("shape.zID",0x46);drawShapeCallback(shapeId,argument);break;
 case 11:break;
 default:aptAssert("NOT_REACHED",0x53);break;
 }
 if(matrix)context->popVertexMatrix();
}
void Rva006EBD30::bounds(AptRenderingContext *context,void *argument,void *matrix){
 if(matrix){context->pushVertexMatrix();((BfmeThingDXH*)context)->bfmeGoDXH(matrix);}
 switch(type){
 case 1:((BfmeThingXS*)context)->bfmeApplyXS(argument,(char*)this+8);break;
 case 10:((BfmeThingXS*)context)->bfmeApplyXS(argument,(char*)this+8);break;
 case 11:break;
 default:aptAssert("NOT_REACHED",0x8E);break;
 }
 if(matrix)context->popVertexMatrix();
}
