// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// Size-optimised (/O1) emission of DetailedArchivedDirectoryInfo teardown and its map base.
//
#include "PreRTS.h"
// LINK-COMDAT: block ZH ArchiveFileSystem.h so this TU's ArchivedFileInfo
// emits the kept (/O2 frameless) copy via pragma ty, while Detailed stays
// /O1 for its rows. Layout mirrors the ZH header verbatim.
#define __ARCHIVEFILESYSTEM_H_
#include <map>
#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"
class ArchivedDirectoryInfo;
class DetailedArchivedDirectoryInfo;
class ArchivedFileInfo;
class ArchiveFile;
typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedDirectoryInfo> ArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;
typedef std::map<AsciiString, ArchiveFile *> ArchiveFileMap;
typedef std::map<AsciiString, AsciiString> ArchivedFileLocationMap;
class ArchivedDirectoryInfo
{
public:
	AsciiString m_directoryName;
	ArchivedDirectoryInfoMap m_directories;
	ArchivedFileLocationMap m_files;
	void clear();
};
class DetailedArchivedDirectoryInfo
{
public:
	AsciiString m_directoryName;
	DetailedArchivedDirectoryInfoMap m_directories;
	ArchivedFileInfoMap m_files;
	void clear();
};
#pragma optimize("ty", on)
class ArchivedFileInfo
{
public:
	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;
	ArchivedFileInfo();
	~ArchivedFileInfo();
	void clear();
};
#pragma optimize("", on)
#include "Common/ArchiveFile.h"
#include "Common/File.h"
#include "Common/PerfTimer.h"

#pragma inline_depth(0)
// ?_bfmeDetailedDirMapAnchor@@YAXPAV?$map@VAsciiString@@VDetailedArchivedDirectoryInfo@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VDetailedArchivedDirectoryInfo@@@_STL@@@3@@_STL@@@Z absent-from-retail
void _bfmeDetailedDirMapAnchor(DetailedArchivedDirectoryInfoMap *m)
{
	m->DetailedArchivedDirectoryInfoMap::map();
}
#pragma inline_depth()
// ?_bfmeDetailedDirInfoAnchor@@YAXPAVDetailedArchivedDirectoryInfo@@@Z absent-from-retail
void _bfmeDetailedDirInfoAnchor(DetailedArchivedDirectoryInfo *d)
{
	d->~DetailedArchivedDirectoryInfo();
}

typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, ArchivedFileInfo>, _STL::_Select1st<_STL::pair<const AsciiString, ArchivedFileInfo> >, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, ArchivedFileInfo> > > ArchivedFileTree;

class Rva002241D1
{
public:
	void rva002241D1();
};

void Rva002241D1::rva002241D1()
{
	((ArchivedFileTree *)this)->ArchivedFileTree::~_Rb_tree();
}

class Rva00224243
{
public:
	void rva00224243();
};

void Rva00224243::rva00224243()
{
	((ArchivedFileTree *)this)->ArchivedFileTree::~_Rb_tree();
}

class Rva00224248
{
public:
	void rva00224248();
};

void Rva00224248::rva00224248()
{
	((ArchivedFileTree *)this)->ArchivedFileTree::~_Rb_tree();
}

class Rva0022424D
{
public:
	void rva0022424D();
};

void Rva0022424D::rva0022424D()
{
	((ArchivedFileTree *)this)->ArchivedFileTree::~_Rb_tree();
}

// ?rva002241D6@Rva002241D6@@QAEXPAVINI@@@Z, retail 0x002241D6, 109B: INI key/value
// pair inserted into the +0xC location map via its operator[] (rowed 0x002240CB)
// then set from the second token. Evidence: gap between 0x002241D1 and
// 0x00224243 in this TU, callers 0x00224A39, flags /O1 /arch:SSE /G7,
// callees INI::getNextAsciiString StringBase::set releaseBuffer all rowed.
class Rva002240CB
{
public:
	AsciiString &rva002240CB(const AsciiString &key);
};

class Rva002241D6
{
public:
	void rva002241D6(INI *ini);
private:
	unsigned char m_pad0[0xC];
	Rva002240CB m_map;
};

void Rva002241D6::rva002241D6(INI *ini)
{
	AsciiString key = ini->getNextAsciiString();
	AsciiString value = ini->getNextAsciiString();
	AsciiString &slot = m_map.rva002240CB(key);
	slot.setCopyInline(value);
}



