// #include "Addresses.hpp"
#include "ScriptData.hpp"
#include "ModSettings.hpp"
#include <Registrar.hpp>

// @hash 3993832650
// void *__fastcall ReleaseScriptData(ModSettings::ScriptData *scriptData);
// RED4ext::UniversalRelocFunc<void (*)(ModSettings::ScriptData *)> ReleaseScriptData(3993832650);

REGISTER_HOOK_HASH(void *, 3993832650, ReleaseScriptData, ModSettings::ScriptData *scriptData) {
  if (ModSettings::sdk) {
    ModSettings::sdk->logger->InfoF(ModSettings::pluginHandle, "Hook: ReleaseScriptData called (scriptData=%p)", scriptData);
  }
  ModSettings::ModSettings::ProcessScriptData(scriptData);
  if (ModSettings::sdk) {
    ModSettings::sdk->logger->InfoF(ModSettings::pluginHandle, "Hook: ReleaseScriptData finished (scriptData=%p)", scriptData);
  }
  auto og = ReleaseScriptData_Original(scriptData);
  return og;
}