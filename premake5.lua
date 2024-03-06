include "Dependencies.lua"

workspace "Ext2FileSystem"
   architecture "x86"
   startproject "Ext2FS"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
   include "Dependencies/spdlog"
group ""

include "project"
