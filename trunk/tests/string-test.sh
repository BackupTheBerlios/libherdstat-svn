#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "string utility functions" || exit 1
indent
