// Native stance-name table at VA C3C210: six pointers followed by null.
// Complete measured label extents and native indexed consumers are recorded
// in reverse/attempt_support/stance-names-owner/README.md.
// The existing TheStanceNames identifier is retained as the sole table owner.
// Label identifiers are descriptive; their original names are unknown.
// .rdata and all four executable references prove read-only table use.

// Native stance table: six complete NUL-terminated labels and a null.
// Label object names are descriptive; original names are unknown.
extern const char BfmeStanceNameUninitialized[];
const char BfmeStanceNameUninitialized[] = "Uninitialized";
extern const char BfmeStanceNameBattle[];
const char BfmeStanceNameBattle[] = "Battle";
extern const char BfmeStanceNameAggressive[];
const char BfmeStanceNameAggressive[] = "Aggressive";
extern const char BfmeStanceNameHoldGround[];
const char BfmeStanceNameHoldGround[] = "HoldGround";
extern const char BfmeStanceNamePorcupine[];
const char BfmeStanceNamePorcupine[] = "Porcupine";
extern const char BfmeStanceNameHoldGroundMoving[];
const char BfmeStanceNameHoldGroundMoving[] = "HoldGroundMoving";
extern const char *const TheStanceNames[];
const char *const TheStanceNames[] = {
    BfmeStanceNameUninitialized,
    BfmeStanceNameBattle,
    BfmeStanceNameAggressive,
    BfmeStanceNameHoldGround,
    BfmeStanceNamePorcupine,
    BfmeStanceNameHoldGroundMoving,
    0
};
