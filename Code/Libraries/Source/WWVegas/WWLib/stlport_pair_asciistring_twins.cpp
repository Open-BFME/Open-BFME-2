// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport pair<const AsciiString, T> constructors for map value types whose
// copy constructors are rowed. Each is an EH-framed twin of a rowed pair
// constructor, identical to it except for its second-member copy call and its
// own __ehhandler, and that call lands on T's rowed copy constructor:
//
//   pair(const AsciiString &, const T &), 57 bytes, twins of 0x002027B1
//   (stlport_rb_tree_hint_asciistring_pair.cpp):
//     0x00303D6B  T = MapMetaData        (copy ctor 0x003039E8, MapMetaDataCopy.cpp)
//     0x003829AC  T = Open2Rec4F1120     (copy ctor 0x001EF485, Open2Records.cpp)
//     0x004106C1  T = Rva0045EF90Object  (copy ctor 0x004104FE, Rva0045EF90CopyConstructor.cpp)
//     0x00216296  T = Gen_003A8BE0       (copy ctor 0x0021613D, BfmeThreeStringCopyWH.cpp)
//   pair(const pair &), 61 bytes, twins of 0x002A1538
//   (stlport_rb_tree_hint_002a5895.cpp):
//     0x004105C4  T = Rva0045EF90Object
//     0x002161DE  T = Gen_003A8BE0
//
// The mapped types are declared only as far as these constructors need them.

#include "ascii_string.h"
#include <utility>
#include <memory>

class MapMetaData
{
public:
	MapMetaData(const MapMetaData &other);
	~MapMetaData();
};

class Open2Rec4F1120
{
public:
	Open2Rec4F1120(const Open2Rec4F1120 &other);
	~Open2Rec4F1120();
};

class Rva0045EF90Object
{
public:
	Rva0045EF90Object(const Rva0045EF90Object &other);
	~Rva0045EF90Object();
};

class Gen_003A8BE0
{
public:
	Gen_003A8BE0(const Gen_003A8BE0 &other);
	~Gen_003A8BE0();
};

template _STL::pair<const AsciiString, MapMetaData>::pair(const AsciiString &, const MapMetaData &);
template _STL::pair<const AsciiString, Open2Rec4F1120>::pair(const AsciiString &, const Open2Rec4F1120 &);
template _STL::pair<const AsciiString, Rva0045EF90Object>::pair(const AsciiString &, const Rva0045EF90Object &);
template _STL::pair<const AsciiString, Gen_003A8BE0>::pair(const AsciiString &, const Gen_003A8BE0 &);
template _STL::pair<const AsciiString, Rva0045EF90Object>::pair(const _STL::pair<const AsciiString, Rva0045EF90Object> &);
template _STL::pair<const AsciiString, Gen_003A8BE0>::pair(const _STL::pair<const AsciiString, Gen_003A8BE0> &);

template void _STL::_Construct<_STL::pair<const AsciiString, Rva0045EF90Object>, _STL::pair<const AsciiString, Rva0045EF90Object> >(_STL::pair<const AsciiString, Rva0045EF90Object> *, const _STL::pair<const AsciiString, Rva0045EF90Object> &);
