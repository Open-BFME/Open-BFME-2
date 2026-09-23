// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target member copy; original application record identity is unknown.
#include "OwnedRecord900.h"
extern template BfmeStringRecordTree900::_Rb_tree(const BfmeStringRecordTree900 &);
extern template BfmeStringRecordTree900::~_Rb_tree();
extern template void BfmeStringRecordTree900::clear();
extern template void BfmeStringRecordTree900::_M_erase(BfmeStringRecordTree900::_Link_type);
extern template BfmeStringRecordTree900::_Link_type
BfmeStringRecordTree900::_M_copy(BfmeStringRecordTree900::_Link_type, BfmeStringRecordTree900::_Link_type);
BfmeRecordOwner900::BfmeRecordOwner900(const BfmeRecordOwner900 &other)
    : fixed_000(other.fixed_000), fixed_080(other.fixed_080),
      strings_100(other.strings_100), strings_10C(other.strings_10C),
      fixed_118(other.fixed_118), fixed_164(other.fixed_164),
      records_1B0(other.records_1B0), tree_370(other.tree_370),
      unknown_37C(other.unknown_37C), unknown_380(other.unknown_380),
      unknown_381(other.unknown_381), unknown_382(other.unknown_382) {}
