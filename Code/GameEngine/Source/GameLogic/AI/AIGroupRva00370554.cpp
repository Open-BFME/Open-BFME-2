// cl: /O1 /G7 /arch:SSE /MD /Oy- /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
enum CommandSourceType { CMD_FROM_PLAYER=0,CMD_FROM_SCRIPT=1,CMD_FROM_AI=2 };
class Object;
class AICommandInterface { public: void rva0036EC1D(Object*,CommandSourceType); };
class AIUpdateInterface { public: char pad00[0x20]; AICommandInterface m_commands; };
class Object { public: Object *rva002931F5(bool); char pad00[0x258]; AIUpdateInterface *m_ai; };
class AIGroup { public: void rva00370554(Object*,CommandSourceType); unsigned int pad00; std::list<Object*> m_memberList; };
// Native 00370554..003705C2: first-member command through resolved producer.
void AIGroup::rva00370554(Object *arg1,CommandSourceType source)
{
 if(m_memberList.empty()) return;
 Object *target=arg1;
 Object *original=target;
 Object *obj=m_memberList.front();
 if(obj && original) {
  if(obj->rva002931F5(false)) obj=obj->rva002931F5(false);
  if(original->rva002931F5(false)) target=original->rva002931F5(false);
  AIUpdateInterface *ai=obj->m_ai;
  if(ai) ai->m_commands.rva0036EC1D(target,source);
 }
}

