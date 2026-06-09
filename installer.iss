#define MyAppName "FOCWorld TCG"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "FOC JJK (by Neau)"
#define MyAppExeName "focworld_tcg.exe"

[Setup]
AppId={{5F7C32AB-C5E9-4C45-A6B1-D43AB3F5A829}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=Output
OutputBaseFilename=FOCWorld_TCG_Setup
SetupIconFile=assets\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "build\Release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\Release\*.dll"; DestDir: "{app}"; Flags: ignoreversion skipifsourcedoesntexist
Source: "assets\*"; DestDir: "{app}\assets"; Flags: ignoreversion recursesubdirs createallsubdirs
; Add any extra DLLs if needed, though they should be statically linked or system provided since we use vcpkg

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Registry]
; Register the foc-tcg:// protocol
Root: HKCR; Subkey: "foc-tcg"; ValueType: string; ValueName: ""; ValueData: "URL:FOC TCG Protocol"; Flags: uninsdeletekey
Root: HKCR; Subkey: "foc-tcg"; ValueType: string; ValueName: "URL Protocol"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "foc-tcg\shell"; Flags: uninsdeletekey
Root: HKCR; Subkey: "foc-tcg\shell\open"; Flags: uninsdeletekey
Root: HKCR; Subkey: "foc-tcg\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""; Flags: uninsdeletevalue

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
Filename: "{app}\{#MyAppExeName}"; Flags: nowait; Check: WizardSilent
