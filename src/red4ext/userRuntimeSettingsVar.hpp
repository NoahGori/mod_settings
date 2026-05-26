#pragma once

// Local copy of game structs originally from jack fork's RED4ext.SDK.
// The upstream SDK does not ship these non-generated game type definitions.

#include "RED4ext/CName.hpp"
#include "RED4ext/DynArray.hpp"
#include <RED4ext/Common.hpp>
#include <stdint.h>

namespace RED4ext {
namespace user {

struct ConfigVarFlags {
  uint32_t isInPreGame : 1;            // 0x001
  uint32_t isInGame : 1;               // 0x002
  uint32_t isVisible : 1;              // 0x004
  uint32_t isPlatformSpecific : 1;     // 0x008
  uint32_t isDynamic : 1;              // 0x010
  uint32_t unk20 : 1;                  // 0x020
  uint32_t isInitialized : 1;          // 0x040
  uint32_t listHasDisplayValues : 1;   // 0x080
  uint32_t canBeRestoredToDefault : 1; // 0x100
  uint32_t isInput : 1;                // 0x200
  uint32_t isDisabled : 1;             // 0x400
};

enum class EConfigVarType : char {
  Bool = 0,       // bool
  Int = 1,        // int
  Float = 2,      // float
  Name = 3,       // name
  IntList = 4,    // int_list
  FloatList = 5,  // float_list
  StringList = 6, // string_list
  NameList = 7,   // name_list
};

enum class EConfigVarUpdatePolicy : char {
  Disabled = 0,                   // update_disabled
  Immediately = 1,                // immediately
  ConfirmationRequired = 2,       // require_confirmation
  RestartRequired = 3,            // require_restart
  LoadLastCheckpointRequired = 4, // require_load_last_checkpoint
};

enum class EConfigVarImportPolicy : char {
  ReadValue = 0x0, // read_value
  Ignore = 0x1     // ignore
};

// InGameConfig::Var (updated for game 2.3: added warning CName, size 0x54)
#pragma pack(push, 1)
struct RuntimeSettingsVar {
  RuntimeSettingsVar() {
    displayNameKeys = RED4ext::DynArray<RED4ext::CName>(new RED4ext::Memory::DefaultAllocator());
    unk44 = 0xFF;
    unk45 = 0xFF;
    memset(&bitfield, 0, sizeof(bitfield));
  }

  virtual RED4ext::Memory::IAllocator *__fastcall GetAllocator(RuntimeSettingsVar *) // 00
  {
    return new Memory::DefaultAllocator();
  }
  virtual RuntimeSettingsVar *__fastcall Deinitialize(bool shouldFree) // 08
  {
    if (displayNameKeys.capacity) {
      displayNameKeys.Clear();
    }
    return this;
  }
  virtual bool __fastcall WasModifiedSinceLastSave() = 0;     // 10
  virtual bool __fastcall HasChange() = 0;                    // 18
  virtual bool __fastcall IsDefault() = 0;                    // 20
  virtual bool __fastcall RestoreDefault(uint8_t) = 0;        // 28
  virtual void __fastcall SetRequestedValue(void *value) = 0; // 30
  virtual void __fastcall AcceptChange() = 0;                 // 38
  virtual void __fastcall RejectChange() = 0;                 // 40
  virtual void __fastcall MarkAsSaved() = 0;                  // 48
  virtual void __fastcall LoadValue(void *value) = 0;         // 50

  CName name = CName();                                                      // 08
  CName groupPath = CName();                                                 // 10
  CName displayName = CName();                                               // 18
  DynArray<CName> displayNameKeys;                                           // 20
  CName description = CName();                                               // 30
  CName warning = CName();                                                   // 38 (new in 2.3)
  EConfigVarType type;                                                       // 40
  EConfigVarUpdatePolicy updatePolicy = EConfigVarUpdatePolicy::Immediately; // 41
  EConfigVarImportPolicy importPolicy = EConfigVarImportPolicy::ReadValue;   // 42
  uint8_t unk3B;                                                             // 43
  ConfigVarFlags bitfield;                                                   // 44
  uint32_t order;                                                            // 48
  uint8_t unk44;                                                             // 4C
  uint8_t unk45;                                                             // 4D
  uint8_t unk46;                                                             // 4E
  uint8_t unk47;                                                             // 4F
  uint32_t unk50_new;                                                        // 50 (new in 2.3)
};
RED4EXT_ASSERT_SIZE(RuntimeSettingsVar, 0x54);
#pragma pack(pop)

} // namespace user
} // namespace RED4ext
