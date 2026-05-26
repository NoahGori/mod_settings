// #include "Addresses.hpp"
#include "ModSettings.hpp"
#include "ScriptData.hpp"
#include <Registrar.hpp>

// @hash 3993832650
// void *__fastcall ReleaseScriptData(ModSettings::ScriptData *scriptData);
// RED4ext::UniversalRelocFunc<void (*)(ModSettings::ScriptData *)> ReleaseScriptData(3993832650);

REGISTER_HOOK_HASH(void *, 3993832650, ReleaseScriptData, ModSettings::ScriptData *scriptData) {
  ModSettings::sdk->logger->Info(ModSettings::pluginHandle, "ReleaseScriptData: processing script data...");
  ModSettings::ModSettings::ProcessScriptData(scriptData);
  ModSettings::sdk->logger->Info(ModSettings::pluginHandle, "ReleaseScriptData: calling original...");
  auto og = ReleaseScriptData_Original(scriptData);
  ModSettings::sdk->logger->Info(ModSettings::pluginHandle, "ReleaseScriptData: done");
  return og;
}
