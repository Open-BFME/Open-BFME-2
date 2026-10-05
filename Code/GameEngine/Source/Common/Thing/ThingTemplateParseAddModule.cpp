// cl: /O1 /GX /DNDEBUG /MD /Ireference/shims/iniexception
// Semantic donor: ZH ThingTemplate.cpp through BFME1
// 6583b3c1ff21db4a561285717028fdafc780b7db. Native33A50D..33A561 84B.
// Native field table DBF4D8 labels this handler AddModule. Mode byte
// +5F8, constant1, validation message and tableDBECD8 are target facts.
// The donor mode enum independently calls value1 ADD_REMOVE_REPLACE. The existing
// home unit supplies s_objectFieldParseTable; rowed INIException ctor and
// INI::initFromINI preserve the target parser and exception ABI.
#include "Common/INIException.h"
struct FieldParse { unsigned int words[4]; };
class INI { public: void initFromINI(void *,const FieldParse *); };
class ThingTemplate {
protected:
 static void parseAddModule(INI *,void *,void *,const void *);
private:
 char prefix[0x5F8]; signed char m_moduleParsingMode;
 static const FieldParse s_objectFieldParseTable[];
};
void ThingTemplate::parseAddModule(INI *ini,void *instance,void *,const void *)
{
 ThingTemplate *self=(ThingTemplate *)instance;
 int oldMode=self->m_moduleParsingMode;
 if (oldMode!=0) throw INIException(3,"Expected oldMode to be MODULEPARSE_NORMAL");
 self->m_moduleParsingMode=1;
 ini->initFromINI(self,s_objectFieldParseTable);
 self->m_moduleParsingMode=(signed char)oldMode;
}
