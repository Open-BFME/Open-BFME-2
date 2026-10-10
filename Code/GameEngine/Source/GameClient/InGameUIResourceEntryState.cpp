// cl: /MD
// Native29BB8B..29BDBC cleanup paths call4E551E on this singleton address;
// the owned cleanup adjusts by4 then reads the list head. Own only this
// independently accessed eight-byte prefix; complete collector extent and
// the original global identifier remain unknown. Initial loader zeros
// and COFF sizeof8 are independently checked by the data-row gate.
struct BfmeUiResourceEntryState { unsigned unknown00; void *head; };
BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
