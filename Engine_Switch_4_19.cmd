@ECHO OFF
CALL clean_intermediate_files.cmd
SET APP="UnrealEngineVersionChanger\bin\Debug\UnrealEngineVersionChanger.exe"
IF NOT EXIST %APP% ECHO UnrealEngineVersionChanger needs to be compiled!
IF EXIST %APP% CALL %APP% 4.19
COPY /Y UE4ChromaSDKRT_4_19.uproject UE4ChromaSDKRT.uproject
CALL SwitchEngineVersion.cmd
IF EXIST "%CD%\ChromaSDKPlugin_4_19.zip" START "" OpenPluginBinaries.cmd
IF EXIST "%CD%\ChromaSDKPlugin_4_19.zip" "C:\Program Files\7-Zip\7zFM.exe" "%CD%\ChromaSDKPlugin_4_19.zip\ChromaSDKPlugin\Binaries\Win64\"
