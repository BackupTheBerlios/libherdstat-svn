#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "userinfo.xml parsing" \
    "${TEST_DATA}/localstatedir/userinfo.xml ka0ttic" || exit 1
indent
