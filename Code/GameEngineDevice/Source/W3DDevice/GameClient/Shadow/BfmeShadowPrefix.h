// Shared minimum ABI views, not complete target class declarations.
// Native EFA4E/132 establishes stores at4..54; F0F2B and109D8C call it
// before installing BCEFA0. Its first slot targets EFAD2/28, which calls
// the108B4D/7 vtable reset and conditionally deletes this. The relation
// between the initializer prefix and owner base is inferred from those
// callers; original names and complete class/table extents remain unknown.
// Only the independently observed destructor slot is modeled here.
#pragma once
struct BfmeShadowVectorPrefix
{
	float x;
	float y;
	float z;
};

struct BfmeShadowPrefixFields
{
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[2];
	BfmeShadowVectorPrefix m_08;
	BfmeShadowVectorPrefix m_14;
	float m_20;
	int m_24;
	int m_28;
	int m_2C;
	unsigned char m_30;
	char m_pad31[3];
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
};
class Rva000EFA4E
{
public:
 void initialize();
private:
 unsigned int m_vptr00;
 BfmeShadowPrefixFields m_fields;
};
class BfmeShadowBufferOwnerBase
{
public:
 virtual ~BfmeShadowBufferOwnerBase() {}
protected:
 BfmeShadowPrefixFields m_fields;
};
