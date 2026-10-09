// cl: /O1 /DNDEBUG /MD
// WBCA4BE0 is an empty member called on the drawable returned by
// builder->getDrawable() in WB116CFB0 GettingBuiltBehavior::resumeBuildingConstruction.
// Retail454B49 calls the shared one-byte RETB3FD0. No original spelling is known.
class Drawable { public: void rva000B3FD0(); };
void Drawable::rva000B3FD0() {}
