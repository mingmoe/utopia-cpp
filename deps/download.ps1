
&git submodule init
&git submodule update

$prebuilt_dir = (Convert-Path $PSScriptRoot) + "/prebuilt"

# 创建prebuilt目录
if(-not(Test-Path -Path "$PSScriptRoot/prebuilt" -PathType Container)){
    New-Item -Path $prebuilt_dir -ItemType "directory"
}


if(-not(Test-Path -Path "$prebuilt_dir/icu-win.zip" -PathType Leaf)){  
    Invoke-WebRequest -Uri "https://github.com/unicode-org/icu/releases/download/release-70-1/icu4c-70_1-Win64-MSVC2019.zip" -OutFile "$prebuilt_dir/icu-win.zip"

    Expand-Archive -Path "$prebuilt_dir/icu-win.zip" -DestinationPath "$prebuilt_dir/icu-win"
}
else{
    Write-Host "skip icu-windows"
}

if(-not(Test-Path -Path "$prebuilt_dir/icu-linux.tgz" -PathType Leaf)){  
    Invoke-WebRequest -Uri "https://github.com/unicode-org/icu/releases/download/release-70-1/icu4c-70_1-Ubuntu-20.04-x64.tgz" -OutFile "$prebuilt_dir/icu-linux.tgz"

    mkdir "$prebuilt_dir/icu-linux"
    &tar -xzf "$prebuilt_dir/icu-linux.tgz" -C "$prebuilt_dir/icu-linux"
}
else{
    Write-Host "skip icu-linux"
}


if(-not(Test-Path -Path "$prebuilt_dir/sdl-win.zip" -PathType Leaf)){
    Invoke-WebRequest -Uri "https://libsdl.org/release/SDL2-devel-2.0.20-VC.zip" -OutFile "$prebuilt_dir/sdl-win.zip"
    
    Expand-Archive -Path "$prebuilt_dir/sdl-win.zip" -DestinationPath "$prebuilt_dir/sdl-win"
    
    Copy-Item "$prebuilt_dir/sdl-win/SDL2-2.0.20/*" -Destination "$prebuilt_dir/sdl-win" -Recurse -Force
}
else{
    Write-Host "skip sdl-windows"
}


if(-not(Test-Path -Path "$prebuilt_dir/freetype-win.zip" -PathType Leaf)){
    Invoke-WebRequest -Uri "https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v2.11.1.zip" -OutFile "$prebuilt_dir/freetype-win.zip"
    
    Expand-Archive -Path "$prebuilt_dir/freetype-win.zip" -DestinationPath "$prebuilt_dir/freetype-win"
    
    Copy-Item "$prebuilt_dir/freetype-win/freetype-windows-binaries-2.11.1/*" -Destination "$prebuilt_dir/freetype-win" -Recurse -Force
}
else{
    Write-Host "skip freetype-windows"
}


if(-not(Test-Path -Path "$prebuilt_dir/android.tar" -PathType Leaf)){
    Invoke-WebRequest -Uri "https://github.com/moe-org/utopia-binary/releases/download/v1.3/android.tar" -OutFile "$prebuilt_dir/android.tar"

    mkdir "$prebuilt_dir/android"
    &tar -xzf "$prebuilt_dir/android.tar" -C "$prebuilt_dir/android"
}
else{
    Write-Host "skip android"
}

if(-not(Test-Path -Path "$prebuilt_dir/windows.tar" -PathType Leaf)){
    Invoke-WebRequest -Uri "https://github.com/moe-org/utopia-binary/releases/download/v1.3/windows.zip" -OutFile "$prebuilt_dir/windows.zip"
    
    mkdir "$prebuilt_dir/windows"
    Expand-Archive -Path "$prebuilt_dir/windows.zip" -DestinationPath "$prebuilt_dir/windows"
}
else{
    Write-Host "skip windows"
}

if(-not(Test-Path -Path "$prebuilt_dir/linux.tar" -PathType Leaf)){
    Invoke-WebRequest -Uri "https://github.com/moe-org/utopia-binary/releases/download/v1.3/linux.tar" -OutFile "$prebuilt_dir/linux.tar"
    
    mkdir "$prebuilt_dir/linux"
    &tar -xzf "$prebuilt_dir/linux.tar" -C "$prebuilt_dir/linux"
}
else{
    Write-Host "skip linux"
}
