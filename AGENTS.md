# Repository Instructions

## Repo Overview

This repository stores Keyball keyboard sources and related workflows. It is not a standalone full QMK checkout.

- Main firmware sources live under `qmk_firmware/keyboards/keyball/`.
- This fork is intended to be used together with a separate upstream `qmk_firmware` checkout.
- Treat this repository as the place to edit Keyball sources. Treat the external QMK checkout as the place to run build and flash commands.

## Source Of Truth For QMK Version

Always verify the required QMK version from repository references before doing version-sensitive work.

- Current pinned reference: `0.22.14`
- Check `.github/workflows/build-user.yml`
- Check `.github/workflows/build-all.yml`
- Check `.github/actions/checkout-qmk_firmware/action.yml`

Do not silently bump the QMK version.

## External QMK Checkout

Before running any build or flash command, check for a sibling `qmk_firmware/` directory in the parent folder of this repository.

Typical local layout:

- this repo: `../keyball`
- external QMK checkout: `../qmk_firmware`

Required behavior:

- First check whether `../qmk_firmware` exists.
- If it does not exist, stop and report the missing directory to the user before taking any further build or flash action.
- If it exists, run build and flash commands from that external `../qmk_firmware` checkout, not from this repository.

## Repository Layout

Keyboard models live under `qmk_firmware/keyboards/keyball/`, including:

- `keyball39`
- `keyball44`
- `keyball46`
- `keyball61`
- `one47`

Common edit locations:

- `qmk_firmware/keyboards/keyball/<keyboard>/keymaps/<keymap>/keymap.c`
- `qmk_firmware/keyboards/keyball/<keyboard>/keymaps/<keymap>/config.h`
- `qmk_firmware/keyboards/keyball/<keyboard>/keymaps/<keymap>/rules.mk`
- `qmk_firmware/keyboards/keyball/<keyboard>/keymaps/<keymap>/combos.def`

Shared Keyball behavior may live outside a single keymap, especially under shared keyboard files or `qmk_firmware/keyboards/keyball/lib/`.

## How To Choose What To Edit

- If the user names a keyboard and keymap, edit only that target unless a shared change is clearly required.
- If the request affects multiple boards or shared trackball behavior, inspect shared files before duplicating changes into multiple keymaps.
- Avoid touching unrelated keymaps.
- Preserve existing behavior unless the user asks for a behavior change.

## Default Personal Target

For this fork, the default personal `keyball61` target is:

- `qmk_firmware/keyboards/keyball/keyball61/keymaps/custom_v2`

When the user asks for a `keyball61` change without naming a keymap, start there. Do not modify other `keyball61` keymaps unless the user explicitly asks.

## Build Commands

Use `make` as the primary build interface.

Run builds from the external sibling QMK checkout after confirming it exists.

Generic build form:

```sh
make SKIP_GIT=yes keyball/<keyboard>:<keymap>
```

Example for the default personal target:

```sh
make SKIP_GIT=yes keyball/keyball61:custom_v2
```

Build the exact target you changed when feasible. If a shared file changes, consider whether additional targets should be built to cover the change.

## Validation Expectations

- After code edits, build the affected target when local setup allows.
- If the requested change touches shared code, use judgment on whether multiple targets should be validated.
- If the build cannot be run because the external QMK checkout or another prerequisite is missing, report that clearly.

## Flashing

Preferred flashing path:

```sh
qmk flash
```

Safety rule:

- Never run flashing commands unless the user explicitly asks for flashing.
- Even when flashing is requested, first confirm the external `../qmk_firmware` checkout exists.

## Keyball-Specific Caution

Be careful when changing trackball-related behavior. Avoid casual changes to:

- CPI defaults and runtime CPI switching
- scroll mode behavior
- scroll divisor settings
- scroll snap settings
- EEPROM-persisted settings such as save/apply flows

Prefer minimal changes. Avoid broad refactors in keymaps or shared Keyball behavior unless the request specifically calls for them.
