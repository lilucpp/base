# Project Rules & Guidelines

## Build & Verification
- **Verification Requirement:** Every code change MUST be verified by performing a full build using the `build.bat` script.
- **Environment:** The build assumes a Windows environment with `vcpkg` installed.
- **Dependencies:** 
  - The project uses `vcpkg` to manage dependencies: `boost`, `zlib`, `gtest`, and `fmt`.
  - Default `VCPKG_ROOT` is `D:\vcpkg`. This can be overridden via an environment variable.

