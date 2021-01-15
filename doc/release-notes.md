*After branching off for a major version release of Californium Core, use this
template to create the initial release notes draft.*

*The release notes draft is a temporary file that can be added to by anyone. See
[/doc/developer-notes.md#release-notes](/doc/developer-notes.md#release-notes)
for the process.*

*Create the draft, named* "*version* Release Notes Draft"
*(e.g. "0.20.0 Release Notes Draft"), as a collaborative wiki in:*

https://github.com/californium-core/californium-devwiki/wiki/

*Before the final release, move the notes back to this git repository.*

*version* Release Notes Draft
===============================

Californium Core version *version* is now available from:

  <https://californiumcore.org/bin/californium-core-*version*/>

This release includes new features, various bug fixes and performance
improvements, as well as updated translations.

Please report bugs using the issue tracker at GitHub:

  <https://github.com/californium/californium/issues>

To receive security and update notifications, please subscribe to:

  <https://californiumcore.org/en/list/announcements/join/>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes in some cases), then run the
installer (on Windows) or just copy over `/Applications/Californium-Qt` (on Mac)
or `californiumd`/`californium-qt` (on Linux).

Upgrading directly from a version of Californium Core that has reached its EOL is
possible, but it might take some time if the data directory needs to be migrated. Old
wallet versions of Californium Core are generally supported.

Compatibility
==============

Californium Core is supported and extensively tested on operating systems
using the Linux kernel, macOS 10.14+, and Windows 7 and newer.  Californium
Core should also work on most other Unix-like systems but is not as
frequently tested on them.  It is not recommended to use Californium Core on
unsupported systems.

From Californium Core 0.22.0 onwards, macOS versions earlier than 10.14 are no
longer supported. Additionally, Californium Core does not yet change appearance
when macOS "dark mode" is activated.

Notable changes
===============

P2P and network changes
-----------------------

Updated RPCs
------------
- `getpeerinfo` no longer returns the following fields: `addnode`, `banscore`,
  and `whitelisted`, which were previously deprecated in 0.21. Instead of
  `addnode`, the `connection_type` field returns manual. Instead of
  `whitelisted`, the `permissions` field indicates if the peer has special
  privileges. The `banscore` field has simply been removed. (#20755)

Changes to Wallet or GUI related RPCs can be found in the GUI or Wallet section below.

New RPCs
--------

Build System
------------

New settings
------------

Updated settings
----------------

Changes to Wallet or GUI related settings can be found in the GUI or Wallet section below.

- Passing an invalid `-rpcauth` argument now cause californiumd to fail to start.  (#20461)

Tools and Utilities
-------------------

Wallet
------

GUI changes
-----------

Low-level changes
=================

RPC
---

Tests
-----

Credits
=======

Thanks to everyone who directly contributed to this release:


As well as to everyone that helped with translations on
[Transifex](https://www.transifex.com/californium/californium/).
