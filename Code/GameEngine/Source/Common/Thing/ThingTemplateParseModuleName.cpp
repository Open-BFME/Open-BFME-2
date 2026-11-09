// ?parseModuleName@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// cl: /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// ZH semantic donor via BFME1 6583b3c1. Target33D865..33DB25, 704B.
// Target field table DBF068/DBF078 labels Behavior/Body and this callback.
// Measured target mode+5F8, name+64, replacements+94/+98 and four ModuleInfo
// members+2E4/+2F0/+2FC/+308; target masks/body32 and load types2/4.
// Additional slot7 clear is target-only; original slot7 identity is unknown.
#include "ascii_string.h"
#include "Common/INIException.h"
enum ModuleType { MODULETYPE_BEHAVIOR=0 };
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/ModuleData.h"
class ThingTemplate;
#include "../../../Include/Common/ModuleFactoryClass.h"
extern ModuleFactory *TheModuleFactory;
#include "../../../Include/Common/ModuleInfoClass.h"
#include "../../../Include/Common/ThingTemplate.h"
void ThingTemplate::parseModuleName(INI *ini,void *instance,void *store,const void *userData)
{
 ThingTemplate *self=(ThingTemplate *)instance;
 ModuleInfo *mi=(ModuleInfo *)store;
 ModuleType type=(ModuleType)(unsigned int)userData;
 const char *token=ini->getNextToken();
 AsciiString tokenStr=token;
 AsciiString moduleTagStr;
 try {moduleTagStr=ini->getNextToken();} catch(...) {throw;}
 int mask;
 if ((int)type==999) {
   type=MODULETYPE_BEHAVIOR;
   mask=TheModuleFactory->findModuleInterfaceMask(tokenStr,type);
   if ((mask&32)==0) throw INIException(3,"Only Body allowed here");
 } else {
   mask=TheModuleFactory->findModuleInterfaceMask(tokenStr,type);
   if ((mask&32)!=0) throw INIException(3,"No Body allowed here");
 }
 if (ini->getLoadType()==2) {
   if (self->m5F8!=1) throw INIException(3,"You must use AddModule to add modules in override INI files.");
 } else {
   if (ini->getLoadType()!=4) {
     reinterpret_cast<ModuleInfo *>(self->m_behaviorModuleInfo)->rva0033C84A(mask);
     reinterpret_cast<ModuleInfo *>(self->m_drawModuleInfo)->rva0033C84A(mask);
     reinterpret_cast<ModuleInfo *>(self->m_clientUpdateModuleInfo)->rva0033C84A(mask);
     reinterpret_cast<ModuleInfo *>(self->m_clientBehaviorModuleInfo)->rva0033C84A(mask);
   }
 }
 if (self->m5F8==1 && !((const StringBase<char> *)&self->m094)->isEmpty() && self->m094!=tokenStr)
   throw INIException(3,"ReplaceModule must replace modules with another module of the same type, but you are attempting to replace a %s with a %s for object %s.",self->m094.str(),tokenStr.str(),self->m_nameString.str());
 if (self->m5F8==1 && !((const StringBase<char> *)&self->m098)->isEmpty() && self->m098==moduleTagStr)
   throw INIException(3,"ReplaceModule must specify a new unique tag for the replaced module, but you are not doing so for %s (%s) for object %s.",moduleTagStr.str(),self->m094.str(),self->m_nameString.str());
 ModuleData *data=TheModuleFactory->newModuleDataFromINI(ini,tokenStr,type,moduleTagStr);
 bool overrideFile=ini->getLoadType()==4;
 if (data->isAiModuleData()) mi->clearAiModuleInfo();
 if (data->slot07() && overrideFile) mi->rva0033C8B5();
 bool inheritable=self->m5F8==2;
 mi->addModuleInfo(self,tokenStr,moduleTagStr,data,mask,inheritable,overrideFile);
}
