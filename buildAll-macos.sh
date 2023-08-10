set echo on

echo  "\033[32mBuilding everything...\n"

# alias pushd='cd'
# alias popd='cd ..'

make

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "\033[32m\nAll assemblies built successfully.\033[0m"
