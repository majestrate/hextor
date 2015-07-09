AppName=Hextor Spelling Dictionaries
AppVerName=Hextor Spelling Dictionaries r1
AppVersion=1.0
VersionInfoVersion=1.0
OutputBaseFilename=Hextor Spelling Dictionaries r1
AppPublisher=Hextor
AppPublisherURL=http://www.hextor.org/
AppCopyright=Copyright (C) 1998-2010 Peter Zelezny
AppSupportURL=https://github.com/hextor/hextor/issues
AppUpdatesURL=http://www.hextor.org/home/downloads
DefaultDirName={localappdata}\enchant
DefaultGroupName=Hextor
DisableProgramGroupPage=yes
DisableDirPage=yes
SolidCompression=yes
Compression=lzma2/ultra64
SourceDir=.
OutputDir=.
FlatComponentsList=no
PrivilegesRequired=lowest
ShowComponentSizes=no
CreateUninstallRegKey=no
Uninstallable=no
DirExistsWarning=no
ArchitecturesAllowed=x86 x64

[Files]
Source: "myspell\*"; DestDir: "{app}\myspell"; Flags: createallsubdirs recursesubdirs

[Messages]
BeveledLabel= Hextor
