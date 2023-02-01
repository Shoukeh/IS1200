  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Edited 2023 by Juris Homickis for the IS1200 course
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000	# assuming this can be changed, makes no sense otherwise
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
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
	subi $a0,$a0,1		# ms = ms - 1
	li $t0, 0		# i = 0
	li $a2, 350		# set the for loop constant. 4 works on my 5800X, while 350 is needed on the M1 Max
				# I assume this is the constant that needed to be adjusted to get this to equal 1000ms if a0 = 1000
	bgtz $a0, onems		# the actual "while". It will jump to onems if ms/a0 is larger than 0
	nop
	
	jr $ra			# return back to caller
	nop

  # converts the time from binary/hex to a ASCII string
time2string:
	move $t7,$ra		# store the return address to return to the "main loop" later on
	move $t6,$a0		# temporarily store the adress in a0 to s0 as a0 is used as the input for hexasc

	andi $a1,0xFFFF		# sanitize register a1 so that only the 4 LSB are present
	
	# convert to ASCII and load into the stack
	
	# Xx:xx
	srl $a0,$a1,12
	jal hexasc
	nop
	PUSH($v0)
	
	# xX:xx
	srl $a0,$a1,8
	jal hexasc
	nop
	PUSH($v0)
	
	# xx::xx
	li $v0,0x3A
	PUSH($v0)
	
	# xx:Xx
	srl $a0,$a1,4
	jal hexasc
	PUSH($v0)
	
	# xx:xX
	move $a0,$a1
	jal hexasc
	nop
	PUSH($v0)
	
	# NULL
	li $v0,0x00
	PUSH($v0)
	
	# unload the stack into memory
	
	move $a0,$t6		# restore address from temporary register
	
	# NULL
	POP($t0)
	sb $t0,5($a0)
	
	# xx:xX
	POP($t0)
	sb $t0,4($a0)
	
	# xx:Xx
	POP($t0)
	sb $t0,3($a0)
	
	# xx::xx
	POP($t0)
	sb $t0,2($a0)
	
	# xX:xx
	POP($t0)
	sb $t0,1($a0)
	
	# Xx:xx
	POP($t0)
	sb $t0,0($a0)
	
	move $ra,$t7		# restore return address from temporary register
	jr $ra			# jump back to caller
	nop
	
	
	
	
	
