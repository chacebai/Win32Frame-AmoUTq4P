@echo off
chcp 65001
:: 设置CMake生成目录和编译目录
set build_dir=build
:: 替换为你生成的可执行文件的名称
set exe_name=Win32Frame\\Debug\\Win32Frame.exe

:: 如果生成目录不存在，则创建它
if not exist %build_dir% (
    mkdir %build_dir%
)

:: 进入生成目录
cd %build_dir%

:: 运行CMake生成步骤（假设源代码在上一级目录）
cmake ..

:: 检查CMake是否成功
if %errorlevel% neq 0 (
    echo CMake 生成失败!
    exit /b %errorlevel%
)

:: 开始编译
cmake --build . --config Debug

:: 检查编译是否成功
if %errorlevel% neq 0 (
    echo 编译失败!
    exit /b %errorlevel%
)

:: 检查是否生成了exe文件
if not exist %exe_name% (
    echo %exe_name% 文件未找到, 可能编译失败!
    exit /b 1
)

echo 编译成功!

:: 运行生成的exe程序
echo 运行程序 %exe_name%
%exe_name%



