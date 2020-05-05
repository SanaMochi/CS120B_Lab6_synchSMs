# Test file for "Lab6_synchSMs"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below
test "Loop all of PORTB without buttons"
set state = start
setPINA 0x00
timeContinue
expect state pb0
expectPORTB 0x01
setPINA 0x00
timeContinue
expect state pb1
expectPORTB 0x02
setPINA 0x00
timeContinue
expect state pb2
expect PORTB 0x04
timeContinue
expect state pb11
expectPORTB 0x02
timeContinue
expect state pb0
expectPORTB 0x01
checkResult

test "Loop all of PORTB with button on pb1"
set state = start
setPINA 0x00
timeContinue
expect state pb0
expectPORTB 0x01
timeContinue
expect state pb1
expectPORTB 0x02
setPINA 0x01
timeContinue
expect state waitfall1
expectPORTB 0x02
setPINA 0x01
timeContinue
expect state waitfall1
expectPORTB 0x02
setPINA 0x00
timeContinue
expect state wait1
expect PORTB 0x02
setPINA 0x00
timeContinue
expect state wait1
expect PORTB 0x02
setPINA 0x01
timeContinue
expect state pb2
expectPORTB 0x04
checkResult

test "button on pb"
setPINA 0x01
timeContinue
expect state waitfall2
expect PORTB 0x04
timeContinue

checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n