hostsblock
==========

Converts AdBlock Plus filter lists to hosts file entries

About
-----

hostsblock finds any domain-only blocking rules in an AdBlock Plus filter list
(e.g. of the form `||some.domain.com^`) and prints them as host file entries
for 127.0.0.1 (e.g. `127.0.0.1	some.domain.com`).

Standalone ad-blocking hosts files like http://someonewhocares.org/hosts/hosts
are good, but since ABP filter lists are far more common and frequently updated,
it's nice to have a tool to parse them.

Building
--------

    make

Usage
-----

    hostsblock file

If the file argument is `-` or omitted, hostsblock will read from stdin. For
example,

    curl -s https://www.fanboy.co.nz/r/fanboy-ultimate.txt | hostsblock -

If you had your original hosts file at /etc/hosts~, you could fetch an AdBlock
list, read the hosts file entries from it with hostsblock, and concatenate the
original hosts file with the ad-blocking entries to create the actual hosts
file:

    curl -s https://www.fanboy.co.nz/r/fanboy-ultimate.txt |
    hostsblock |
    cat /etc/hosts~ - > /etc/hosts

Copyright
---------

hostsblock is Copyright (C) from 2016 by William Alexander per the GNU General Public License v3.

gen-hosts
=========

This script takes a list of URLs pointing to adblocker filters, hostsfiles, and domain lists.
It then converts them into hostsfiles, and merges them together.
The final result is located at `./hosts`.
It functions as a wrapper for hostsblock, and is useful for doing batch operations.
You could run this script daily, for example, to ensure that your hosts file is always up-to-date.

Usage
-----

    gen-hosts file.list

Configuration
-------------

gen-hosts requires a textfile containing the URLs to blocklists.
This textfile should have one entry per line.
Blank lines are ignored.
Comments are prefixed by '#'.
Hostsfiles are prefixed by '@'.
Domain lists are prefixed by '&'.
All other lines are assumed to be adblock filters.

Copyright
---------

gen-hosts is Copyright (C) from 2018 by Miles Huff per GNU General Public License v3.
