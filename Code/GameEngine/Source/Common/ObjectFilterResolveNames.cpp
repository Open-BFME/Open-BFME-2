// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003611EFResolveNames@ObjectFilter@@SAXPAV1@@Z retail 0x003611EF 585 bytes.
// ObjectFilter name resolution: every inclusion name (+0x00) starting with S:
// with length >= 3 (rest names a template kept in its own list at +0x18) or
// naming a template (+0x30) must resolve through TheThingFactory rva002D06CA else
// INIException ObjectFilter resolveNames specified. Name list cleared after.
// Same pass over exclusion names (+0x0C) into +0x24 and +0x3C. Evidence: four
// message literals name it. BFME1 donor ObjectFilterResolveNames.cpp retail
// 0x0039E2B0 has same six vectors at same offsets. Callers at 0x0036145E and
// 0x0036235C push one filter pointer cdecl. All callees rowed or pinned.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>


template <typename T>
struct StringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class ModuleData
{
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;
// TheThingFactory (0x009FF000) is ThingFactory.cpp's global; this unit reads it through its own view.



class ObjectFilter
{
public:
	static void rva003611EFResolveNames(ObjectFilter *filter);

	_STL::vector<AsciiString> m_inclusionNames;
	_STL::vector<AsciiString> m_exclusionNames;
	_STL::vector<const ModuleData *> m_inclusionSTemplates;
	_STL::vector<const ModuleData *> m_exclusionSTemplates;
	_STL::vector<const ModuleData *> m_inclusionTemplates;
	_STL::vector<const ModuleData *> m_exclusionTemplates;
	char m_tail[0x94 - 0x48];
};

void ObjectFilter::rva003611EFResolveNames(ObjectFilter *filter)
{
	int i;
	int count = filter->m_inclusionNames.size();
	for (i = 0; i < count; ++i)
	{
		AsciiString &name = filter->m_inclusionNames[i];
		if (name.startsWith("S:") && (unsigned)name.getLength() >= 3)
		{
			const char *templateName = name.str();
			templateName += 2;
			const ModuleData *tmpl;
			{
				AsciiString tmp(templateName);
				tmpl = (const ModuleData *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp);
			}
			if (!tmpl)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified +S:%s but template %s doesn't exist! Typo?", templateName, templateName);
			}
			filter->m_inclusionSTemplates.push_back(tmpl);
		}
		else
		{
			const ModuleData *tmpl = (const ModuleData *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name);
			if (!tmpl)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified +%s but this template doesn't exist! Typo?", name.str());
			}
			filter->m_inclusionTemplates.push_back(tmpl);
		}
	}
	filter->m_inclusionNames.clear();

	count = filter->m_exclusionNames.size();
	for (i = 0; i < count; ++i)
	{
		AsciiString &name = filter->m_exclusionNames[i];
		if (name.startsWith("S:") && (unsigned)name.getLength() >= 3)
		{
			const char *templateName = name.str();
			templateName += 2;
			const ModuleData *tmpl;
			{
				AsciiString tmp(templateName);
				tmpl = (const ModuleData *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp);
			}
			if (!tmpl)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified -S:%s but template %s doesn't exist! Typo?", templateName, templateName);
			}
			filter->m_exclusionSTemplates.push_back(tmpl);
		}
		else
		{
			const ModuleData *tmpl = (const ModuleData *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name);
			if (!tmpl)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified -%s but this template doesn't exist! Typo?", name.str());
			}
			filter->m_exclusionTemplates.push_back(tmpl);
		}
	}
	filter->m_exclusionNames.clear();
}
