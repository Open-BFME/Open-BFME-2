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

// FILE: NameKeyGenerator.h ///////////////////////////////////////////////////////////////////////
// Created:    Michael Booth, May 2001
//						 Colin Day, May 2001
// Desc:       Name key system to translate between names and unique key ids
///////////////////////////////////////////////////////////////////////////////////////////////////

// BFME shadow shim (TU-scoped; only Common/NameKeyGenerator.cpp uses this -I path).
// BFME2 retail establishes the following ABI differences from the donor header:
//   - init/reset's `m_nextID = 1` store lands at this+0x2bf48, i.e.
//     this+0xc+45007*4.  SOCKET_COUNT remains 45007, while m_sockets starts at
//     this+0xc after the inherited SubsystemInterface fields and a BFME2 pad.
//   - nameToKey(const AsciiString&) has an out-of-line retail body that forwards
//     to nameToKey(const char*); declare it out-of-line here so the reconstructed
//     Common/NameKeyGenerator.cpp emits that standalone overload.
//   - the retail name-to-key path maintains an auxiliary key->Bucket index after
//     m_sockets/m_nextID.  Its layout is modeled below for the verified path;
//     keyToName remains outside the byte-verified rows in this TU.

#pragma once

#ifndef __NAMEKEYGENERATOR_H_
#define __NAMEKEYGENERATOR_H_

#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameMemory.h"
#include "Common/AsciiString.h"
#include "Common/CriticalSection.h"

//-------------------------------------------------------------------------------------------------
/**
	Note that NameKeyType isn't a "real" enum, but an enum type used to enforce the
	fact that NameKeys are really magic cookies, and aren't really interchangeable
	with ints. NAMEKEY_INVALID is always a legal value, but all other values are dynamically
	determined at runtime. (The generated code is basically identical, of course.)
*/
//-------------------------------------------------------------------------------------------------
enum NameKeyType
{
	NAMEKEY_INVALID					= 0,
	NAMEKEY_MAX							= 1<<23,					// max ordinal value of a NameKey (some code relies on these fitting into 24 bits safely)
	FORCE_NAMEKEYTYPE_LONG	= 0x7fffffff	// a trick to ensure the NameKeyType is a 32-bit int
};

//-------------------------------------------------------------------------------------------------
/** A bucket entry for the name key generator */
//-------------------------------------------------------------------------------------------------
// BFME2: Bucket is NOT a MemoryPoolObject. Retail's freeSockets/keyToName/
// nameToKey bodies delete/construct Bucket with a SINGLE virtual call
// (`push 1; call [vtbl]`) with no separate getObjectMemoryPool() virtual call --
// i.e. plain `delete b;` through a lone virtual dtor slot, not
// MemoryPoolObject::deleteInstance()'s getObjectMemoryPool()+dtor+freeBlock 3-call
// sequence. Matches the already-documented BFME model (this file's own
// MP_GLUE_ALLOCATE comment: "BFME's retail exe has no pool-backed allocations at
// newInstance sites") and the DisplayString precedent (reference/shims/displaystring)
// of retail dropping MEMORY_POOL_GLUE's extra getObjectMemoryPool vtable slot.
// Keep the already-matched placement operator new/delete (??2Bucket/??3Bucket,
// 14B/12B) verbatim -- only the base class + the extra virtual are dropped.
class Bucket
{
public:

	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };

	inline void *operator new(size_t s, BucketMagicEnum e)
	{
		return ::operator new(s);
	}
	inline void operator delete(void *p, BucketMagicEnum e)
	{
		::operator delete(p);
	}

	Bucket();
	virtual ~Bucket();

	Bucket				*m_nextInSocket;
	NameKeyType		m_key;
	AsciiString		m_nameString;
};

inline Bucket::Bucket() : m_nextInSocket(NULL), m_key(NAMEKEY_INVALID) { }

//-------------------------------------------------------------------------------------------------
/** This class implements the conversion of an arbitrary string into a unique
	* integer "key". Calling the nameToKey() method with the same string is
	* guaranteed to return the same key. Also, all keys generated by an
	* instance of this class are guaranteed to be unique with respect to that
	* instance's catalog of names.  Multiple instances of this class can be
	* created to service multiple namespaces. */
//-------------------------------------------------------------------------------------------------
class NameKeyGenerator : public SubsystemInterface
{

public:

	NameKeyGenerator();
	virtual ~NameKeyGenerator();

	virtual void init();
	virtual void reset();
	virtual void update() { }

	/// Given a string, convert into a unique integer key.
	// BFME2: retail has a standalone out-of-line body for this overload (see
	// shim header comment above) -- declare only, define out-of-line in the .cpp.
	NameKeyType nameToKey(const AsciiString& name);
	NameKeyType nameToLowercaseKey(const AsciiString& name) { return nameToLowercaseKey(name.str()); }

	/// Given a string, convert into a unique integer key.
	NameKeyType nameToKey(const char* name);
	NameKeyType nameToLowercaseKey(const char *name);

	/**
		given a key, return the name. this is almost never needed,
		except for a few rare cases like object serialization. also
		note that it's not particularly fast; it does a dumb linear
		search for the key.
	*/
	AsciiString keyToName(NameKeyType key);

  // Get a string out of the INI. Store it into a NameKeyType
  static void parseStringAsNameKeyType( INI *ini, void *instance, void *store, const void* userData );

private:

	enum
	{
			// Proven byte-exact via NameKeyGenerator::init/reset's `m_nextID = 1` store
			// (retail offset this+0x2bf48 == this+0xc+45007*4): SOCKET_COUNT is NOT
			// drifted in BFME2, matches the ZH reference exactly.
		SOCKET_COUNT = 45007
	};

	void freeSockets();

	UnsignedInt		m_bfmePad;
	Bucket*				m_sockets[SOCKET_COUNT];			///< Catalog of all Buckets already generated
	UnsignedInt		m_nextID;											///< Next available ID

	// BFME2-only O(1) reverse key->Bucket index (this+0x2bf4c, right after m_nextID;
	// no donor-header equivalent).  Retail's constructor creates this auxiliary
	// map, freeSockets clears it, and nameToKey inserts each new key/value pair.
	// The node and storage sizes below follow the retail map helper's decoded
	// value layout and call ABI.
	//
	// It is modeled as raw storage rather than a real hash_map member because the
	// surrounding destructor is outside this TU's verified surface; a normal
	// hash_map member would add an implicit destructor call to that unclaimed body.
	class KeyToBucketMap
	{
	public:
		struct value_type
		{
			NameKeyType first;
			Bucket *second;

			value_type(NameKeyType key, Bucket *bucket) : first(key), second(bucket) { }
		};

		struct insert_result
		{
			void *first;
			void *second;
			bool inserted;
		};

		insert_result insert(const value_type& value);
		void clear();

	private:
		UnsignedInt m_storage[5];
	};
	UnsignedInt		m_keyToBucketStorage[(sizeof(KeyToBucketMap) + sizeof(UnsignedInt) - 1) / sizeof(UnsignedInt)];
	CriticalSection	m_mutex;
	KeyToBucketMap& keyToBucketMap() { return *reinterpret_cast<KeyToBucketMap*>(m_keyToBucketStorage); }

};  // end class NameKeyGenerator

//-------------------------------------------------------------------------------------------------
//           Externals
//-------------------------------------------------------------------------------------------------
extern NameKeyGenerator *TheNameKeyGenerator;  ///< just one namespace for now

// typing "TheNameKeyGenerator->nameToKey()" is awfully wordy. Here are shorter synonyms:
inline NameKeyType NAMEKEY(const AsciiString& name) { return TheNameKeyGenerator->nameToKey(name); }
inline NameKeyType NAMEKEY(const char* name) { return TheNameKeyGenerator->nameToKey(name); }

inline AsciiString KEYNAME(NameKeyType nk) { return TheNameKeyGenerator->keyToName(nk); }

//-------------------------------------------------------------------------------------------------
class StaticNameKey
{
private:
	mutable NameKeyType m_key;
	const char* m_name;
public:
	StaticNameKey(const char* p) : m_key(NAMEKEY_INVALID), m_name(p) {}
	NameKeyType key() const;
	// ugh, this is a little hokey, but lets us pretend that a StaticNameKey == NameKeyType
	inline operator NameKeyType() const { return key(); }
};

#endif // __NAMEKEYGENERATOR_H_
