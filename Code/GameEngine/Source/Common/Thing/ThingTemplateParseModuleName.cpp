// ?parseModuleName@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// ZH semantic donor via BFME1 6583b3c1. Target33D865..33DB25, 704B.
// Target field table DBF068/DBF078 labels Behavior/Body and this callback.
// Measured target mode+5F8, name+64, replacements+94/+98 and four ModuleInfo
// members+2E4/+2F0/+2FC/+308; target masks/body32 and load types2/4.
// Additional slot7 clear is target-only; original slot7 identity is unknown.
#include "ascii_string.h"
#include "Common/INIException.h"
enum ModuleType { MODULETYPE_BEHAVIOR=0 };
class INI { public:
 const char *getNextToken(const char *sep=0);
 int getLoadType() const {return loadType;}
private: char prefix[8]; int loadType;
};
class ModuleData { public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual bool isAiModuleData(); virtual void s5(); virtual void s6();
 virtual bool rvaSlot7();
};
class ThingTemplate;
class ModuleFactory { public:
 int rva00256F39(const AsciiString &,ModuleType);
 ModuleData *newModuleDataFromINI(INI *,const AsciiString &,ModuleType,const AsciiString &);
};
extern ModuleFactory *TheModuleFactory;
class ModuleInfo { public:
 bool rva0033C84A(int);
 bool clearAiModuleInfo();
 bool rva0033C8B5();
 void addModuleInfo(ThingTemplate *,const AsciiString &,const AsciiString &,const ModuleData *,int,bool,bool);
private: char bytes[12];
};
class ThingTemplate { protected:
 static void parseModuleName(INI *,void *,void *,const void *);
private:
 char prefix[0x64]; AsciiString name;
 char pad68[0x94-0x68]; AsciiString replacedName,replacedTag;
 char pad9C[0x2E4-0x9C]; ModuleInfo infos[4];
 char pad314[0x5F8-0x314]; signed char mode;
};
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
   mask=TheModuleFactory->rva00256F39(tokenStr,type);
   if ((mask&32)==0) throw INIException(3,"Only Body allowed here");
 } else {
   mask=TheModuleFactory->rva00256F39(tokenStr,type);
   if ((mask&32)!=0) throw INIException(3,"No Body allowed here");
 }
 if (ini->getLoadType()==2) {
   if (self->mode!=1) throw INIException(3,"You must use AddModule to add modules in override INI files.");
 } else {
   if (ini->getLoadType()!=4) {
     self->infos[0].rva0033C84A(mask);
     self->infos[1].rva0033C84A(mask);
     self->infos[2].rva0033C84A(mask);
     self->infos[3].rva0033C84A(mask);
   }
 }
 if (self->mode==1 && !((const StringBase<char> *)&self->replacedName)->isEmpty() && self->replacedName!=tokenStr)
   throw INIException(3,"ReplaceModule must replace modules with another module of the same type, but you are attempting to replace a %s with a %s for object %s.",self->replacedName.str(),tokenStr.str(),self->name.str());
 if (self->mode==1 && !((const StringBase<char> *)&self->replacedTag)->isEmpty() && self->replacedTag==moduleTagStr)
   throw INIException(3,"ReplaceModule must specify a new unique tag for the replaced module, but you are not doing so for %s (%s) for object %s.",moduleTagStr.str(),self->replacedName.str(),self->name.str());
 ModuleData *data=TheModuleFactory->newModuleDataFromINI(ini,tokenStr,type,moduleTagStr);
 bool overrideFile=ini->getLoadType()==4;
 if (data->isAiModuleData()) mi->clearAiModuleInfo();
 if (data->rvaSlot7() && overrideFile) mi->rva0033C8B5();
 bool inheritable=self->mode==2;
 mi->addModuleInfo(self,tokenStr,moduleTagStr,data,mask,inheritable,overrideFile);
}
