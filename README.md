# bazel-cpp-rust-codecov

Minimal reproduction of a **Rust code coverage failure** when using
[`rules_rust`](https://github.com/bazelbuild/rules_rust) with
[`hermetic_cc_toolchain`](https://github.com/uber/hermetic_cc_toolchain) (Zig-based).

C++ coverage works, but `bazel coverage` on a `rust_test` target fails at link
time because the Zig linker cannot find `__llvm_profile_runtime`:

```
ld.lld: error: cannot open __llvm_profile_runtime: No such file or directory
```

## Reproducing

Open this repo in a **GitHub Codespace** (devcontainer includes bazelisk), then:

```sh
bazel coverage //...
```

C++ passes. Rust fails:

```
//cpp:greeter_test    PASSED in 0.9s
//rust:greeter_test   FAILED TO BUILD
```

<details>
<summary>Full Rust linker error</summary>

```
error: linking with `external/hermetic_cc_toolchain~~toolchains~zig_config/tools/x86_64-linux-gnu.2.17/c++` failed: exit status: 1
  |
  = note: ld.lld: error: cannot open __llvm_profile_runtime: No such file or directory
```

The linker is invoked with `-u __llvm_profile_runtime` and
`-fprofile-instr-generate`, but the Zig/Clang toolchain bundled by
`hermetic_cc_toolchain` does not ship the LLVM profiling runtime library
(`libclang_rt.profile`), so the link fails.

</details>

## Toolchain Versions

| Tool | Version |
|------|---------|
| Bazel | 7.6.0 |
| hermetic_cc_toolchain | 4.1.0 |
| rules_rust | 0.68.1 |
| Rust edition | 2021 |
| Rust toolchain | 1.85.0 |

## Build Targets

- `//cpp:hello` — C++ hello-world binary (`cc_binary`)
- `//cpp:greeter_test` — C++ test (`cc_test`)
- `//rust:hello` — Rust hello-world binary (`rust_binary`)
- `//rust:greeter_test` — Rust test (`rust_test`)

## Usage

```sh
# Build all targets
bazel build //...

# Run tests (no coverage)
bazel test //...

# Run coverage (reproduces the Rust failure)
bazel coverage //...
```
