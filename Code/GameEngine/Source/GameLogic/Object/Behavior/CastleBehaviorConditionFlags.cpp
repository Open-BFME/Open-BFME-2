// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native 3979FB..397B03 (264B), WB EC0B70 independently confirms all
// seven callees, parent ObjectID38 and child ObjectID vector5C.
// Both paths change object flags, refresh the drawable, then notify the
// CastleMemberBehavior module through recovered audio-flags helper395BCB.
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;
class Drawable {public:void rva00274176(bool);};
class Thing {public:Drawable *getDrawable() const;};
class Module;
class Object:public Thing {friend class Rva003979FB;protected:Module *findModule(NameKeyType)const;public:void rva0028CFB2(const int*,const int*);};
class Rva00395BCB {public:void rva00395BCB(const void*,const void*);};
class Rva003979FB {
public:
 void rva003979FB(const int *oldFlags,const int *newFlags);
 char unknown00[0x38];
 ObjectID parentID;
 char unknown3C[0x5C-0x3C];
 _STL::vector<ObjectID> children;
};
void Rva003979FB::rva003979FB(const int *oldFlags,const int *newFlags)
{
 static const NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 Object *parent=TheGameLogic->findObjectByID(parentID);
 if(parent) {
  parent->rva0028CFB2(oldFlags,newFlags);
  parent->getDrawable()->rva00274176(false);
  Module *module=parent->findModule(key);
  if(module)((Rva00395BCB *)module)->rva00395BCB(oldFlags,newFlags);
 }
 for(unsigned int i=0;i<children.size();++i) {
  Object *child=TheGameLogic->findObjectByID(children[i]);
  if(child) {
   child->rva0028CFB2(oldFlags,newFlags);
   child->getDrawable()->rva00274176(false);
   Module *module=child->findModule(key);
   if(module)((Rva00395BCB *)module)->rva00395BCB(oldFlags,newFlags);
  }
 }
}
