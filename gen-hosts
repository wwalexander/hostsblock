#!/bin/bash
## This script takes a list of URLs pointing to adblocker filters, hostsfiles, and domain lists.
## It then converts them into hostsfiles, and merges them together.

## If invalid input, print help.
if [[ ! -f "$1" ]]; then
	echo 'Please provide the path to a file consisting of URLs on separate lines.'
	echo 'Each URL must link to a valid adblocker blocklist.'
	echo 'You can comment out URLs by prefixing them with a hashtag.'
	echo 'You can specify URLs to hostsfiles, as well;  simply prefix them with an @ sign.'
	echo 'Domain lists can also be used -- just prefix their URLs with an ampersand.'
	exit 1
fi

## Prepare the workspace
INDIR='input'
OUTDIR='output'
rm -rf "$INDIR"  2> /dev/null
mkdir "$INDIR"
rm -rf "$OUTDIR" 2> /dev/null
mkdir "$OUTDIR"
rm -f hosts      2> /dev/null
rm -f wget.log   2> /dev/null

## Download blocklists from specified file
echo ':: Downloading blocklists...'
echo
while read L; do

	## Skip blank lines and comments
	if [[ "$L" && $(echo "$L" | egrep -v '^#') ]]; then

		## Figure out where to download to.  Non-adblock files go right to the outdir.
		if [[ $(echo "$L" | egrep '^[@|&]') ]]; then
			cd "$OUTDIR"
		else
			cd "$INDIR"
		fi

		## Download the file
		wget -nv $(echo "$L" | sed 's/^[@|&]//') 2>&1 | tee wget.log
		FILE=$(cat wget.log | sed 's/.*-> "//' | sed 's/".*//')
		rm -f wget.log

		## Process raw domain lists
		if [[ $(echo "$L" | egrep '^&') ]]; then
			rm -f "$FILE.new" 2> /dev/null
			touch "$FILE.new"
			while read DOMAIN; do
				echo "0 $DOMAIN" >> "$FILE.new"
			done < "$FILE"
			mv -f "$FILE.new" "$FILE"
		fi

		## Cleanup
		cd ..
		unset FILE
	fi
done < "$1"
echo

## Convert blocklists into hostsfiles
echo ':: Creating hostsfiles...'
for F in $(ls -1 "$INDIR"); do
	echo "$F"
	./hostsblock "$INDIR/$F" > "$OUTDIR/$F"
done
echo

## Merge hostsfiles
echo ':: Merging hostsfiles...'
for F in $(ls -1 "$OUTDIR"); do
	echo "$F"
	cat "$OUTDIR/$F" >> hosts
done
echo

## Clean up hostsfile
echo ':: Cleanup...'
cat hosts | sed 's/^.*#.*$//' | sed 's/127\.0\.0\.1/0/' | sed 's/\t/ /' | sed 's/  / /' | sort | uniq > "$OUTDIR/hosts"
rm -f hosts
mv "$OUTDIR/hosts" ./
echo

## Done
rm -rf "$INDIR" "$OUTDIR"
echo ':: Done.'
echo 'Your new hostsfile can be found at ./hosts'
echo
exit 0
