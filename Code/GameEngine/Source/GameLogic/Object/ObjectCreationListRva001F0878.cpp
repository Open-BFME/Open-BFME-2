// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/ocls /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// ?create@ObjectCreationList@@QAEXPAX00H@Z @ 0x001F0878 (91B).
// Honest address-named method of ObjectCreationList resolving the BFME2
// reference chain (flag at +0x0C, AsciiString name at +0x10) via
// TheObjectCreationListStore->findObjectCreationList then invoking nugget
// vtable slot 0x0C with the 4 forwarded args. Proven by callers 0x00456520
// (null-checked static wrapper forwarding 4 args) and 0x00487480 (BoneFX
// path pushing esi/&local/0/0); callees all rowed (find at 0x001F07B8).
// AsciiString::str() inlines m_data ? m_data+8 : "" (empty at 0x00BBAC1C).
#include <vector>

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"

class ObjectCreationNugget
{
public:
	virtual void v0() = 0;
	virtual void v1(void *a1, void *a2, void *a3, void *a4, int a5) = 0;
	virtual void v2(void *a1, void *a2, void *a3) = 0;
	virtual void v3(void *a1, void *a2, void *a3, int a4) = 0;
	virtual void v4(void *a1, void *a2) = 0;
};

class ObjectCreationList;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};

extern ObjectCreationListStore *TheObjectCreationListStore;

extern "C" void __cdecl free(void *p);

struct Rva001F0468Node
{
	char m_pad00[8];
	Rva001F0468Node *m_next08;
	Rva001F0468Node *m_child0c;
};

class ObjectCreationList
{
public:
	void create(void *a1, void *a2, void *a3, int a4);
	void create(void *a1, void *a2, void *a3);
	void create(void *a1, void *a2, void *a3, void *a4, int a5);
	void rva001F0410(void *a1, void *a2);
	void rva001F0468(Rva001F0468Node *head);

private:
	_STL::vector<ObjectCreationNugget *> m_nuggets;
	unsigned char m_flag0c;
	char m_pad0d[3];
	AsciiString m_name10;
};

void ObjectCreationList::create(void *a1, void *a2, void *a3, int a4)
{
	ObjectCreationList *cur = this;
	while (cur->m_flag0c != 0)
	{
		const char *name = cur->m_name10.str();
		const ObjectCreationList *found = TheObjectCreationListStore->findObjectCreationList(name);
		if (found == 0)
			break;
		if (found->m_flag0c != 0)
		{
			cur = (ObjectCreationList *)found;
			continue;
		}
		cur = (ObjectCreationList *)found;
		break;
	}
	for (ObjectCreationNugget **i = cur->m_nuggets.begin(); i != cur->m_nuggets.end(); ++i)
		(*i)->v3(a1, a2, a3, a4);
}

void ObjectCreationList::rva001F0410(void *a1, void *a2)
{
	for (ObjectCreationNugget **i = m_nuggets.begin(); i != m_nuggets.end(); ++i)
		(*i)->v4(a1, a2);
}

void __cdecl Rva004C309CForward(void *ocl, void *a1, void *a2, void *a3, void *a4, int a5)
{
	if (ocl == 0)
		return;
	((ObjectCreationList *)ocl)->create(a1, a2, a3, a4, a5);
}

void ObjectCreationList::create(void *a1, void *a2, void *a3, void *a4, int a5)
{
	ObjectCreationList *cur = this;
	while (cur->m_flag0c != 0)
	{
		const char *name = cur->m_name10.str();
		const ObjectCreationList *found = TheObjectCreationListStore->findObjectCreationList(name);
		if (found == 0)
			break;
		if (found->m_flag0c != 0)
		{
			cur = (ObjectCreationList *)found;
			continue;
		}
		cur = (ObjectCreationList *)found;
		break;
	}
	for (ObjectCreationNugget **i = cur->m_nuggets.begin(); i != cur->m_nuggets.end(); ++i)
		(*i)->v1(a1, a2, a3, a4, a5);
}

void ObjectCreationList::create(void *a1, void *a2, void *a3)
{
	ObjectCreationList *cur = this;
	while (cur->m_flag0c != 0)
	{
		const char *name = cur->m_name10.str();
		const ObjectCreationList *found = TheObjectCreationListStore->findObjectCreationList(name);
		if (found == 0)
			break;
		if (found->m_flag0c != 0)
		{
			cur = (ObjectCreationList *)found;
			continue;
		}
		cur = (ObjectCreationList *)found;
		break;
	}
	for (ObjectCreationNugget **i = cur->m_nuggets.begin(); i != cur->m_nuggets.end(); ++i)
		(*i)->v2(a1, a2, a3);
}

void ObjectCreationList::rva001F0468(Rva001F0468Node *head)
{
	Rva001F0468Node *cur = head;
	if (cur == 0)
		return;
	while (cur != 0)
	{
		rva001F0468(cur->m_child0c);
		Rva001F0468Node *next = cur->m_next08;
		free(cur);
		cur = next;
	}
}

struct Rva001F050BMid
{
	char m_pad00[4];
	Rva001F0468Node *m_head04;
	Rva001F050BMid *m_next08;
	Rva001F050BMid *m_prev0c;
};

class Rva001F050B
{
public:
	void rva001F050B();

private:
	Rva001F050BMid *m_ptr00;
	int m_count04;
};

void Rva001F050B::rva001F050B()
{
	if (m_count04 == 0)
		return;
	((ObjectCreationList *)this)->rva001F0468(m_ptr00->m_head04);
	m_ptr00->m_next08 = m_ptr00;
	m_ptr00->m_head04 = 0;
	m_ptr00->m_prev0c = m_ptr00;
	m_count04 = 0;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?bfmeDoBPB@BfmeSubBPB@@QAEXPAX00@Z=?create@ObjectCreationList@@QAEXPAX00@Z")
#pragma comment(linker, "/alternatename:?bfmeDoBUC@BfmeSubBUC@@QAEXPAX000@Z=?create@ObjectCreationList@@QAEXPAX00H@Z")
