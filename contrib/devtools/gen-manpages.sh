#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

KENFMCOIND=${KENFMCOIND:-$SRCDIR/kenfmcoind}
KENFMCOINCLI=${KENFMCOINCLI:-$SRCDIR/kenfmcoin-cli}
KENFMCOINTX=${KENFMCOINTX:-$SRCDIR/kenfmcoin-tx}
KENFMCOINQT=${KENFMCOINQT:-$SRCDIR/qt/kenfmcoin-qt}

[ ! -x $KENFMCOIND ] && echo "$KENFMCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
KENVER=($($KENFMCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for kenfmcoind if --version-string is not set,
# but has different outcomes for kenfmcoin-qt and kenfmcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$KENFMCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $KENFMCOIND $KENFMCOINCLI $KENFMCOINTX $KENFMCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${KENVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${KENVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
