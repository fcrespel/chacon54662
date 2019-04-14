#!/bin/sh

SCRIPT_DIR=`dirname "$0"`

flock -w 10 "$SCRIPT_DIR/send.lock" "$SCRIPT_DIR/send" "$@"
