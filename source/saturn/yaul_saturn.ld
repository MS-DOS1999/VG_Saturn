OUTPUT_FORMAT ("elf32-sh")
OUTPUT_ARCH (sh)
EXTERN (_start)
ENTRY (_start)
SEARCH_DIR ("$YAUL_INSTALL_ROOT/$YAUL_ARCH_SH_PREFIX/lib");

MEMORY {
  lowram (W) : ORIGIN = 0x00200000, LENGTH = 0x00100000
  ram (Wx)  : ORIGIN = 0x06004000, LENGTH = 0x000FC000
}

SECTIONS
{
  .text :
  {
     *(.text)
     *(.text.*)
     *(.gnu.linkonce.t.*)

     INCLUDE ldscripts/yaul-c++.x

     . = ALIGN (4);
  } > ram

  .rodata :
  {
     . = ALIGN (16);

     *(.rdata)
     *(.rodata)
     *(.rodata.*)
     *(.gnu.linkonce.r.*)
  } > ram

  .data :
  {
     . = ALIGN (16);

     *(.data)
     *(.data.*)
     *(.gnu.linkonce.d.*)
     SORT (CONSTRUCTORS)
     *(.sdata)
     *(.sdata.*)
     *(.gnu.linkonce.s.*)
  } > ram

  .bss :
  {
     . = ALIGN (16);
     PROVIDE (___bss_start = .);

     *(.bss)
     *(.bss.*)
     *(.gnu.linkonce.b.*)
     *(.sbss)
     *(.sbss.*)
     *(.gnu.linkonce.sb.*)
     *(.scommon)
     *(COMMON)

     . = ALIGN (16);
     PROVIDE (___bss_end = .);
  } > ram

  .lowram_bss (NOLOAD) :
  {
     . = ALIGN (16);
     PROVIDE (___vg_lowram_bss_start = .);

     *(.lowram_bss)
     *(.lowram_bss.*)

     . = ALIGN (16);
     PROVIDE (___vg_lowram_bss_end = .);
  } > lowram

  .uncached (0x20000000 | ___bss_end) : AT (___bss_end)
  {
     *(.uncached)
     *(.uncached.*)

     . = ALIGN (4);
  }

  ___end = ___bss_end + SIZEOF (.uncached);
}
