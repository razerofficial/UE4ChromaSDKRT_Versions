ECHO OFF
SET APP="UnrealEngineVersionChanger\bin\Debug\UnrealEngineVersionChanger.exe"
IF NOT EXIST %APP% ECHO UnrealEngineVersionChanger needs to be compiled!
IF NOT EXIST %APP% PAUSE
FOR /l %%i in (5, 1, 19) DO (
COPY /Y "empty.zip" "%CD%\ChromaSDKPlugin_Source_4_%%i.zip"
%APP% 4.%%i
COPY /Y UE4ChromaSDKRT_4_%%i.uproject UE4ChromaSDKRT.uproject
REM IF EXIST "%CD%\ChromaSDKPlugin_Source_4_%%i.zip" "C:\Program Files\7-Zip\7zFM.exe" "%CD%\ChromaSDKPlugin_Source_4_%%i.zip"
"C:\Program Files\7-Zip\7zFM.exe" "%CD%\ChromaSDKPlugin_Source_4_%%i.zip"
PAUSE
)
PAUSE
