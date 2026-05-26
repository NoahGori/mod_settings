#include "RED4ext/RTTISystem.hpp"
#include "Red/TypeInfo/Registrar.hpp"
#include "Utils.hpp"
#include <RED4ext/Common.hpp>
#include <Windows.h>
#include <stdio.h>

#include "ModSettings.hpp"

#include <ArchiveXL.hpp>
#include <CNames.hpp>
#include <CyberpunkMod.hpp>
#include <RedLib.hpp>

namespace ModSettings {
const RED4ext::v1::Sdk *sdk;
RED4ext::v1::PluginHandle pluginHandle;
} // namespace ModSettings

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    ModSettings::ModSettings::GetInstance();
    break;
  }
  return true;
}

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(RED4ext::v1::PluginHandle aHandle, RED4ext::v1::EMainReason aReason,
                                        const RED4ext::v1::Sdk *aSdk) {
  switch (aReason) {
  case RED4ext::v1::EMainReason::Load: {
    ModSettings::sdk = aSdk;
    ModSettings::pluginHandle = aHandle;

    aSdk->logger->Info(aHandle, "Starting up Mod Settings " MOD_VERSION_STR);
    auto ptr = GetModuleHandle(nullptr);
    aSdk->logger->InfoF(aHandle, "Base address: %p", ptr);

    aSdk->logger->Info(aHandle, "Getting root directory...");
    auto rootDir = Utils::GetRootDir();
    auto rootDirStr = rootDir.string();
    aSdk->logger->InfoF(aHandle, "Root directory: %s", rootDirStr.c_str());

    aSdk->logger->Info(aHandle, "Checking for old scripts folder...");
    auto scriptsFolder = rootDir / "r6" / "scripts" / "mod_settings";
    if (std::filesystem::exists(scriptsFolder)) {
      aSdk->logger->Info(aHandle, "Deleting old scripts folder");
      std::filesystem::remove_all(scriptsFolder);
    }
    aSdk->logger->Info(aHandle, "Checking for old archive...");
    auto archive = rootDir / "archive" / "pc" / "mod" / "ModSettings.archive";
    if (std::filesystem::exists(archive)) {
      aSdk->logger->Info(aHandle, "Deleting old archive");
      std::filesystem::remove_all(archive);
    }
    aSdk->logger->Info(aHandle, "Checking for old archive.xl...");
    auto archiveXL = rootDir / "archive" / "pc" / "mod" / "ModSettings.archive.xl";
    if (std::filesystem::exists(archiveXL)) {
      aSdk->logger->Info(aHandle, "Deleting old archive.xl");
      std::filesystem::remove_all(archiveXL);
    }
    aSdk->logger->Info(aHandle, "Checking for old xl...");
    auto XL = rootDir / "archive" / "pc" / "mod" / "ModSettings.xl";
    if (std::filesystem::exists(XL)) {
      aSdk->logger->Info(aHandle, "Deleting old xl");
      std::filesystem::remove_all(XL);
    }

    aSdk->logger->Info(aHandle, "Registering type info...");
    Red::TypeInfoRegistrar::RegisterDiscovered();
    aSdk->logger->Info(aHandle, "Type info registered");

    aSdk->logger->Info(aHandle, "Adding scripts...");
    aSdk->scripts->Add(aHandle, L"packed.reds");
    aSdk->scripts->Add(aHandle, L"module.reds");
    aSdk->logger->Info(aHandle, "Scripts added");

    aSdk->logger->Info(aHandle, "Registering archive...");
    ArchiveXL::RegisterArchive(aHandle, "ModSettings.archive");
    aSdk->logger->Info(aHandle, "Archive registered");

    aSdk->logger->Info(aHandle, "Loading module factory...");
    ModModuleFactory::GetInstance().Load(aSdk, aHandle);
    aSdk->logger->Info(aHandle, "Load complete");
    // Engine::RTTIRegistrar::RegisterPending();

    break;
  }
  case RED4ext::v1::EMainReason::Unload: {
    aSdk->logger->Info(aHandle, "Shutting down");
    ModModuleFactory::GetInstance().Unload(aSdk, aHandle);
    break;
  }
  }

  return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::v1::PluginInfo *aInfo) {
  aInfo->name = L"Mod Settings";
  aInfo->author = L"Jack Humbert";
  aInfo->version = RED4EXT_V1_SEMVER(MOD_VERSION_MAJOR, MOD_VERSION_MINOR, MOD_VERSION_PATCH);
  // aInfo->runtime = RED4EXT_V1_RUNTIME_VERSION_LATEST;
  aInfo->runtime = RED4EXT_V1_RUNTIME_VERSION_INDEPENDENT;
  aInfo->sdk = RED4EXT_V1_SDK_VERSION_CURRENT;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports() { return RED4EXT_API_VERSION_1; }
