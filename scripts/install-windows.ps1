$src = $PSCommandPath
$src = $src[0..$src.LastIndexOf('\')] -join ''
$src += "..\src"

$dest = "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\dot_lib"

if ($args[0]) {
	$dest = $args[0]
}
#$dest = "E:\vedqiibyol\Programming\.libs\dot_lib"

echo "Copying: $src -> $dest"
Copy-Item -path $src -Destination $dest -Recurse -Force



