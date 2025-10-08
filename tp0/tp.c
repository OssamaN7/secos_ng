/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

void tp() {
   debug("kernel mem [0x%p - 0x%p]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);

   multiboot_memory_map_t* entry = (multiboot_memory_map_t*)info->mbi->mmap_addr;
   while((uint32_t)entry < (info->mbi->mmap_addr + info->mbi->mmap_length)) {
      // TODO print "[start - end] type" for each entry
         const char* type_str;
         
         switch(entry->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
               type_str = "MULTIBOOT_MEMORY_AVAILABLE";
               break;
            case MULTIBOOT_MEMORY_RESERVED:
               type_str = "MULTIBOOT_MEMORY_RESERVED";
               break;
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
               type_str = "MULTIBOOT_MEMORY_ACPI_RECLAIMABLE";
               break;
            case MULTIBOOT_MEMORY_NVS:
               type_str = "MULTIBOOT_MEMORY_NVS";
               break;
            default:
               type_str = "NOOOWAAY";
               break;
         }
         
         debug("[0x%x - 0x%x] %s\n", 
               (unsigned int)entry->addr, 
               (unsigned int)(entry->addr + entry->len - 1), 
                type_str);
         
         entry++;
   }
   int *ptr_in_available_mem;
   ptr_in_available_mem = (int*)0x0;
   debug("Available mem (0x0): before: 0x%x ", *ptr_in_available_mem); // read
   *ptr_in_available_mem = 0xaaaaaaaa;                           // write
   debug("after: 0x%x\n", *ptr_in_available_mem);                // check



   int *ptr_in_reserved_mem;
   ptr_in_reserved_mem = (int*)0xf0000;
   debug("Reserved mem (at: 0xf0000):  before: 0x%x ", *ptr_in_reserved_mem); // read
   *ptr_in_reserved_mem = 0xaaaaaaaa;                           // write
   debug("after: 0x%x\n", *ptr_in_reserved_mem);    

   // lecture hors 128Mo 


   int *ptr_in_out_mem;
   ptr_in_out_mem = (int*)0xfa00000;
   debug("out mem (at: 0xf0000):  before: 0x%x ", *ptr_in_out_mem); // read
   *ptr_in_out_mem = 0xaaaaaaaa;                           // write
   debug("after: 0x%x\n", *ptr_in_out_mem);    



}
