#!/bin/bash

if [[ -z "$EMAIL_RECEIVER" || -z "$EMAIL_SUBJECT" || -z "$EMAIL_PATH" || -z "$EMAIL_TYPE" ]]; then
    exit 1
fi

SCRIPT_DIR="$(dirname "$0")"
python3 "$SCRIPT_DIR/gmail.py" --send "$EMAIL_RECEIVER" "$EMAIL_SUBJECT" "$EMAIL_PATH"
exit $?
