
.text

	addi $a0, $0, 11		# !n
	addi $v0, $0, 1		# set starting output value
	beq $a0, $0, stop	# skip to done if the input is 0 or 1
	beq $a0, 1, stop
	add $v0, $0, $0		# reset v0
	
	add $v0, $0, $a0
	addi $a2, $a0, -1
	beq $0, $0, skip
	
dec:	addi $a2, $a2, -1
skip:	beq $a2, 1, stop
	add $a3, $0, $0
	add $a3, $a2, $0
	add $a0, $v0, $0

mlt:	add $v0, $v0, $a0
	addi $a3, $a3, -1
	beq $a3, 1, dec
	beq $0, $0, mlt
	
stop:	beq $0, $0, stop
	