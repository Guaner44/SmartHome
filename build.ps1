# 用 g++ 直接编译（Windows + MinGW，或 Linux 均可用）
# 用法：powershell -File .\build.ps1
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Push-Location $root
try {
    New-Item -ItemType Directory -Force -Path build | Out-Null
    & g++ -std=c++17 -Wall -Wextra -O2 -Iinclude `
        src/main.cpp src/Device.cpp src/DeviceManager.cpp src/ConsoleInput.cpp `
        -o build/smart_home_lab01.exe
    if ($LASTEXITCODE -ne 0) { throw "编译失败（exit $LASTEXITCODE）" }
    Write-Host "编译成功：build\smart_home_lab01.exe"
}
finally {
    Pop-Location
}
