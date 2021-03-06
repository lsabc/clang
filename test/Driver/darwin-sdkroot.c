// Check that SDKROOT is used to define the default for -isysroot on Darwin.
//
// RUN: rm -rf %t.tmpdir
// RUN: mkdir -p %t.tmpdir
// RUN: env SDKROOT=%t.tmpdir %clang -target x86_64-apple-darwin10 \
// RUN:   -c %s -### 2> %t.log
// RUN: FileCheck --check-prefix=CHECK-BASIC < %t.log %s
//
// CHECK-BASIC: clang
// CHECK-BASIC: "-cc1"
// CHECK-BASIC: "-isysroot" "{{.*tmpdir}}"

// Check that we don't use SDKROOT as the default if it is not a valid path.
//
// RUN: rm -rf %t.nonpath
// RUN: env SDKROOT=%t.nonpath %clang -target x86_64-apple-darwin10 \
// RUN:   -c %s -### 2> %t.log
// RUN: FileCheck --check-prefix=CHECK-NONPATH < %t.log %s
//
// CHECK-NONPATH: clang
// CHECK-NONPATH: "-cc1"
// CHECK-NONPATH-NOT: "-isysroot"

// Check that we don't use SDKROOT as the default if it is just "/"
//
// RUN: env SDKROOT=/ %clang -target x86_64-apple-darwin10 \
// RUN:   -c %s -### 2> %t.log
// RUN: FileCheck --check-prefix=CHECK-NONROOT < %t.log %s
//
// CHECK-NONROOT: clang
// CHECK-NONROOT: "-cc1"
// CHECK-NONROOT-NOT: "-isysroot"
//
// It doesn't make sense on msys bash.
// REQUIRES: shell-preserves-root
// Even running under cmd.exe and not the msys shell, the msys 1.0 env
// command will *not* preserve root, expanding / into C:/MINGW/MSYS/1.0.
// To see, from the command prompt of cmd.exe run:
//   env SDKROOT=/ cmd //c echo %SDKROOT%
// To be sure we have real env program from a real shell and not the MSYS one:
// REQUIRES: shell
