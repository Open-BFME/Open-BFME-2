// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f ScienceStoreFriendGetScienceNames semantic donor.
// Retail1FFCA3..1FFD2C keeps the donor's name-collection purpose and loop.
// Native: ScienceStore vector+C/+10, ScienceInfo key+10, override pointer+4;
// keyToName148C95 returns a reference, so BFME2 constructs no string temporary.
// Return vector copyBC07E and cleanup2CC70 are existing verified providers.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include "ascii_string.h"

// Retail already provides these concrete string-vector operations. Declare
// them here so this caller uses those providers with their established ABI.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> > &);
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString &);
}

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName( NameKeyType key );
};

extern NameKeyGenerator *TheNameKeyGenerator;

// Retail next-override hop uses the established address-derived view at1E35DF.
// The donor calls this base Overridable; the target spelling remains unproven.
class Rva001E35DFView
{
public:
	const Rva001E35DFView *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

public:
	void *m_unmodelled00;
	Rva001E35DFView *m_nextOverride;
	bool m_isOverride;
};

class Rva0043D3A8 {
public:
    virtual bool v00(ScienceType science) const;
};

class ScienceInfo : public Rva001E35DFView
{
public:
	Int m_unmodelled0c;
	ScienceType m_science;
	char m_nameAndDescription[8];
	std::vector<std::vector<ScienceType> > m_prereqGroups;
};

typedef std::vector<ScienceInfo *> ScienceInfoVec;

class ScienceStore
{
public:
	std::vector<AsciiString> friend_getScienceNames() const;
	bool playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType st) const;
private:
	const ScienceInfo *findScienceInfo(ScienceType st) const;

private:
	void *m_unmodelled00;
	Int m_unmodelled04;
	Int m_unmodelled08;
	ScienceInfoVec m_sciences;
};

std::vector<AsciiString> ScienceStore::friend_getScienceNames() const
{
	std::vector<AsciiString> v;
	for ( ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it )
	{
		const ScienceInfo *si = (const ScienceInfo *)( *it )->getFinalOverride();
		NameKeyType nk = (NameKeyType)( si->m_science );
		v.push_back( TheNameKeyGenerator->keyToName( nk ) );
	}
	return v;
}

// Existing 47-byte lookup keeps the same null-guarded native override hop.
const ScienceInfo *ScienceStore::findScienceInfo(ScienceType st) const
{
    ScienceInfo *const *begin = m_sciences.begin();
    ScienceInfo *const *end = m_sciences.end();
    for (ScienceInfo *const *it = begin; it != end; ++it) {
        const ScienceInfo *si = (const ScienceInfo *)(*it)->getFinalOverride();
        if (si->m_science == st)
            return si;
    }
    return 0;
}

// BFME1 Science.cpp nested prerequisite groups guide; retail1FF47D..1FF4D3
// tests each group through the holder's virtual slot0 and accepts any full group.
bool ScienceStore::playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType st) const
{
    const ScienceInfo *si = findScienceInfo(st);
    if (si) {
        if (si->m_prereqGroups.size() == 0)
            return true;
        for (std::vector<std::vector<ScienceType> >::const_iterator g = si->m_prereqGroups.begin(); g != si->m_prereqGroups.end(); ++g) {
            for (std::vector<ScienceType>::const_iterator p = g->begin();; ++p) {
                if (p == g->end())
                    return true;
                // Native captures the science key before reading the holder vtable.
                // Keep that evaluation order without runtime instructions.
                ScienceType key = *p;
                _ReadWriteBarrier();
                if (!holder->v00(key))
                    break;
            }
        }
    }
    return false;
}
