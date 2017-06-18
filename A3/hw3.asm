#
# Data segment: where we declare global data
#
	.data
arr:	.word	9,6,32,67,12,5,39,44,13,8,5,14
	.eqv	asize, 12
sum:	.word	0
str1:	.asciiz "The value produced is "
endl:	.asciiz "\n"

#
# Code (text) segment
#
	.text
	.globl main
#
# main: program will start here, but MARS does not "call" main, it just starts here
#	
main: 
	ori $v0,$zero,4		# 4 means print string
	la  $a0,str1
	syscall			# on syscall
	
	jal esum
	
	ori $v0,$zero,4		# 4 means print string
	la  $a0,endl	
	syscall			# on syscall
	
	ori $v0,$zero,10  	# 10 means terminate program
	syscall			# on syscall
	
#
# Function int esum(int vals[], int size) : returns sum of even values in
# the array provided as first argument (call-by-ref), the array is of the
# size specified in the second argument (call-by-val). 
#
esum:	ori  $t0,$zero,0    	#i = 0
	ori  $t1,$zero,0   	#sum = 0
	la   $a0,asize 
	or   $t2,$zero,$a0 	#size = 12
	la   $a1,arr        	#load address of array into a1

loop:	
	slt  $t4,$t0,$t2
	beq  $t4,$zero,out
	lw   $t4,($a1)

	#Check if even or not
	andi $t5,$t4,1
	bne  $t5,0,update
	add  $t1,$t1,$t4
	j update
	
update:	addi $t0,$t0,1
	addi $a1,$a1,4
	j loop
	
out: 	
	ori $v0,$zero,1 	# 1 means print integer
	add  $a0,$t1,$zero
	syscall			# on syscall

	jr $ra			# return from function
