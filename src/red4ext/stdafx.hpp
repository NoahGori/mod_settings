#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

#include <TlHelp32.h>
#include <Windows.h>
// #include <detours.h>

#include <RED4ext/RED4ext.hpp>
// #include <spdlog/spdlog.h>

// The upstream RED4ext SDK places Sdk and PluginHandle in RED4ext::v1.
// Registrar.hpp (from the cpcmake submodule) uses RED4ext::Sdk / RED4ext::PluginHandle
// (the old jack-fork convention). Bridge the gap here.
namespace RED4ext {
using Sdk = v1::Sdk;
using PluginHandle = v1::PluginHandle;
} // namespace RED4ext
