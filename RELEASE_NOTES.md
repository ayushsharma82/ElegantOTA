# ElegantOTA 4.0.0

A rebuilt portal, and an integrity check that finally does what it always claimed to.

Nothing in the C++ API changed. This is a drop-in upgrade — your existing sketch compiles and runs unmodified.

---

## Redesigned portal

The update page has been rebuilt from scratch around one idea: show what is actually happening to the flash.

It leads with a **capacity strip** — the target flash region drawn to scale. When you stage a `.bin`, the portal measures it against the room actually available and refuses an oversized image up front, instead of letting it fail half way through a flash. At rest the strip shows how much of the region the running build occupies.

- Drag and drop, or pick a file — with the file staged and confirmed before anything is written, rather than starting the moment it lands
- Live transfer rate and byte counts alongside the percentage
- Centred success and failure screens, with the device's own reason shown verbatim when something goes wrong
- Light and dark themes, both designed rather than inverted; follows your system setting by default
- Fully keyboard reachable, respects `prefers-reduced-motion`, and readable down to 320px
- New brand mark, drawn in the current text colour so one copy serves both themes

**The portal got smaller: 10,214 → 8,839 bytes gzipped (−13.5%)**, even though the new logo artwork is larger than the old one. Tailwind and the `md5` npm package were dropped in favour of hand-written CSS and a compact MD5 implementation.

---

## Fixes

**MD5 verification was silently doing nothing.** `/ota/start` called `Update.setMD5()` *before* `Update.begin()`, and `begin()` clears the expected digest. Every upload since this feature was added has gone unverified. The order is now correct, so a truncated or corrupted upload is rejected instead of installed.

> ⚠️ If your tooling was sending a digest that did not match the bytes it uploaded, those uploads used to succeed and will now be rejected. That is the intended behaviour, but it is a change worth knowing about before you roll this out to a fleet.

**Repeated OTA updates failed on RP2040 and RP2350.** These chips stage an
incoming image as a file inside the filesystem region, and `Update.begin()`
takes the budget the write may use. ElegantOTA was passing the space that
happened to be *free* at that moment, so once a previously staged image was
sitting in the filesystem the next update was refused for want of room:

```
ERROR[4]: Not Enough Space
```

The first update after a cold boot worked, the second did not. The budget is
now the filesystem region itself, which is the core's own limit and does not
shrink as images are staged.

These boards also reported no firmware capacity at all, so the portal could not
show how much room was left or catch an oversized image before writing it.
Both now work.

- The dropzone was a `<div>` with a click handler and could not be reached by keyboard. It is now focusable and responds to Enter and Space.
- Error messages throughout the portal and the HTTP responses were rewritten to say what went wrong and what to do about it.

---

## One new endpoint

`/ota/metadata` reports the chip family, both partition capacities, and the size of the running build. The portal needs these numbers to draw the capacity strip and to catch an oversized image before writing.

```json
{"hw":"ESP32","ar":true,"fwa":1966080,"fsa":1507328,"fwu":1210368}
```

No new configuration, and no new public methods — the library sets this up for you.

---

## Tested on

ESP32 · ESP8266 · RP2040 (Pico W) · RP2350 (Pico 2W), each with both the sync and async webservers.

📖 [Documentation](https://docs.elegantota.pro) · 🚀 [ElegantOTA Pro](https://elegantota.pro)
