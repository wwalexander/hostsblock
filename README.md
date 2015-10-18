hostsblock
==========

Converts AdBlock Plus filter lists to hosts file entries

About
-----

hostsblock finds any domain-only blocking rules in an AdBlock Plus filter list
(i.e. of the form (`||some.domain.com^`) and prints them as host file entries
for 127.0.0.1 (e.g. `127.0.0.1	some.domain.com`).

Standalone ad-blocking hosts files like http://someonewhocares.org/hosts/hosts
are good, but since ABP filter lists are far more common and frequently updated,
it's nice to have a tool to parse them.

Building
--------

    make

Usage
-----

    hostsblock [LIST]
