SECTIONS
{
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.text.vector_table_el2 : { *(.text.vector_table_el2) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) } 
	bss_end = .;
}