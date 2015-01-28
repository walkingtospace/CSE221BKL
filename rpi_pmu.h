#ifndef RPI_PMU_H_
#define RPI_PMU_H_

#define ARMV6_EVENT_ICACHE_MISS     0x0
#define ARMV6_EVENT_IBUF_STALL      0x1
#define ARMV6_EVENT_DDEP_STALL      0x2
#define ARMV6_EVENT_ITLB_MISS       0x3
#define ARMV6_EVENT_DTLB_MISS       0x4
#define ARMV6_EVENT_BR_EXEC         0x5
#define ARMV6_EVENT_BR_MISPREDICT   0x6
#define ARMV6_EVENT_INSTR_EXEC      0x7
#define ARMV6_EVENT_DCACHE_CACCESS  0x9
#define ARMV6_EVENT_DCACHE_ACCESS   0xA
#define ARMV6_EVENT_DCACHE_MISS     0xB
#define ARMV6_EVENT_DCACHE_WBACK    0xC
#define ARMV6_EVENT_SW_PC_CHANGE    0xD
#define ARMV6_EVENT_MAIN_TLB_MISS   0xF
#define ARMV6_EVENT_EXPL_D_ACCESS   0x10
#define ARMV6_EVENT_LSU_FULL_STALL  0x11
#define ARMV6_EVENT_WBUF_DRAINED    0x12
#define ARMV6_EVENT_NOP             0x20
#define ARMV6_EVENT_CPU_CYCLES      0xFF


#define ARMV6_EVENT_CALL_EXEC       0x23
#define ARMV6_EVENT_RET_EXEC        0x24
#define ARMV6_EVENT_RET_PREDICT     0x25
#define ARMV6_EVENT_RET_MISPREDICT  0x26

#define ARMV6_PMCR_ENABLE               (1 << 0)
#define ARMV6_PMCR_CTR01_RESET          (1 << 1)
#define ARMV6_PMCR_CCOUNT_RESET         (1 << 2)
#define ARMV6_PMCR_CCOUNT_DIV           (0 << 3)
#define ARMV6_PMCR_COUNT0_IEN           (1 << 4)
#define ARMV6_PMCR_COUNT1_IEN           (1 << 5)
#define ARMV6_PMCR_CCOUNT_IEN           (1 << 6)
#define ARMV6_PMCR_COUNT0_OVERFLOW      (1 << 8)
#define ARMV6_PMCR_COUNT1_OVERFLOW      (1 << 9)
#define ARMV6_PMCR_CCOUNT_OVERFLOW      (1 << 10)
#define ARMV6_PMCR_EVT_COUNT0_SHIFT     20
#define ARMV6_PMCR_EVT_COUNT0_MASK      (0xFF << ARMV6_PMCR_EVT_COUNT0_SHIFT)
#define ARMV6_PMCR_EVT_COUNT1_SHIFT     12
#define ARMV6_PMCR_EVT_COUNT1_MASK      (0xFF << ARMV6_PMCR_EVT_COUNT1_SHIFT)

#define ARMV6_PMCR_OVERFLOWED_MASK \
	(ARMV6_PMCR_COUNT0_OVERFLOW | ARMV6_PMCR_COUNT1_OVERFLOW | \
	 ARMV6_PMCR_CCOUNT_OVERFLOW)

inline void pmcr_write(unsigned long val){
	asm volatile("mcr   p15, 0, %0, c15, c12, 0" : : "r"(val));
}
inline unsigned ccnt_read()
{
	unsigned cc;
	asm volatile ("mrc p15, 0, %0, c15, c12, 1" : "=r" (cc));
	return cc;
}

inline unsigned pmcr_read(){
	unsigned val;
	asm volatile("mrc   p15, 0, %0, c15, c12, 0" : "=r"(val));
	return val;
}

#endif
