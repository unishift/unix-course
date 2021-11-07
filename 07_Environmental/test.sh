#!/bin/sh

RHASHER=./rhasher
ALGO="${ALGO:-sha1}"

LOWER_ALGO=$(echo $ALGO | tr [:upper:] [:lower:])
UPPER_ALGO=$(echo $ALGO | tr [:lower:] [:upper:])

# Get target output
/bin/echo -n "${UPPER_ALGO} \"test_text
${UPPER_ALGO} $0
${LOWER_ALGO} \"Hello,World!" | ${RHASHER} > output_target.txt

# Get reference output
/bin/echo -n test_text | rhash -p "%x{${LOWER_ALGO}}\n" - > output_reference.txt
rhash -p "%x{${LOWER_ALGO}}\n" $0 >> output_reference.txt
/bin/echo -n "Hello,World!" | rhash -p "%B{${LOWER_ALGO}}\n" - >> output_reference.txt

# Compare outputs
diff output_target.txt output_reference.txt
RES=$?

# Clean and return
rm -f output_target.txt output_reference.txt
exit $RES
