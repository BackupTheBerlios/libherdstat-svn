#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "pattern matching" || exit 1
indent
