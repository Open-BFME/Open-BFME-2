// cl: /Ireference/shims/archivefile_directory_dtor /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/System/ArchiveFile.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

/////////ArchiveFile.cpp ///////////////////////
// Bryan Cleveland, August 2002
////////////////////////////////////////////////

#include "PreRTS.h"
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

// Same archive views as ArchiveDirInfoO1.cpp (ZH ArchiveFileSystem.h layout).
// Declare the directory teardown so this TU binds to the rowed /O1 body
// instead of emitting its competing implicit destructor.
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
	void clear()
	{
		m_directoryName.clear();
		m_directories.clear();
		m_files.clear();
	}
};
class DetailedArchivedDirectoryInfo
{
public:
	~DetailedArchivedDirectoryInfo(); // rowed /O1 teardown at 0x00224252
	AsciiString m_directoryName;
	DetailedArchivedDirectoryInfoMap m_directories;
	ArchivedFileInfoMap m_files;
	void clear()
	{
		m_directoryName.clear();
		m_directories.clear();
		m_files.clear();
	}
};
class ArchivedFileInfo
{
public:
	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;
	ArchivedFileInfo() { clear(); }
	void clear()
	{
		m_filename.clear();
		m_archiveFilename.clear();
		m_offset = 0;
		m_size = 0;
	}
};
#include "Common/ArchiveFile.h"
#include "Common/ArchiveFileSystem.h"
#include "Common/File.h"
#include "Common/PerfTimer.h"
namespace _STL { template <> void _Construct<AsciiString, AsciiString>(AsciiString *, AsciiString const &); }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, DetailedArchivedDirectoryInfo>, _Select1st<pair<AsciiString const, DetailedArchivedDirectoryInfo> >, less<AsciiString>, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > >::_Rb_tree(less<AsciiString> const &, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > const &); }
namespace _STL { template <> _Rb_tree_base<pair<AsciiString const, DetailedArchivedDirectoryInfo>, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > >::_Rb_tree_base(allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > const &); }
namespace _STL { template <> map<AsciiString, DetailedArchivedDirectoryInfo, less<AsciiString>, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > >::map(); }
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, ArchivedFileInfo>, _Select1st<pair<AsciiString const, ArchivedFileInfo> >, less<AsciiString>, allocator<pair<AsciiString const, ArchivedFileInfo> > >::~_Rb_tree(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@VAsciiString@@@_STL@@@_STL@@QBEPAU?$_Rb_tree_node@V:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Rb_tree_node<AsciiString> * allocator<_Rb_tree_node<AsciiString> >::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ??R?$less@VAsciiString@@@_STL@@QBE_NABVAsciiString@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> bool less<AsciiString>::operator()(AsciiString const &,AsciiString const &) const; }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, DetailedArchivedDirectoryInfo>, _Select1st<pair<AsciiString const, DetailedArchivedDirectoryInfo> >, less<AsciiString>, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > >::~_Rb_tree(); }
namespace _STL { template <> pair<AsciiString const, DetailedArchivedDirectoryInfo>::~pair(); }
namespace _STL { template <> void _Rb_tree<AsciiString, pair<AsciiString const, DetailedArchivedDirectoryInfo>, _Select1st<pair<AsciiString const, DetailedArchivedDirectoryInfo> >, less<AsciiString>, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > >::_M_erase(_Rb_tree_node<pair<AsciiString const, DetailedArchivedDirectoryInfo> > *); }
namespace _STL { template <> void _Rb_tree<AsciiString, pair<AsciiString const, DetailedArchivedDirectoryInfo>, _Select1st<pair<AsciiString const, DetailedArchivedDirectoryInfo> >, less<AsciiString>, allocator<pair<AsciiString const, DetailedArchivedDirectoryInfo> > >::clear(); }
// bfme link decl-only end


// checks to see if str matches searchString.  Search string is done in the
// using * and ? as wildcards. * is used to denote any number of characters,
// and ? is used to denote a single wildcard character.
static Bool SearchStringMatches(AsciiString str, AsciiString searchString) 
{
	if (str.getLength() == 0) {
		if (searchString.getLength() == 0) {
			return TRUE;
		}
		return FALSE;
	}
	if (searchString.getLength() == 0) {
		return FALSE;
	}

	const char *c1 = str.str();
	const char *c2 = searchString.str();

	while ((*c1 == *c2) || (*c2 == '?') || (*c2 == '*')) {
		if ((*c1 == *c2) || (*c2 == '?')) {
			++c1;
			++c2;
		} else if (*c2 == '*') {
			++c2;
			if (*c2 == 0) {
				return TRUE;
			}
			while (*c1 != 0) {
				if (SearchStringMatches(AsciiString(c1), AsciiString(c2))) {
					return TRUE;
				}
				++c1;
			}
		}
		if (*c1 == 0) {
			if (*c2 == 0) {
				return TRUE;
			}
			return FALSE;
		}
		if (*c2 == 0) {
			return FALSE;
		}
	}
	return FALSE;
}

// ?ArchiveFile::~ArchiveFile present-unmatched
ArchiveFile::~ArchiveFile() 
{
	if (m_file != NULL) {
		m_file->close();
		m_file = NULL;
	}
}

// ?ArchiveFile::ArchiveFile present-unmatched
ArchiveFile::ArchiveFile() 
{
	m_rootDirectory.clear();
}

// ?ArchiveFile::addFile present-unmatched
void ArchiveFile::addFile(const AsciiString& path, const ArchivedFileInfo *fileInfo) 
{
	AsciiString temp;
	temp = path;
	((StringBase<char> *)&temp)->toLower();
	AsciiString token;
	AsciiString debugpath;

	DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	temp.nextToken(&token, "\\/");

	while (token.getLength() > 0) {
		DetailedArchivedDirectoryInfoMap::iterator it = dirInfo->m_directories.find(token);
		if (it == dirInfo->m_directories.end())
		{
			// Insert the missing directory without instantiating this map's pair
			// destructor: ArchiveFile's /O2 pair body is not retail's, the /O1 body
			// in ArchiveDirInfoO1.cpp is, and a destroyable pair temporary here would
			// emit (and reference) it ahead of that unit.
			union BfmeDaiEntryBuffer { UnsignedInt m_align; unsigned char m_bytes[sizeof(DetailedArchivedDirectoryInfoMap::value_type)]; } buffer;
			DetailedArchivedDirectoryInfoMap::value_type *entry =
				new (buffer.m_bytes) DetailedArchivedDirectoryInfoMap::value_type(token, DetailedArchivedDirectoryInfo());
			it = dirInfo->m_directories.insert(*entry).first;
			const_cast<AsciiString &>(entry->first).clear();
			it->second.clear();
			it->second.m_directoryName = token;
		}

		((StringBase<char> *)&debugpath)->concat(*(const StringBase<char> *)&token);
		debugpath.concat('\\');
		dirInfo = &it->second;
		temp.nextToken(&token, "\\/");
	}

	dirInfo->m_files[fileInfo->m_filename] = *fileInfo;
	//path.concat(fileInfo->m_filename);
}

// ?ArchiveFile::getFileListInDirectory present-unmatched
void ArchiveFile::getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{

	AsciiString searchDir;
	const DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	searchDir = originalDirectory;
	((StringBase<char> *)&searchDir)->toLower();
	AsciiString token;
	
	searchDir.nextToken(&token, "\\/");

	while (token.getLength() > 0) {

		DetailedArchivedDirectoryInfoMap::const_iterator it = dirInfo->m_directories.find(token);
		if (it != dirInfo->m_directories.end())
		{
			dirInfo = &it->second;
		}
		else
		{
			// if the directory doesn't exist, then there aren't any files to be had.
			return;
		}

		searchDir.nextToken(&token, "\\/");
	}

	getFileListInDirectory(dirInfo, originalDirectory, searchName, filenameList, searchSubdirectories);
}

// ?ArchiveFile::getFileListInDirectory present-unmatched
void ArchiveFile::getFileListInDirectory(const DetailedArchivedDirectoryInfo *dirInfo, const AsciiString& currentDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{
	DetailedArchivedDirectoryInfoMap::const_iterator diriter = dirInfo->m_directories.begin();
	while (diriter != dirInfo->m_directories.end()) {
		const DetailedArchivedDirectoryInfo *detailedArchivedDirectoryInfo = &(diriter->second);
		AsciiString tempdirname;
		tempdirname = currentDirectory;
		if ((tempdirname.getLength() > 0) && (!tempdirname.endsWith("\\"))) {
			tempdirname.concat('\\');
		}
		((StringBase<char> *)&tempdirname)->concat(
			*(const StringBase<char> *)&detailedArchivedDirectoryInfo->m_directoryName);
		getFileListInDirectory(detailedArchivedDirectoryInfo, tempdirname, searchName, filenameList, searchSubdirectories);
		diriter++;
	}

	ArchivedFileInfoMap::const_iterator fileiter = dirInfo->m_files.begin();
	while (fileiter != dirInfo->m_files.end()) {
		if (SearchStringMatches(fileiter->second.m_filename, searchName)) {
			AsciiString tempfilename;
			tempfilename = currentDirectory;
			if ((tempfilename.getLength() > 0) && (!tempfilename.endsWith("\\"))) {
				tempfilename.concat('\\');
			}
			((StringBase<char> *)&tempfilename)->concat(
				*(const StringBase<char> *)&fileiter->second.m_filename);
			if (filenameList.find(tempfilename) == filenameList.end()) {
				// only insert into the list if its not already in there.
				filenameList.insert(tempfilename);
			}
		}
		fileiter++;
	}
}

// ?ArchiveFile::attachFile present-unmatched
void ArchiveFile::attachFile(File *file) 
{
	if (m_file != NULL) {
		m_file->close();
		m_file = NULL;
	}
	m_file = file;
}

// ?ArchiveFile::getArchivedFileInfo present-unmatched
const ArchivedFileInfo * ArchiveFile::getArchivedFileInfo(const AsciiString& filename) const
{
	AsciiString path;
	path = filename;
	((StringBase<char> *)&path)->toLower();
	AsciiString token;

	const DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	path.nextToken(&token, "\\/");

	while ((((const StringBase<char> *)&token)->find('.') == NULL) ||
		((const StringBase<char> *)&path)->find('.') != NULL) {

		DetailedArchivedDirectoryInfoMap::const_iterator it = dirInfo->m_directories.find(token);
		if (it != dirInfo->m_directories.end())
		{
			dirInfo = &it->second; 
		}
		else
		{
			return NULL;
		}

		path.nextToken(&token, "\\/");
	}

	ArchivedFileInfoMap::const_iterator it = dirInfo->m_files.find(token);
	if (it != dirInfo->m_files.end())
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}

}
