// ??1NameKeyGenerator@@UAE@XZ
// partial score=0.96 date=2026-10-07
// ??1NameKeyGenerator@@UAE@XZ
// partial score=0.95 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHsc /Oi- /Ireference/shims/sweep /Ireference/shims/bfme_namekey /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
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

// FILE: NameKeyGenerator.cpp /////////////////////////////////////////////////////////////////////
// Created:   Michael Booth, May 2001
//						Colin Day, May 2001
// Desc:      Name key system to translate between names and unique key ids
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"

__declspec(noinline) UnsignedInt calcHashForString(const char* p);

//-------------------------------------------------------------------------------------------------
// BFME2's retail body inserts the new bucket into the reverse key->Bucket index
// after linking it into the socket list.  The TU-scoped shim models that index
// and its independently pinned insertion helper.
NameKeyType NameKeyGenerator::nameToKey(const char* nameString)
{
	Bucket *b;
	ScopedCriticalSection scopedCriticalSection(&m_mutex);

	UnsignedInt hash = calcHashForString(nameString) % SOCKET_COUNT;

	// hmm, do we have it already?
	for (b = m_sockets[hash]; b; b = b->m_nextInSocket)
	{
		if (strcmp(nameString, b->m_nameString.str()) == 0)
			return b->m_key;
	}

	// nope, guess not. let's allocate it.
	b = newInstance(Bucket);
	b->m_key = (NameKeyType)m_nextID++;
	((StringBase<char>*)&b->m_nameString)->set(nameString);
	b->m_nextInSocket = m_sockets[hash];
	m_sockets[hash] = b;

	// BFME2 also indexes it in the reverse key->Bucket map (see the shim).
	keyToBucketMap().insert(KeyToBucketMap::value_type(b->m_key, b));

	NameKeyType result = b->m_key;

#if defined(_DEBUG) || defined(_INTERNAL)
	// reality-check to be sure our hasher isn't going bad.
	const Int maxThresh = 3;
	Int numOverThresh = 0;
	for (Int i = 0; i < SOCKET_COUNT; ++i)
	{
		Int numInThisSocket = 0;
		for (b = m_sockets[i]; b; b = b->m_nextInSocket)
			++numInThisSocket;

		if (numInThisSocket > maxThresh)
			++numOverThresh;
	}

	// if more than a small percent of the sockets are getting deep, probably want to increase the socket count.
	if (numOverThresh > SOCKET_COUNT/20)
	{
		DEBUG_CRASH(("hmm, might need to increase the number of bucket-sockets for NameKeyGenerator (numOverThresh %d = %f%%)\n",numOverThresh,(Real)numOverThresh/(Real)(SOCKET_COUNT/20)));
	}
#endif

	return result;

}  // end nameToKey

// ?freeSockets@NameKeyGenerator@@AAEXXZ 0x00148B42 66B donor ZH NameKeyGenerator.cpp freeSockets plus BFME aux KeyToBucketMap clear; callers 0x00148BFB 0x00148C6B; tail clear at this+0x2bf4c rowed as Armor hashtable clear via ICF fold
#include "GameLogic/Armor.h"

// The NameKeyGenerator singleton pointer. Matched DIR32 sites (e.g. the
// Rva00148F5ECache::get row at 0x00148F5E reads it with mov ecx,[0x00DF36A4])
// place it at VA 0x00DF36A4 in the .data zero-fill tail, so retail starts it
// null. Upstream 6c58ed268 deleted the split-out unit that used to define it.
NameKeyGenerator *TheNameKeyGenerator = NULL;
void NameKeyGenerator::freeSockets()
{
	for (Int i = 0; i < SOCKET_COUNT; ++i)
	{
		Bucket *next;
		for (Bucket *b = m_sockets[i]; b; b = next)
		{
			next = b->m_nextInSocket;
			struct FakeBucket { virtual void *del(int flag); };
			void *mem = ((FakeBucket *)b)->del(0);
			::operator delete(mem);
		}
		m_sockets[i] = NULL;
	}
	// Tail clears the aux key->Bucket index at this+0x2bf4c. Retail folds its
	// hashtable::clear body onto the ArmorTemplate instantiation at 0x1DBCDC,
	// so call through that rowed spelling; same lea+jmp shape as the donor.
	((std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > &)keyToBucketMap()).clear();
}  // end freeSockets

// ?reset@NameKeyGenerator@@UAEXXZ 0x00148C41 84B chain from freeSockets 0x00148B42; ZH reset plus BFME lock; sets m_nextID at this+0x2bf48
void NameKeyGenerator::reset()
{
	ScopedCriticalSection scopedCriticalSection(&m_mutex);
	freeSockets();
	m_nextID = 1;
}  // end reset

// ??1NameKeyGenerator@@UAE@XZ 0x00148BC2 127B
// Target evidence: vtable 0x00BD3568, freeSockets() at 0x00148B42, the scoped
// lock at m_mutex (+0x2BF60), map storage at +0x2BF4C, and SubsystemInterface
// base teardown at 0x001B4E74.  The prior raw-storage shim omitted the map
// destructor, which is why this body was not previously in this TU.
NameKeyGenerator::~NameKeyGenerator()
{
	ScopedCriticalSection scopedCriticalSection(&m_mutex);
	freeSockets();
	((std::hash_map<NameKeyType, Bucket *, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > *)&keyToBucketMap())->~hash_map();
}
