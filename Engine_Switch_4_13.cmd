@ECHO OFF
CALL clean_intermediate_files.cmd
SET APP="UnrealEngineVersionChanger\bin\Debug\UnrealEngineVersionChanger.exe"
IF NOT EXIST %APP% ECHO UnrealEngineVersionChanger needs to be compiled!
IF EXIST %APP% CALL %APP% 4.13
COPY /Y UE4ChromaSDKRT_4_13.uproject UE4ChromaSDKRT.uproject
CALL SwitchEngineVersion.cmd
IF EXIST "%CD%\ChromaSDKPlugin_4_13.zip" START "" OpenPluginBinaries.cmd
IF EXIST "%CD%\ChromaSDKPlugin_4_13.zip" "C:\Program Files\7-Zip\7zFM.exe" "%CD%\ChromaSDKPlugin_4_13.zip\ChromaSDKPlugin\Binaries\Win64\"
