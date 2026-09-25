param(
    [Parameter(Mandatory = $true)][string]$ExePath,
    [Parameter(Mandatory = $true)][string]$WorkingDirectory
)

$command = 'chcp 65001 > nul && "' + $ExePath + '"'
Start-Process -FilePath $env:ComSpec -WorkingDirectory $WorkingDirectory -ArgumentList @('/k', $command) -WindowStyle Normal
