  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Edited 2023 by Juris Homickis
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"

	.global	delay
	.global	time2string
	.text
  #
  # Please add your own code below this line
  #
  # hexasc: input: $a0, output: $v0
hexasc:
	andi $a0,$a0,0xF	# bitmask. bitwise AND so that only the 4 msb are left
	addi $v0,$a0,0x30	# add 0x30 so that they line up with the ASCII codes for 0 to 9
	jr $ra			# jump back to stored address in main
	nop

  # supposedly one loop should take one ms
onems:
	addi $t0,$t0,1		# i++
	blt $t0,$a2,onems	# checks i<t1, which in this case is 4
	nop			# once i = t1, we "fall thru" to the delay subroutine

  # delay subroutine, loops as many times as a0 tells it. No outputs.
delay:
	addi $t2,$0,1		  # ms = ms - 1
 	sub $a0,$a0,$t2
	li $t0, 0		# i = 0
	li $a2, 6000		# set the for loop constant. 4 works on my 5800X, while 350 is needed on the M1 Max
				# I assume this is the constant that needed to be adjusted to get this to equal 1000ms if a0 = 1000
	bgtz $a0, onems		# the actual "while". It will jump to onems if ms/a0 is larger than 0
	nop

	jr $ra			# return back to caller
	nop

  # converts the time from binary/hex to a ASCII string
time2string:
	PUSH $s0		# store s registers in case they were used by caller
	PUSH $s1
	move $s0,$ra		# store the return address to return to the "main loop" later on
	move $s1,$a0		# temporarily store the adress in a0 to s0 as a0 is used as the input for hexasc

	andi $a1,0xFFFF		# sanitize register a1 so that only the 4 LSB are present

	# convert to ASCII and load into the stack

	# Xx:xx
	srl $a0,$a1,12
	jal hexasc
	nop
	PUSH $v0 

	# xX:xx
	srl $a0,$a1,8
	jal hexasc
	nop
	PUSH $v0 

	# xx:Xx
	srl $a0,$a1,4
	jal hexasc
	PUSH $v0

	# xx:xX
	move $a0,$a1
	jal hexasc
	nop
	PUSH $v0

	# unload the stack into memory

	move $a0,$s1		# restore address from temporary register

	# NULL
	li $v0,0x00
	sb $t0,5($a0)

	# xx:xX
	POP $t0 
	sb $t0,4($a0)

	# xx:Xx
	POP $t0 
	sb $t0,3($a0)

	# xx::xx
	li $t0,0x3A
	sb $t0,2($a0)

	# xX:xx
	POP $t0
	sb $t0,1($a0)

	# Xx:xx
	POP $t0
	sb $t0,0($a0)

	move $ra,$s0		# restore return address from temporary register
	POP $s1			# restore s registers
	POP $s0
	jr $ra			# jump back to caller
	nop
