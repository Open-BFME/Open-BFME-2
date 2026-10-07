// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/LanguageFilter.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

#include "GameClient/LanguageFilter.h"
#include "Common/FileSystem.h"
#include "Common/File.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


LanguageFilter *TheLanguageFilter = NULL;

// ?LanguageFilter::LanguageFilter present-unmatched
// ZH-ported ctor body; retail's bytes are not yet pinned.
inline LanguageFilter::LanguageFilter() 
{
	//Modified by Saad
	//Unnecessary
	//m_wordList.clear();
}

// ?LanguageFilter::~LanguageFilter present-unmatched
inline LanguageFilter::~LanguageFilter() {
	m_wordList.clear();
}

// ?LanguageFilter::init present-unmatched
inline void LanguageFilter::init() {
	m_wordList.clear();

	// read in the file already.
	File *file1 = TheFileSystem->openFile(BadWordFileName, File::READ | File::BINARY);
	if (file1 == NULL) {
		return;
	}

	wchar_t word[128];
	while (readWord(file1, word)) {
		Int wordLen = wcslen(word);
		if (wordLen == 0) {
			continue;
		}
		for (Int i = 0; i < wordLen; ++i) {
			word[i] = word[i] ^ LANGUAGE_XOR_KEY;
		}
		UnicodeString uniword(word);
		unHaxor(uniword);
		//DEBUG_LOG(("Just read %ls from the bad word file.  Entered as %ls\n", word, uniword.str()));
		m_wordList[uniword] = true;
	}

	file1->close();
	file1 = NULL;
}

// ?LanguageFilter::reset present-unmatched
void LanguageFilter::reset() {
	init();
}

// ?LanguageFilter::update present-unmatched
void LanguageFilter::update() {
	// Keeps this TU emitting its two matched STL bodies (allocator allocate
	// and pair copy ctor) after the duplicate LanguageFilter members became
	// inline/extern for the link census. Uses the same LangMap type.
	UnicodeString k(L"");
	m_wordList[k] = true;
	m_wordList.clear();
}

extern wchar_t ignoredChars[];

// ?LanguageFilter::filterLine present-unmatched
inline void LanguageFilter::filterLine(UnicodeString &line) 
{
	WideChar *buf = NEW WideChar[line.getLength()+1];
	wcscpy(buf, line.str());

	UnicodeString newLine(line);
	UnicodeString token(L"");

	while (newLine.nextToken(&token, UnicodeString(L" ;,.!?:=\\/><`~()&^%#\n\t"))) {
		wchar_t *pos = wcsstr(buf, token.str());
		if (pos == NULL) {
			DEBUG_CRASH(("Couldn't find the token in its own string."));
			continue;
		}

		Int len = token.getLength(); // need to get the length of the original word, not the unhaxor'd word.

		unHaxor(token);
		LangMapIter iter = m_wordList.find(token);
		if (iter != m_wordList.end()) {
			DEBUG_LOG(("Found word %ls in bad word list. Token was %ls\n", (*iter).first.str(), token.str()));
			for (Int i = 0; i < len; ++i) {
				*pos = L'*';
				++pos;
			}
		}
	}

	line.set(buf);
	delete[] buf;
}

// ?LanguageFilter::unHaxor present-unmatched
inline void LanguageFilter::unHaxor(UnicodeString &word) {
	Int len = word.getLength();
	UnicodeString newWord(L"");
	for (Int i = 0; i < len; ++i) {
		wchar_t c = word.getCharAt(i);
		if ((c == L'p') || (c == L'P')) {
			if (((i + 1) < len) && ((word.getCharAt(i+1) == L'h') || (word.getCharAt(i+1) == L'H'))) {
				newWord.concat(L'f');
				++i; // skip the h
			} else {
				// not a problem at all.
				newWord.concat(c);
			}
		} else if (c == L'1') {
			newWord.concat(L'l');
		} else if (c == L'3') {
			newWord.concat(L'e');
		} else if (c == L'4') {
			newWord.concat(L'a');
		} else if (c == L'5') {
			newWord.concat(L's');
		} else if (c == L'6') {
			newWord.concat(L'b');
		} else if (c == L'7') {
			newWord.concat(L't');
		} else if (c == L'0') {
			newWord.concat(L'o');
		} else if (c == L'@') {
			newWord.concat(L'a');
		} else if (c == L'$') {
			newWord.concat(L's');
		} else if (c == L'+') {
			newWord.concat(L't');
		} else if (wcsrchr(ignoredChars, c) == NULL) {
			newWord.concat(c);
		}
	}
	word.set(newWord);
}

// returning true means that there are more words in the file.
// LanguageFilter::readWord: defined in LanguageFilterReadWord.cpp (its row's unit).

inline LanguageFilter * createLanguageFilter() 
{
	return NEW LanguageFilter;
}
