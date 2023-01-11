# Changelog

## v2.0.0

This is a breaking release! Please have a look at the new API interface.
Also feel free to open an issue if you have trouble while migrating!

- Changed interface:
  - Added `void pause()`
  - Added `void resume()`
  - Removed constructor `Timeout(unsigned long duration)`
  - Removed `void prepare(unsigned long duration)`
  - Removed `void start()` without arguments
  - Removed `bool periodic()` without arguments
- Improved tests
- Fixed rollover issues

## v1.x

- Initial release
