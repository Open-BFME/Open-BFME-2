// ?addModuleInfo@ModuleInfo@@QAEXPAVThingTemplate@@ABVAsciiString@@1PBVModuleData@@H_N3@Z
// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// Semantic donor BFME1 6583b3c1ff21db4a561285717028fdafc780b7db
// game/GameEngine/Source/Common/Thing/ThingTemplate.cpp addModuleInfo.
// Target diagnostics spell addModuleInfo; parser33D865 passes this7-arg ABI.
// Native temporary teardown is the two-string destructor at 0x002CF51B;
// its opaque BfmeStringRecord spelling now links to the verified Nugget dtor.
// Native33D553..33D864 785B; four ModuleInfo offsets2E4..308, name64.
#include "ascii_string.h"
#include "Common/INIException.h"
typedef unsigned char UnsignedByte;
typedef int Int;
typedef bool Bool;
class ThingTemplate; class ModuleData;
class Rva0033C8E8 {public: bool rva0033C8E8(const AsciiString &,AsciiString &);};
struct BfmeStringRecord002CF4C6 {
 AsciiString text0,text1; unsigned int word0,word1; unsigned char flag0,flag1;
 BfmeStringRecord002CF4C6(const AsciiString &,const AsciiString &,unsigned int,unsigned int,unsigned char);
 ~BfmeStringRecord002CF4C6();
};
namespace _STL {
 template<class T> class allocator {};
 template<class T,class Alloc> class vector {public: void push_back(const T &); private: void *first,*last,*end;};
}
struct BfmeModuleInfoLayout {
 _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> > m_info;
};
class ModuleInfo {public:
 struct Nugget {AsciiString first,tag; const ModuleData *data; int mask; unsigned char flags[2];};
 const Nugget *getNuggetWithTag(const AsciiString &) const;
 void addModuleInfo(ThingTemplate *,const AsciiString &,const AsciiString &,const ModuleData *,int,bool,bool);
};
void ModuleInfo::addModuleInfo(ThingTemplate *thingTemplate, 
																	 const AsciiString& name,
															 const AsciiString& moduleTag, 
															 const ModuleData* data, 
															 Int interfaceMask, 
															 Bool inheritable,
                               Bool overrideableByLikeKind)
{
	const UnsignedByte overrideable = reinterpret_cast<const UnsignedByte &>(overrideableByLikeKind);
	const Nugget *nugget = reinterpret_cast<ModuleInfo *>((char *)thingTemplate + 0x2E4)->getNuggetWithTag(moduleTag);
	if (nugget != NULL)
	{
		if (overrideable)
		{
			{
				AsciiString clearedModuleName;
            reinterpret_cast<Rva0033C8E8 *>(thingTemplate)->rva0033C8E8(moduleTag, clearedModuleName);
			}
		}
		else
		{
			throw INIException(3,
				"addModuleInfo - ERROR defining module '%s' on thing template '%s'. The module '%s' has the tag '%s' which must be unique among all modules for this object, but the tag '%s' is also already on behavior module '%s' within this object.\n\nPlease make unique tag names within an object definition.",
				name.str(), reinterpret_cast<const AsciiString *>((const char *)thingTemplate + 0x64)->str(), name.str(),
				moduleTag.str(), moduleTag.str(), nugget->first.str());
		}
	}

	nugget = reinterpret_cast<ModuleInfo *>((char *)thingTemplate + 0x2F0)->getNuggetWithTag(moduleTag);
	if (nugget != NULL)
	{
		if (!overrideable || nugget->first.compare(name) != 0)
		{
			throw INIException(3,
				"addModuleInfo - ERROR defining module '%s' on thing template '%s'. The module '%s' has the tag '%s' which must be unique among all modules for this object, but the tag '%s' is also already on draw module '%s' within this object.\n\nPlease make unique tag names within an object definition.",
				name.str(), reinterpret_cast<const AsciiString *>((const char *)thingTemplate + 0x64)->str(), name.str(),
				moduleTag.str(), moduleTag.str(), nugget->first.str());
		}
		{
			AsciiString clearedModuleName;
        reinterpret_cast<Rva0033C8E8 *>(thingTemplate)->rva0033C8E8(moduleTag, clearedModuleName);
		}
	}

	nugget = reinterpret_cast<ModuleInfo *>((char *)thingTemplate + 0x2FC)->getNuggetWithTag(moduleTag);
	if (nugget != NULL)
	{
		if (overrideable)
		{
			{
				AsciiString clearedModuleName;
            reinterpret_cast<Rva0033C8E8 *>(thingTemplate)->rva0033C8E8(moduleTag, clearedModuleName);
			}
		}
		else
		{
			throw INIException(3,
				"addModuleInfo - ERROR defining module '%s' on thing template '%s'. The module '%s' has the tag '%s' which must be unique among all modules for this object, but the tag '%s' is also already on update module '%s' within this object.\n\nPlease make unique tag names within an object definition.",
				name.str(), reinterpret_cast<const AsciiString *>((const char *)thingTemplate + 0x64)->str(), name.str(),
				moduleTag.str(), moduleTag.str(), nugget->first.str());
		}
	}

	nugget = reinterpret_cast<ModuleInfo *>((char *)thingTemplate + 0x308)->getNuggetWithTag(moduleTag);
	if (nugget != NULL)
	{
		if (overrideable)
		{
			{
				AsciiString clearedModuleName;
            reinterpret_cast<Rva0033C8E8 *>(thingTemplate)->rva0033C8E8(moduleTag, clearedModuleName);
			}
		}
		else
		{
			throw INIException(3,
				"addModuleInfo - ERROR defining module '%s' on thing template '%s'. The module '%s' has the tag '%s' which must be unique among all modules for this object, but the tag '%s' is also already on client behavior module '%s' within this object.\n\nPlease make unique tag names within an object definition.",
				name.str(), reinterpret_cast<const AsciiString *>((const char *)thingTemplate + 0x64)->str(), name.str(),
				moduleTag.str(), moduleTag.str(), nugget->first.str());
		}
	}

	reinterpret_cast<BfmeModuleInfoLayout *>(this)->m_info.push_back(
		BfmeStringRecord002CF4C6(name, moduleTag, (unsigned int)data, (unsigned int)interfaceMask, (unsigned char)inheritable));

}
