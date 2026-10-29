# 一键回归：重新编译并跑完全部测试用例，覆盖 tests\*_output.txt
# 用法：powershell -ExecutionPolicy Bypass -File .\tests\run_tests.ps1
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$exe = Join-Path $root 'build\smart_home_lab01.exe'

if (-not (Test-Path $exe)) {
    & (Join-Path $root 'build.ps1')
}

Push-Location $root
try {
    foreach ($case in 'T1', 'T2', 'T3', 'B1') {
        $in = Join-Path $root "tests\${case}_input.txt"
        $out = Join-Path $root "tests\${case}_output.txt"
        cmd /c "`"$exe`" < `"$in`" > `"$out`" 2>&1"
        Write-Host ("{0}: 运行结束，退出码 {1}" -f $case, $LASTEXITCODE)
    }
}
finally {
    Pop-Location
}
