ECHO OFF
SET APP="UnrealEngineVersionChanger\bin\Release\UnrealEngineVersionChanger.exe"
IF NOT EXIST %APP% ECHO UnrealEngineVersionChanger needs to be compiled!
IF NOT EXIST %APP% PAUSE
FOR /l %%i in (5, 1, 20) DO (
COPY /Y "empty.zip" "%CD%\ChromaSDKPlugin_Source_4_%%i.zip"
%APP% 4.%%i
COPY /Y UE4ChromaSDKRT_4_%%i.uproject UE4ChromaSDKRT.uproject
"C:\Program Files\7-Zip\7z" a "%CD%\ChromaSDKPlugin_Source_4_%%i.zip" UE4ChromaSDKRT.uproject
"C:\Program Files\7-Zip\7z" a "%CD%\ChromaSDKPlugin_Source_4_%%i.zip" Source
"C:\Program Files\7-Zip\7z" a "%CD%\ChromaSDKPlugin_Source_4_%%i.zip" Plugins\ChromaSDKPlugin\ChromaSDKPlugin.uplugin
"C:\Program Files\7-Zip\7z" a "%CD%\ChromaSDKPlugin_Source_4_%%i.zip" Plugins\ChromaSDKPlugin\Resources
"C:\Program Files\7-Zip\7z" a "%CD%\ChromaSDKPlugin_Source_4_%%i.zip" Plugins\ChromaSDKPlugin\Source
REM "C:\Program Files\7-Zip\7zFM.exe" "%CD%\ChromaSDKPlugin_Source_4_%%i.zip"
REM PAUSE
)
PAUSE
