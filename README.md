hostsblock
==========

Converts AdBlock Plus filter lists to hosts file entries

About
-----

hostsblock finds any domain-only blocking rules in an AdBlock Plus filter list
(i.e. of the form (`||some.domain.com^`, `||some.domain.com/`, or
`||some.domain.com:`), and prints them as host file entries for 127.0.0.1 (e.g.
`127.0.0.1	some.domain.com`).

Usage
-----

    hostsblock [LIST]
