#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "PackageList class" || exit 1
indent
