/* GPLv2 (c) Airbus */
#include <debug.h>
#include <segmem.h>
#include <intr.h>

void  bp_handler()
{
    asm volatile("pusha"); 
    debug("Handled BP interruption!\n");
    asm volatile("popa");  
    asm volatile("leave");
    asm volatile("iret");  
 }

void bp_trigger()
{
    debug("Triggering BP...\n");
    asm volatile("int3");
}

void tp()
{
    idt_reg_t idtr;
    get_idtr(idtr);
    int_desc_t *tab_int_desc = idtr.desc;
    
    build_int_desc(tab_int_desc+3, gdt_krn_seg_sel(1), (offset_t)&bp_handler);
    
    bp_trigger();
}