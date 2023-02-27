
.text

	addi $a0, $0, 8		# !n
	addi $v0, $0, 1
	beq $a0, $0, stop	# skip to done if the input is 0 or 1
	beq $a0, 1, stop
	add $v0, $0, $a0
	
	addi $a2, $a0, -1
	beq $0, $0, skip
	
dec:	addi $a2, $a2, -1
skip:	beq $a2, 1, stop

	mul $v0, $v0, $a2
	beq $0, $0, dec
	
stop:	beq $0, $0, stop
	
