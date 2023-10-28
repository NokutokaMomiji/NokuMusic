@echo OFF
echo [Compiling...]
make
echo.
echo [Copying data files for app...]
xcopy datafiles bin /E/H/C/I/Y
echo.
echo [Attempting to open program...]
cd bin
.\nokuplayer
cd ..
@echo ON