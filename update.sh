#!/bin/sh
# Copyright (c) 2025 Core Devices LLC
# SPDX-License-Identifier: Apache-2.0

set -e

SCRIPT_DIR=$(CDPATH= cd "$(dirname "$0")" && pwd)

SIFLI_SDK=${1:-}
if [ -z "$SIFLI_SDK" ]; then
	echo "Usage: $0 /path/to/SiFli_SDK"
	exit 1
fi

if [ ! -d "$SIFLI_SDK" ]; then
	echo "SDK directory not found: $SIFLI_SDK" >&2
	exit 1
fi
SIFLI_SDK=$(CDPATH= cd "$SIFLI_SDK" && pwd)
cd "$SCRIPT_DIR"

CMSIS_UTILS_SOURCE="$SCRIPT_DIR/cmsis/Include/cmsis_utils.h"
for required_path in \
	"$SIFLI_SDK/drivers/cmsis/Include" \
	"$SIFLI_SDK/drivers/cmsis/sf32lb52x" \
	"$SIFLI_SDK/drivers/cmsis/sf32lb57x" \
	"$SIFLI_SDK/external/CMSIS/Include/core_mstar.h" \
	"$CMSIS_UTILS_SOURCE"; do
	if [ ! -e "$required_path" ]; then
		echo "Missing required path: $required_path" >&2
		exit 1
	fi
done

CMSIS_UTILS_BACKUP=$(mktemp)
cp "$CMSIS_UTILS_SOURCE" "$CMSIS_UTILS_BACKUP"
trap 'rm -f "$CMSIS_UTILS_BACKUP"' 0 HUP INT TERM

rm -rf cmsis hal ipc_queue ll

# HAL drivers
mkdir -p hal
cp -r "$SIFLI_SDK/drivers/Include/." hal/include
cp -r "$SIFLI_SDK/drivers/hal/." hal/src

# Remove HAL unwanted files
rm -rf \
	hal/src/SConscript \
	hal/src/*.sym

# LL headers
mkdir -p ll/sf32lb52x
cp -r "$SIFLI_SDK/drivers/ll/sf32lb52x/." ll/sf32lb52x

# Remove LL unwanted files
rm -rf \
	ll/sf32lb52x/SConscript
 
mkdir -p ipc_queue/common ipc_queue/sf32lb52x
cp -r "$SIFLI_SDK/middleware/ipc_queue/common/." ipc_queue/common
cp "$SIFLI_SDK/middleware/ipc_queue/include/"*.h ipc_queue/common
cp -r "$SIFLI_SDK/middleware/ipc_queue/porting/sf32lb52x/hcpu/." ipc_queue/sf32lb52x
cp "$SIFLI_SDK/middleware/include/bf0_mbox_common.h" ipc_queue/common
cp "$SIFLI_SDK/middleware/include/sf_type.h" ipc_queue/common

# Remove ipc_queue unwanted files
rm -rf \
	ipc_queue/common/SConscript \
	ipc_queue/sf32lb52x/SConscript 


# CMSIS register definitions
mkdir -p cmsis/Include cmsis/sf32lb52x cmsis/sf32lb57x
cp -r "$SIFLI_SDK/drivers/cmsis/Include/." cmsis/Include
cp -r "$SIFLI_SDK/drivers/cmsis/sf32lb52x/." cmsis/sf32lb52x
find "$SIFLI_SDK/drivers/cmsis/sf32lb57x" -maxdepth 1 -type f -name '*.h' \
	-exec cp {} cmsis/sf32lb57x \;
cp "$SIFLI_SDK/middleware/bluetooth/patch/sf32lb52/"*.c cmsis/sf32lb52x
cp "$SIFLI_SDK/external/CMSIS/Include/core_mstar.h" cmsis/Include
cp "$CMSIS_UTILS_BACKUP" cmsis/Include/cmsis_utils.h

# Remove CMSIS unwanted files (including binary blobs, not allowed)
rm -rf \
	"cmsis/sf32lb52x/ad9364.h" \
	"cmsis/sf32lb52x/ble_rf_fulcal_ad9364.c" \
	"cmsis/sf32lb52x/SConscript" \
	"cmsis/sf32lb52x/lcpu_patch.c" \
	"cmsis/sf32lb52x/lcpu_patch_rev_b.c" \
	"cmsis/sf32lb52x/spi_tst_drv.c" \
	"cmsis/sf32lb52x/spi_tst_drv.h" \
	"cmsis/sf32lb52x/Templates/arm" \
	"cmsis/sf32lb52x/Templates/gcc" \
	"cmsis/sf32lb52x/Templates/iar" \

# Update revision file
SIFLI_REV=$(git -C "$SIFLI_SDK" rev-parse HEAD)
sed -i.bak "s/[a-z0-9]\{40\}/$SIFLI_REV/g" README.md
rm README.md.bak

echo "HAL updated successfully to revision $SIFLI_REV"
