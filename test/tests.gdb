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

# Test 1
test "All possible paths tested & increment on 0x09"
set state = Init
timeContinue
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFE
timeContinue
expect state inc
expectPORTC 0x08
setPINA 0xFE
timeContinue
expect state waitInc
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFE
timeContinue
expect state inc
expectPORTC 0x09
setPINA 0xFF
timeContinue
expect state wait
expectPORTC 0x09
timeContinue
setPINA 0xFE
timeContinue
expect state inc
expectPORTC 0x09
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFC
timeContinue
expect state reset
expectPORTB 0x00
checkResult

# Test 2
test "PINA: 0x03 => PORTC: 0, state: wait"
set state = Init
timeContinue
setPINA 0xFC
timeContinue
#continue 5
expect state reset
expectPORTC 0x00
setPINA 0xFC
timeContinue
expect state waitReset
checkResult

# Test 3
test "PINA: 0x01 => PORTC: 8, state: waitInc"
set state = Init
timeContinue
setPINA 0xFE
timeContinue
expect state inc
expectPORTC 0x08
checkResult

# Test 4
test "PINA: 0x02 => PORTC: 6, state: waitDec"
set state = Init
timeContinue
setPINA 0xFD
timeContinue
expect state dec
expectPORTC 0x06
checkResult

# Test 5
test "Decrement on 0x00"
set state = Init
timeContinue
setPINA 0xFD
timeContinue
expectPORTC 0x06
expect state dec
setPINA 0xFD
timeContinue
expect state waitDec
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFD
timeContinue
expectPORTC 0x05
expect state dec
setPINA 0xFF
timeContinue
expect state wait
setPINA 0xFC
timeContinue
expectPORTC 0x00
expect state reset
setPINA 0xFF
timeContinue
expectPORTC 0x00
expect state wait
setPINA 0xFD
timeContinue
expectPORTC 0x00
expect state dec
#setPINA 0x00
#continue 5
#expectPORTB 0x01
#expect state waitRise1
#setPINA 0x01
#continue 5
#expectPORTB 0x02
#expect state waitFall1
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
