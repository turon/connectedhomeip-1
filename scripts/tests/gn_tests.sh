#!/usr/bin/env bash

#
# Copyright (c) 2020 Project CHIP Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set -e

# Test script for GN GitHub workflow.

CHIP_ROOT="$(dirname "$0")/../.."

source "$CHIP_ROOT/scripts/activate.sh"

env

set -x

ninja -v -C "$CHIP_ROOT/out/$BUILD_TYPE" -k 0 check

if [ "x$RUN_HAPPY_TESTS" == "x1" ]; then
    unshare --map-root-user -n -m "$CHIP_ROOT/scripts/tests/happy_tests.sh" ninjarun
fi
