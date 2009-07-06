	.text
	
	.set		noreorder
	.global		n64start
	.ent		n64start

n64start:

	j		ovlTest_main
	nop
	
	.end		n64start
	.set		reorder

