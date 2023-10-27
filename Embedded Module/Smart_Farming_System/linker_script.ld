ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 2048K
    CCM (xrw)   : ORIGIN = 0x10000000, LENGTH = 64K 
    RAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 192K
}

SECTIONS
{
    .text :
    {
        _stext = .;

        *(.isr_vectors)
        *(.text)
        *(.rodata)

        . = ALIGN(4);
        _etext = .;
    }> FLASH AT> FLASH

    .data :
    {
        _sdata = .;

        *(.data)

        . = ALIGN(4);
        _edata = .;
    }> RAM AT> FLASH

    .bss :
    {
        _sbss = .;

        *(.bss)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
    }> RAM AT> RAM
}
