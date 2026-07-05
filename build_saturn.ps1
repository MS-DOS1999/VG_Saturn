$ErrorActionPreference = "Stop"

$repo = Split-Path -Parent $MyInvocation.MyCommand.Path
docker run --rm `
    -v "${repo}:/work" `
    -w /work `
    ijacquez/yaul:latest `
    make $args

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
