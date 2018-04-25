@ECHO OFF
CALL clean_intermediate_files.cmd
SET APP="UnrealEngineVersionChanger\bin\Debug\UnrealEngineVersionChanger.exe"
IF NOT EXIST %APP% ECHO UnrealEngineVersionChanger needs to be compiled!
IF EXIST %APP% CALL "UnrealEngineVersionChanger\bin\Debug\UnrealEngineVersionChanger.exe" 4.5
COPY /Y UE4ChromaSDKRT_4_5.uproject UE4ChromaSDKRT.uproject
CALL SwitchEngineVersion.cmd
IF EXIST "%CD%\ChromaSDKPlugin_4_5.zip" START "" OpenPluginBinaries.cmd
IF EXIST "%CD%\ChromaSDKPlugin_4_5.zip" "C:\Program Files\7-Zip\7zFM.exe" "%CD%\ChromaSDKPlugin_4_5.zip\ChromaSDKPlugin\Binaries\Win64\"
