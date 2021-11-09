.globl memzero
memzero:
	str xzr, [x4], #8
	subs x1, x1, #8
	b.gt memzero
	ret
