// Retail139B callback atRVA007F8790; ret16 at7F8818 ends7F881BCC.
// Matcheddeletingdtor7F8970 andctor7F8730 writeprimaryvtable112B8A4 atthis0;
// its slot1 directlycontainsVA00BF8790. Secondarytable112B8A0 isatthis4.
// Demangler source/assertstrings establishsubsystem; originalmethodnameunknown.
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

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void slot08();
	virtual void fail( const char *expr, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();

struct Rva00804150ProtoMangleRef;

extern "C" Rva00804150ProtoMangleRef *ProtoMangleCreate(
	const char *server, int port, const char *gameID, const char *lkey );
void Rva008043F0Connect(
	Rva00804150ProtoMangleRef *ref, int myPort, const char *sessID );

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int slot08();
};

int Rva00656B60Get();

class PrototypeClass {
public:
 PrototypeClass();
 virtual ~PrototypeClass();
 int field04;
};

class Rva00808CB0LanGameEntry : public PrototypeClass {
public:
  __declspec(dllimport) __forceinline Rva00808CB0LanGameEntry() { field08=0; field0c=0; field04=0; }
  ~Rva00808CB0LanGameEntry();
  int field08, field0c;
};

class Rva00803080 {
public:
 Rva00803080() {}
 virtual void slot0(unsigned int) = 0;
};

class Rva007EAServiceList {
public: void add(Rva00803080*);
};

// The deleting destructor 0x00664FF0 inlines this destructor: the cleanup
// 0x00664FC0, then the +0x10 member and the primary base.
class BfmeE1036 { public: void bfmeGo1036E(); };

class DemanglerPrimary {
public:
 virtual ~DemanglerPrimary() {}
 virtual void rva007F8790(const char*,int,const char*,unsigned char) = 0;
 virtual void set(int,int) = 0;
};

class BfmeThingTWA : public DemanglerPrimary, public Rva00803080 {
public:
 BfmeThingTWA(Rva007EAServiceList*);
 virtual ~BfmeThingTWA() { reinterpret_cast<BfmeE1036*>(this)->bfmeGo1036E(); }
 virtual void slot0(unsigned int) = 0;
 virtual void rva007F8790(const char*,int,const char*,unsigned char);
 virtual void set(int,int);
 Rva00804150ProtoMangleRef *field08;
 int field0c;
 Rva00808CB0LanGameEntry packet;
 unsigned int field20;
 unsigned char field24;
 void (__cdecl *field28)(void *, void *);
 void *field2c;
};

void BfmeThingTWA::rva007F8790( const char *gameID, int port,
	const char *session, unsigned char flag )
{
	if( field0c != 0 )
		Rva007EB810Get()->fail(
			"mState == DEMANGLER_READY", "\\views\\feslbuild_main\\jabba\\fesl\\source\\demangler.cpp", 0x3B );

	Rva00804150ProtoMangleRef *ref = ProtoMangleCreate(
		"demangler.ea.com", 0xE4A, gameID, "" );
	field08 = ref;
	if( ref == 0 )
	{
		field28( &packet, field2c );
		return;
	}

	Rva008043F0Connect( ref, port, session );
	field24 = flag;
	field20 = ((Rva007E9B70Obj *)Rva00656B60Get())->slot08();
	field0c = 1;
}

