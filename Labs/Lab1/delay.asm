	.text
main:
	li $a0,0x31
	li $v0,11
	syscall
	
	li $a0, 1000
	jal delay
	nop
	
	li $a0,0x32
	li $v0,11
	syscall
	
	j stop

  # supposedly one loop should take one ms
onems:
	addi $t0,$t0,1		# i++
	blt $t0,$t1,onems	# checks i<t1, which in this case is 4
	nop			# once i = t1, we "fall thru" to the delay subroutine
	
  # delay subroutine, loops as many times as a0 tells it. No outputs.
delay:
	subi $a0,$a0,1		# ms = ms - 1
	li $t0, 0		# i = 0
	li $t1, 4		# set the for loop constant
				# I assume this is the constant that needed to be adjusted to get this to equal 1000ms if a0 = 1000
	bgtz $a0, onems		# the actual "while". It will jump to onems if ms/a0 is larger than 0
	nop
	
	jr $ra			# return back to caller

stop:


	
	

	
	
	