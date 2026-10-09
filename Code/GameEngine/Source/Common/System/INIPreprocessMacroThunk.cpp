// cl: /O1 /G7 /MD
// Native2D145..2D14A is a5B cdecl tail adapter to INI macro expansion2D0A9.
// Native149002 calls this adapter; WB728720 calls preprocessMacro for the
// same expansion-before-tokenization branch. The existing canonical pin's
// 156B target/body and macro table relationship establish the operation.
class INI {public:static const char *preprocessMacro(const char*);};
const char *rva0002D145(const char *token) {return INI::preprocessMacro(token);}
