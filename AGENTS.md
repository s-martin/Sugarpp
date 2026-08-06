# AGENTS.md

## Repository overview
- `Sugarpp` is a small C++17 utility library built with CMake.
- Main library headers live in `/home/runner/work/Sugarpp/Sugarpp/include`.
- Library sources live in `/home/runner/work/Sugarpp/Sugarpp/src`.
- Unit tests live in `/home/runner/work/Sugarpp/Sugarpp/test`.
- Test fixtures live in `/home/runner/work/Sugarpp/Sugarpp/test-data`.
- Doxygen configuration lives in `/home/runner/work/Sugarpp/Sugarpp/doc`.

## Build and test
- Configure: `cmake . -B build`
- Build: `cmake --build build`
- Run tests via CTest: `ctest --test-dir build --output-on-failure`
- The test binary target is `Sugar++Test`.
- Doxygen is enabled by default; use `-DBUILD_DOC=OFF` if documentation tooling is unavailable.

## Dependencies
- Required libraries: Boost (`log`, `log_setup`, `unit_test_framework`) and Xerces-C.
- Linux CI installs `libboost-test-dev`, `libboost-log-dev`, `libxerces-c-dev`, `lcov`, `gcovr`, `doxygen`, `graphviz`, `mscgen`, and `dia`.
- Windows builds are supported and include Windows-specific code guarded by platform checks.

## Editing guidance
- Keep changes small and localized.
- Preserve the existing CMake-based layout and target names.
- Use C++17-compatible changes only.
- When changing tests, keep file paths relative to the repository root because tests run with the source directory as the working directory.
- Avoid changing generated-documentation or coverage behavior unless the task requires it.

## Validation expectations
- For code changes, at minimum rebuild and run the relevant tests.
- For documentation-only changes, verify file placement and content.
