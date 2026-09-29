param(
    [Parameter(Mandatory = $true)][string]$SourceDirectory,
    [Parameter(Mandatory = $true)][string]$OutputPath
)

$sources = @(Get-ChildItem -LiteralPath $SourceDirectory -File -Filter '*.cpp' | ForEach-Object { $_.FullName })
if ($sources.Count -eq 0) {
    Write-Error "No .cpp files found in $SourceDirectory"
    exit 1
}

$compiler = 'D:\mingw\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-14.0.0-r7\mingw64\bin\g++.exe'
& $compiler -std=c++17 -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wall -Wextra -Wpedantic -fdiagnostics-color=always -g3 -O0 @sources "$PSScriptRoot\console-utf8.cpp" -o $OutputPath
exit $LASTEXITCODE
