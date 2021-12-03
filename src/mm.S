.globl memzero
memzero:
	str xzr, [x26], #8
	subs x25, x25, #8
	b.gt memzero
	ret
