@echo off
title rename for visual studio(pap)
color 02
cls
echo select your need change model.
echo (1)all (2)gateway
set /p select=your select?
echo revert to standard?
set revert=-1
set /p revert=(yes/no)?
set all="billing sharememory login world server"
if 1 == %select% echo "php ../php/vcbuild.php" %all% %revert%
if 2 == %select% php ../php/vcbuild.php "gateway" %revert%

pause