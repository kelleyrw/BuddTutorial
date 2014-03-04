#!/bin/bash

# get the project dir
tools_dir=$(cd -P "$(dirname "${BASH_SOURCE[0]}")" && pwd)
project_dir=$(cd -P $tools_dir/.. && pwd)

# host name of the computer
export HOSTNAME=`hostname`

# setup boost (if its not already setup)
if [ -z $BOOST_CURRENT ]; then
    export BOOST_CURRENT=/usr/local/boost/1.49.0
    export BOOST_BUILD_PATH=$BOOST_CURRENT/tools/build/v2
    export PATH=$PATH:$BOOST_BUILD_PATH
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BOOST_CURRENT/stage/lib
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$BOOST_CURRENT/stage/lib
    alias bjamr='bjam variant=release address-model=64 architecture=ia64 threading=multi'
    alias bjamd='bjam variant=debug address-model=64 architecture=ia64 threading=multi'
    alias bjamr32='bjamr address-model=32 architecture=x86'
    alias bjamd32='bjamd address-model=32 architecture=x86'
fi

# set the path and setup shared libraries
export BUDD=$project_dir
alias cdbudd="cd $BUDD"

LD_LIBRARY_PATH=$project_dir/bin/release:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$project_dir/bin/release:$DYLD_LIBRARY_PATH
# LD_LIBRARY_PATH=$project_dir/bin/debug:$LD_LIBRARY_PATH
# DYLD_LIBRARY_PATH=$project_dir/bin/debug:$DYLD_LIBRARY_PATH
PATH=$PATH:$BUDD/bin/release

