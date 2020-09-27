#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
    echo "ERROR: You need to run this script as root!"
    exit 1
fi

DATA_PATH="/var/lib/anbox"
CONTAINER_PATH="$DATA_PATH/containers"
CONTAINER_NAME=default

state=$(lxc-info -P "$CONTAINER_PATH" -n "$CONTAINER_NAME" -s | cut -d':' -f 2 | tr -d '[:space:]')
if [ "$state" != "RUNNING" ] ; then
    echo "ERROR: Cannot attach to container as it is not running"
    exit 1
fi

cmd=
opt=$1
if [ "$opt" = "" ]; then
    echo "no cmd!"
    exit 1
fi

if [ "$opt" = "install" ]; then
    param=$2
    if [ "$param" = "-r" ]; then
        cmd="/system/bin/pm install -r"
        param=$3
    else
        cmd="/system/bin/pm install"
    fi
    if [ -f $param ]; then
        if [ "${param##*.}" = "apk" ]; then
            cp $param $DATA_PATH/data/media/0/
            cmd="$cmd /sdcard/${param##*/}"
        else
            echo "\"$param\" file illegal"
            exit 1
        fi
    else
        echo "$param not found!"
        exit 1
    fi
elif [ "$opt" = "uninstall" ]; then
    cmd="/system/bin/pm uninstall"
    package=
    temp_opt="p"
    mm=($*)
    for (( i=1; i < $#; i++ )) 
    do
        param=${mm[$i]}
        if [ "${param:0:1}" = "-" ]; then
            for ((j=1; j<${#param}; j++)); do
                uninstall_opt=${param:j:1}
                if [ "$uninstall_opt" = "f" ]; then
                    temp_opt="f"
                elif [ "$uninstall_opt" = "p" ]; then
                    temp_opt="p"
                elif [ "$uninstall_opt" = "k" ]; then
                    cmd="$cmd -k"
                else
                    echo "\"$uninstall_opt\" unknown uninstall type"
                fi
            done
        else
            break
        fi
    done
    if [ "$param" = "" ]; then
        echo "no file or package!"
        exit 1
    fi
    if [ "$temp_opt" = "f" ]; then
        if [ -f $param ]; then
            content=`cat $param`
        else
            echo "\"$param\" file not found!"
            exit 1
        fi
        temp=${content##*--package=}
        package=${temp%% --component*}
    else
        package=$param
    fi
    cmd="$cmd $package"
elif [ "$opt" = "package-list" ]; then
    cmd="/system/bin/pm list package"
elif [ "$opt" = "package-version" ]; then
    if [ "$2" = "" ]; then
        echo "no package name"
        exit 1
    fi
    cmd="/system/bin/dumpsys package $2 | grep versionName"
elif [ "$opt" = "clean" ]; then
    if [ "$2" = "" ]; then
        echo "no package!"
        exit 1
    fi
    cmd="/system/bin/pm clear $2"
else
    echo "\"$opt\" unknown cmd!"
    exit 1
fi

#echo $cmd

info=`lxc-attach \
    -q \
    --clear-env \
    -P "$CONTAINER_PATH" \
    -n "$CONTAINER_NAME" \
    -v PATH=/sbin:/system/bin:/system/sbin:/system/xbin \
    -v ANDROID_ASSETS=/assets \
    -v ANDROID_DATA=/data \
    -v ANDROID_ROOT=/system \
    -v ANDROID_STORAGE=/storage \
    -v ASEC_MOUNTPOINT=/mnt/asec \
    -v EXTERNAL_STORAGE=/sdcard \
    -- /system/bin/sh -c "$cmd"`

#echo "$info"
if [ "$opt" = "install" ]; then
    rm $DATA_PATH/data/media/0/${param##*/}
fi

if [ "$opt" = "install" ] || [ "$opt" = "uninstall" ] || [ "$opt" = "clean" ]; then
    if [ "$info" != "Success" ]; then
        echo "$opt failed! err-msg:$info"
        exit 1
    else
        echo "$opt success"
    fi
fi

if [ "$opt" = "package-list" ]; then
    echo "$info"
fi

if [ "$opt" = "package-version" ]; then
    echo "get version, ($2, ${info##*=})"
fi

exit 0
