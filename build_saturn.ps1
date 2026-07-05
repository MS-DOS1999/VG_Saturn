$ErrorActionPreference = "Stop"

$repo = Split-Path -Parent $MyInvocation.MyCommand.Path
$baseImage = "ijacquez/yaul:latest"
$assetImage = "verdict-guilty-yaul-assets:latest"
$assetDockerfile = Join-Path $repo "tools\yaul-asset-tools.Dockerfile"

$onlyClean = ($args.Count -eq 1 -and $args[0] -eq "clean")
$image = $baseImage

if (-not $onlyClean) {
    docker image inspect $assetImage *> $null
    if ($LASTEXITCODE -ne 0) {
        docker build -t $assetImage -f $assetDockerfile $repo
        if ($LASTEXITCODE -ne 0) {
            exit $LASTEXITCODE
        }
    }

    docker run --rm `
        -v "${repo}:/work" `
        -w /work `
        $assetImage `
        python3 tools/build_saturn_assets.py

    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }

    Start-Sleep -Seconds 1
    $image = $assetImage
}

docker run --rm `
    -v "${repo}:/work" `
    -w /work `
    $image `
    make $args

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
