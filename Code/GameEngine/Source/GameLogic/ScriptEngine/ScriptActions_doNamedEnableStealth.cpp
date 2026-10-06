// cl: /DNDEBUG /MD /EHsc
// ?doNamedEnableStealth@ScriptActions@@IAEXABVAsciiString@@_N@Z @0x003BBD39 40B
// Chain from Object::setScriptStatus 0x00292969: named-unit wrapper setting
// UNSTEALTHED bit 8 with !enabled. BFME1 donor ScriptActions.cpp
// doNamedEnableStealth establishes semantics; getUnitNamed pin 0x3588E7
// resolves the lookup. Caller 0x003CBD8F in executeAction dispatcher.

class AsciiString;
class Object;

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_UNSTEALTHED = 0x08
};

typedef bool Bool;

class Object
{
public:
    void setScriptStatus( ObjectScriptStatusBit bit, Bool set );
};

class ScriptEngine
{
public:
    Object *getUnitNamed( const AsciiString & );
};

class ScriptActions
{
protected:
    void doNamedEnableStealth( const AsciiString &, Bool );
    void rva003BBD61( const AsciiString &, Bool );
};

extern ScriptEngine *TheScriptEngine;

// ?doNamedEnableStealth@ScriptActions@@IAEXABVAsciiString@@_N@Z
void ScriptActions::doNamedEnableStealth( const AsciiString &unitName, Bool enabled )
{
    Object *self = TheScriptEngine->getUnitNamed( unitName );
    if( !self )
        return;
    self->setScriptStatus( OBJECT_STATUS_SCRIPT_UNSTEALTHED, !enabled );
}

// ?rva003BBD61@ScriptActions@@IAEXABVAsciiString@@_N@Z
void ScriptActions::rva003BBD61( const AsciiString &unitName, Bool enabled )
{
    Object *self = TheScriptEngine->getUnitNamed( unitName );
    if( !self )
        return;
    self->setScriptStatus( (ObjectScriptStatusBit)0x20, enabled );
}
