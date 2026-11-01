// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Donor LanguageFilter initialization with the target file and string ABI.
// Target adds RAM-file conversion and delete-on-close; its map starts at +0xC.
// The filesystem forwards a third 32-bit argument, passed as zero here.
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

typedef int Int;
typedef bool Bool;
#include "unicode_string.h"


struct UnicodeStringLessThan {
    Bool operator()(UnicodeString a, UnicodeString b) const {
        return a.compareNoCase(b) < 0;
    }
};
typedef _STL::pair<const UnicodeString, bool> LanguageFilterValue;
typedef _STL::map<UnicodeString, bool, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterMap;

#include "../../Include/Common/File.h"
class FileSystem {
public:
    File *openFile(const char *filename, Int access, Int extra);
};
extern FileSystem *TheFileSystem;

static const char BadWordFileName[] = "langdata.dat";

class LanguageFilter {
public:
    virtual void init();
protected:
    bool readWord(File *file, unsigned short *buf);
    void unHaxor(UnicodeString &word);
    void *opaquePrefix[2];
    LanguageFilterMap m_wordList;
};

// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > * _Rb_tree<UnicodeString,_STL::pair<UnicodeString const,bool>,_STL::_Select1st<_STL::pair<UnicodeString const,bool> >,UnicodeStringLessThan,_STL::allocator<_STL::pair<UnicodeString const,bool> > >::_M_create_node(_STL::pair<UnicodeString const,bool> const &); }
namespace _STL { template <> void _Rb_tree<UnicodeString,_STL::pair<UnicodeString const,bool>,_STL::_Select1st<_STL::pair<UnicodeString const,bool> >,UnicodeStringLessThan,_STL::allocator<_STL::pair<UnicodeString const,bool> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > *); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > * allocator<_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > *,_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > *,unsigned int) const; }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<UnicodeString const,bool>,_STL::_Nonconst_traits<_STL::pair<UnicodeString const,bool> > >,bool> _Rb_tree<UnicodeString,_STL::pair<UnicodeString const,bool>,_STL::_Select1st<_STL::pair<UnicodeString const,bool> >,UnicodeStringLessThan,_STL::allocator<_STL::pair<UnicodeString const,bool> > >::insert_unique(_STL::pair<UnicodeString const,bool> const &); }
// bfme link decl-only end
void LanguageFilter::init()
{
    m_wordList.clear();
    File *file = TheFileSystem->openFile(BadWordFileName,
        File::READ | File::BINARY, 0);
    if (file == 0)
        return;
    file = file->convertToRAMFile();
    if (file == 0)
        return;
    file->deleteOnClose();
    unsigned short word[128];
    while (readWord(file, word)) {
        Int wordLen = wcslen(word);
        if (wordLen == 0)
            continue;
        for (Int i = 0; i < wordLen; ++i) {
            word[i] = word[i] ^ 0x5555;
        }
        UnicodeString uniword(word);
        unHaxor(uniword);
        m_wordList[uniword] = true;
    }
    file->close();
    file = 0;
}
