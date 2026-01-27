# bazel-cpp-rust-codecov

An example repository with the goal of debugging `rules_rust` support for codecov with `hermetic_cc_toolchain`.

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
- `//rust:hello` — Rust hello-world binary (`rust_binary`)

## Usage

```sh
# Build all targets
bazel build //...

# Run the C++ binary
bazel run //cpp:hello

# Run the Rust binary
bazel run //rust:hello
```
