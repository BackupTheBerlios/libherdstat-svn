#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "ContainerBase classes" \
    "${srcdir}/src/container_base-test" "" || exit 1
indent
