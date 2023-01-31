  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,2		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	andi $a0,$a0,0xF	# bitmask. bitwise AND so that only the 4 lsb are left
	bgt $a0,9,atof		# if the input is larger than 9, call atof subroutine
	addi $v0,$a0,0x30	# add 0x30 so that they line up with the ASCII codes for 0 to 9
	jr $ra			# jump back to stored address in main

  # atof handles inputs that are A to F in hex
atof:
	addi $v0,$a0,0x37	# add 0x37 to line 10-15 up with ASCII codes for A to F
	jr $ra			# jump back to stored address in main
	


