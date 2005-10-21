#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "userinfo.xml parsing" \
    "${srcdir}/src/userinfo.xml-test" \
    "${TEST_DATA}/localstatedir/userinfo.xml ka0ttic" || exit 1
indent
