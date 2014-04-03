#!/bin/sh

if [[ -z "$NACL_SDK_ROOT" ]]; then
  echo "Please set NACL_SDK_ROOT before building."
  exit 1
fi

$NACL_SDK_ROOT/toolchain/linux_x86_newlib/bin/x86_64-nacl-g++ \
handle_input.cc -I $NACL_SDK_ROOT/include/ -lppapi \
-lppapi_cpp -o handle_input.nexe
