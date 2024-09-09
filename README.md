# Plugin Template
Simple template and guide for building **ARK: Survival Evolved** server plugins using [AseApi](https://github.com/ArkServerApi/AseApi).
## Requirements
- A copy of this repository, including the AseApi submodule found in `extern\ArkServerApi\`
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/community/)
  - The "Desktop development with C++" workload should be installed via the Visual Studio Installer
- An **ARK: Survival Evolved** dedicated server with AseApi installed

**Note:** This plugin template is up-to-date with AseApi v3.56. If you require a newer version of the AseApi library or headers, you should pull the latest code from [AseApi](https://github.com/ArkServerApi/AseApi) into the `extern\ArkServerApi\` submodule.
## 1: Modify The Plugin Template
Open `PluginTemplate.sln` with Visual Studio and rename the solution and project with your desired plugin name. The plugin file produced by the build will be named `[ProjectName].dll`.

Add your plugin code to `src\Plugin.cpp`, or add additional source code files.
#### void Plugin_Init()
This function is called by AseApi when your plugin is loaded. This is a good place to do plugin setup such as initializing logging and installing hooks.
#### void Plugin_Unload()
This function is called by AseApi when your plugin is unloaded. Be sure to uninstall any hooks that your plugin has set and perform any other necessary cleanup.
## 2: Modify PluginInfo.json
`PluginInfo.json`, found in `configs\`, holds information about your plugin that is used by AseApi when the plugin is loaded.
#### FullName
The name of your plugin that AseApi will display on startup.
#### Description
A description of your plugin that AseApi will display on startup.
#### Version
The version of your plugin. Be sure to increase this value when releasing a new plugin build.
#### MinApiVersion
The minimum version of AseApi required to load your plugin. I recommend setting this to the version of AseApi that you have built your plugin with or the lowest AseApi version you have tested with.
#### Dependencies
An array of plugin names that are required by your plugin. After loading all plugins on startup, AseApi will check if any plugins have unmet dependencies and display warnings.
## 3: Install Your Plugin
After building your plugin solution, the output can be found in the `build\` directory.
#### [PluginName].dll
This is your plugin. Your plugin can be installed on an **ARK: Survival Evolved** server by placing this DLL, along with `PluginInfo.json`, into the server's `ShooterGame\Binaries\Win64\ArkApi\Plugins\[PluginName]\` directory.
#### [PluginName].dll.arkapi
This is simply a copy of your plugin DLL that can be used to ease testing. If your plugin is already loaded, you can drop `[PluginName].dll.arkapi` into the `ShooterGame\Binaries\Win64\ArkApi\Plugins\[PluginName]\` server directory and AseApi will automatically reload the plugin and rename this file to `[PluginName].dll`.

**Note:** AseApi's automatic plugin reloading can be configured in AseApi's `config.json` file on the server.
#### [PluginName].pdb
This file contains debug info that provides more detailed information when using a debugger or if the server is producing crash logs. If you want to take advantage of this file, you can place it in the server's `ShooterGame\Binaries\Win64\ArkApi\Plugins\[PluginName]\` directory.
