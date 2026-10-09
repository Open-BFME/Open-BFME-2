// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DTreeBuffer method at retail 0x000ECDF5 (309 bytes, ret 0xC, called from
// addTree 0x000ECF79): finds or adds the tree type for a template's tree
// draw module data and returns its index, or -2; a template without that
// module reports it and fails. Donor: Open-BFME-1 W3DTreeBufferRva00736940.cpp
// (BFME1 0x00736940). BFME2 deltas read from retail: the template is looked up
// through the rowed 0x002D06CA on the 0x00DFF000 registry, the draw module
// list is the ModuleInfo at template+0x2F0 (rowed getNthData 0x0033ACE8), the
// tree draw module data accessor is module vtable slot 16 (+0x40), the debug
// report goes through theDebug +0x60 / +0x6C(0,0,0) / +0x38 / +0x4C(2), tree
// types are 0x5C bytes at +0x44558 (count +0x45C58), and the type-added flag
// is +0x44556.
#include "ascii_string.h"

typedef int Int;

struct Rva000ECDF5TreeDrawData
{
	unsigned char moduleDataBase[8];
	AsciiString m_modelName;
	AsciiString m_nameC;
};

class ModuleData
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual const Rva000ECDF5TreeDrawData *getAsW3DTreeDrawModuleData() const;
};

class ModuleInfo
{
public:
	const ModuleData *getNthData(Int i) const;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x64];
	AsciiString m_name;
	unsigned char m_pad68[0x2F0 - 0x68];
	ModuleInfo m_drawModuleInfo;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second, int third);
};

class Debug;
extern Debug *theDebug;
#define TheBfmeAwakenDebug (*(BfmeAwakenDebug **)&theDebug)
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

struct Rva000ECDF5TreeType
{
	unsigned char prefix[0x4c];
	AsciiString m_modelName;
	AsciiString m_nameC;
	unsigned char suffix[0x5c - 0x54];
};

class W3DTreeBuffer
{
public:
	Int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, Int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	Int rva000ECDF5(const AsciiString &templateName, Int shadowKind, const AsciiString &textureName);

private:
	unsigned char prefix[0x44556];
	bool m_needUpdate;
	unsigned char alignment[1];
	Rva000ECDF5TreeType m_treeTypes[64];
	Int m_numTreeTypes;
};

Int W3DTreeBuffer::rva000ECDF5(const AsciiString &templateName, Int shadowKind, const AsciiString &textureName)
{
	if (((const StringBase<char> *)&templateName)->isEmpty())
		return -2;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(templateName);
	if (tmpl == 0)
		return -2;
	const ModuleData *module = tmpl->m_drawModuleInfo.getNthData(0);
	if (module == 0)
		return -2;
	const Rva000ECDF5TreeDrawData *data = module->getAsW3DTreeDrawModuleData();
	if (data == 0) {
		if (bfmeRva000387C0()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0, 0)->v38("Tree ")->v38(tmpl->m_name.str())
				->v38(" requires a W3DTreeDrawModule.\n")->v4c(2);
		}
		return -2;
	}

	Int index = -2;
	for (Int i = 0; i < m_numTreeTypes; ++i) {
		if (m_treeTypes[i].m_modelName.compareNoCase(data->m_modelName) == 0 &&
			m_treeTypes[i].m_nameC.compareNoCase(data->m_nameC) == 0) {
			index = i;
			break;
		}
	}
	if (index < 0) {
		index = addTreeType(data->m_modelName, data->m_nameC, data, shadowKind, textureName, templateName);
		if (index >= 0)
			m_needUpdate = true;
	}
	return index;
}
