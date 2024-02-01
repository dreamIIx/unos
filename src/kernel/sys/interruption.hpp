#pragma once

#include "./idt.h"
#include "./memory/memory.h"
#include "./io/io.h"

#define __gen_tramplin(x) static void tramplin_##x() { panic_handler(0x##x); }
#define __gen_tramplins(...) static void (*tramplins[])(void) = {__VA_ARGS__};

static void kernel_panic(char* str, int num)
{
	init_printer();
	printf(str, num);
	while (1);
}

static void panic_handler(int vector)
{    
	kernel_panic("unhandled interrupt %x", vector);
}


// AUTO-GENERATED CODE IS BELOW

__gen_tramplin(0)
__gen_tramplin(1)
__gen_tramplin(2)
__gen_tramplin(3)
__gen_tramplin(4)
__gen_tramplin(5)
__gen_tramplin(6)
__gen_tramplin(7)
__gen_tramplin(8)
__gen_tramplin(9)
__gen_tramplin(a)
__gen_tramplin(b)
__gen_tramplin(c)
__gen_tramplin(d)
__gen_tramplin(e)
__gen_tramplin(f)
__gen_tramplin(10)
__gen_tramplin(11)
__gen_tramplin(12)
__gen_tramplin(13)
__gen_tramplin(14)
__gen_tramplin(15)
__gen_tramplin(16)
__gen_tramplin(17)
__gen_tramplin(18)
__gen_tramplin(19)
__gen_tramplin(1a)
__gen_tramplin(1b)
__gen_tramplin(1c)
__gen_tramplin(1d)
__gen_tramplin(1e)
__gen_tramplin(1f)
__gen_tramplin(20)
__gen_tramplin(21)
__gen_tramplin(22)
__gen_tramplin(23)
__gen_tramplin(24)
__gen_tramplin(25)
__gen_tramplin(26)
__gen_tramplin(27)
__gen_tramplin(28)
__gen_tramplin(29)
__gen_tramplin(2a)
__gen_tramplin(2b)
__gen_tramplin(2c)
__gen_tramplin(2d)
__gen_tramplin(2e)
__gen_tramplin(2f)
__gen_tramplin(30)
__gen_tramplin(31)
__gen_tramplin(32)
__gen_tramplin(33)
__gen_tramplin(34)
__gen_tramplin(35)
__gen_tramplin(36)
__gen_tramplin(37)
__gen_tramplin(38)
__gen_tramplin(39)
__gen_tramplin(3a)
__gen_tramplin(3b)
__gen_tramplin(3c)
__gen_tramplin(3d)
__gen_tramplin(3e)
__gen_tramplin(3f)
__gen_tramplin(40)
__gen_tramplin(41)
__gen_tramplin(42)
__gen_tramplin(43)
__gen_tramplin(44)
__gen_tramplin(45)
__gen_tramplin(46)
__gen_tramplin(47)
__gen_tramplin(48)
__gen_tramplin(49)
__gen_tramplin(4a)
__gen_tramplin(4b)
__gen_tramplin(4c)
__gen_tramplin(4d)
__gen_tramplin(4e)
__gen_tramplin(4f)
__gen_tramplin(50)
__gen_tramplin(51)
__gen_tramplin(52)
__gen_tramplin(53)
__gen_tramplin(54)
__gen_tramplin(55)
__gen_tramplin(56)
__gen_tramplin(57)
__gen_tramplin(58)
__gen_tramplin(59)
__gen_tramplin(5a)
__gen_tramplin(5b)
__gen_tramplin(5c)
__gen_tramplin(5d)
__gen_tramplin(5e)
__gen_tramplin(5f)
__gen_tramplin(60)
__gen_tramplin(61)
__gen_tramplin(62)
__gen_tramplin(63)
__gen_tramplin(64)
__gen_tramplin(65)
__gen_tramplin(66)
__gen_tramplin(67)
__gen_tramplin(68)
__gen_tramplin(69)
__gen_tramplin(6a)
__gen_tramplin(6b)
__gen_tramplin(6c)
__gen_tramplin(6d)
__gen_tramplin(6e)
__gen_tramplin(6f)
__gen_tramplin(70)
__gen_tramplin(71)
__gen_tramplin(72)
__gen_tramplin(73)
__gen_tramplin(74)
__gen_tramplin(75)
__gen_tramplin(76)
__gen_tramplin(77)
__gen_tramplin(78)
__gen_tramplin(79)
__gen_tramplin(7a)
__gen_tramplin(7b)
__gen_tramplin(7c)
__gen_tramplin(7d)
__gen_tramplin(7e)
__gen_tramplin(7f)
__gen_tramplin(80)
__gen_tramplin(81)
__gen_tramplin(82)
__gen_tramplin(83)
__gen_tramplin(84)
__gen_tramplin(85)
__gen_tramplin(86)
__gen_tramplin(87)
__gen_tramplin(88)
__gen_tramplin(89)
__gen_tramplin(8a)
__gen_tramplin(8b)
__gen_tramplin(8c)
__gen_tramplin(8d)
__gen_tramplin(8e)
__gen_tramplin(8f)
__gen_tramplin(90)
__gen_tramplin(91)
__gen_tramplin(92)
__gen_tramplin(93)
__gen_tramplin(94)
__gen_tramplin(95)
__gen_tramplin(96)
__gen_tramplin(97)
__gen_tramplin(98)
__gen_tramplin(99)
__gen_tramplin(9a)
__gen_tramplin(9b)
__gen_tramplin(9c)
__gen_tramplin(9d)
__gen_tramplin(9e)
__gen_tramplin(9f)
__gen_tramplin(a0)
__gen_tramplin(a1)
__gen_tramplin(a2)
__gen_tramplin(a3)
__gen_tramplin(a4)
__gen_tramplin(a5)
__gen_tramplin(a6)
__gen_tramplin(a7)
__gen_tramplin(a8)
__gen_tramplin(a9)
__gen_tramplin(aa)
__gen_tramplin(ab)
__gen_tramplin(ac)
__gen_tramplin(ad)
__gen_tramplin(ae)
__gen_tramplin(af)
__gen_tramplin(b0)
__gen_tramplin(b1)
__gen_tramplin(b2)
__gen_tramplin(b3)
__gen_tramplin(b4)
__gen_tramplin(b5)
__gen_tramplin(b6)
__gen_tramplin(b7)
__gen_tramplin(b8)
__gen_tramplin(b9)
__gen_tramplin(ba)
__gen_tramplin(bb)
__gen_tramplin(bc)
__gen_tramplin(bd)
__gen_tramplin(be)
__gen_tramplin(bf)
__gen_tramplin(c0)
__gen_tramplin(c1)
__gen_tramplin(c2)
__gen_tramplin(c3)
__gen_tramplin(c4)
__gen_tramplin(c5)
__gen_tramplin(c6)
__gen_tramplin(c7)
__gen_tramplin(c8)
__gen_tramplin(c9)
__gen_tramplin(ca)
__gen_tramplin(cb)
__gen_tramplin(cc)
__gen_tramplin(cd)
__gen_tramplin(ce)
__gen_tramplin(cf)
__gen_tramplin(d0)
__gen_tramplin(d1)
__gen_tramplin(d2)
__gen_tramplin(d3)
__gen_tramplin(d4)
__gen_tramplin(d5)
__gen_tramplin(d6)
__gen_tramplin(d7)
__gen_tramplin(d8)
__gen_tramplin(d9)
__gen_tramplin(da)
__gen_tramplin(db)
__gen_tramplin(dc)
__gen_tramplin(dd)
__gen_tramplin(de)
__gen_tramplin(df)
__gen_tramplin(e0)
__gen_tramplin(e1)
__gen_tramplin(e2)
__gen_tramplin(e3)
__gen_tramplin(e4)
__gen_tramplin(e5)
__gen_tramplin(e6)
__gen_tramplin(e7)
__gen_tramplin(e8)
__gen_tramplin(e9)
__gen_tramplin(ea)
__gen_tramplin(eb)
__gen_tramplin(ec)
__gen_tramplin(ed)
__gen_tramplin(ee)
__gen_tramplin(ef)
__gen_tramplin(f0)
__gen_tramplin(f1)
__gen_tramplin(f2)
__gen_tramplin(f3)
__gen_tramplin(f4)
__gen_tramplin(f5)
__gen_tramplin(f6)
__gen_tramplin(f7)
__gen_tramplin(f8)
__gen_tramplin(f9)
__gen_tramplin(fa)
__gen_tramplin(fb)
__gen_tramplin(fc)
__gen_tramplin(fd)
__gen_tramplin(fe)
__gen_tramplin(ff)
__gen_tramplins(tramplin_0, tramplin_1, tramplin_2, tramplin_3, tramplin_4, tramplin_5, tramplin_6, tramplin_7,
					tramplin_8, tramplin_9, tramplin_a, tramplin_b, tramplin_c, tramplin_d, tramplin_e, tramplin_f,
					tramplin_10, tramplin_11, tramplin_12, tramplin_13, tramplin_14, tramplin_15, tramplin_16, tramplin_17,
					tramplin_18, tramplin_19, tramplin_1a, tramplin_1b, tramplin_1c, tramplin_1d, tramplin_1e, tramplin_1f,
					tramplin_20, tramplin_21, tramplin_22, tramplin_23, tramplin_24, tramplin_25, tramplin_26, tramplin_27,
					tramplin_28, tramplin_29, tramplin_2a, tramplin_2b, tramplin_2c, tramplin_2d, tramplin_2e, tramplin_2f,
					tramplin_30, tramplin_31, tramplin_32, tramplin_33, tramplin_34, tramplin_35, tramplin_36, tramplin_37,
					tramplin_38, tramplin_39, tramplin_3a, tramplin_3b, tramplin_3c, tramplin_3d, tramplin_3e, tramplin_3f,
					tramplin_40, tramplin_41, tramplin_42, tramplin_43, tramplin_44, tramplin_45, tramplin_46, tramplin_47,
					tramplin_48, tramplin_49, tramplin_4a, tramplin_4b, tramplin_4c, tramplin_4d, tramplin_4e, tramplin_4f,
					tramplin_50, tramplin_51, tramplin_52, tramplin_53, tramplin_54, tramplin_55, tramplin_56, tramplin_57,
					tramplin_58, tramplin_59, tramplin_5a, tramplin_5b, tramplin_5c, tramplin_5d, tramplin_5e, tramplin_5f,
					tramplin_60, tramplin_61, tramplin_62, tramplin_63, tramplin_64, tramplin_65, tramplin_66, tramplin_67,
					tramplin_68, tramplin_69, tramplin_6a, tramplin_6b, tramplin_6c, tramplin_6d, tramplin_6e, tramplin_6f,
					tramplin_70, tramplin_71, tramplin_72, tramplin_73, tramplin_74, tramplin_75, tramplin_76, tramplin_77,
					tramplin_78, tramplin_79, tramplin_7a, tramplin_7b, tramplin_7c, tramplin_7d, tramplin_7e, tramplin_7f,
					tramplin_80, tramplin_81, tramplin_82, tramplin_83, tramplin_84, tramplin_85, tramplin_86, tramplin_87,
					tramplin_88, tramplin_89, tramplin_8a, tramplin_8b, tramplin_8c, tramplin_8d, tramplin_8e, tramplin_8f,
					tramplin_90, tramplin_91, tramplin_92, tramplin_93, tramplin_94, tramplin_95, tramplin_96, tramplin_97,
					tramplin_98, tramplin_99, tramplin_9a, tramplin_9b, tramplin_9c, tramplin_9d, tramplin_9e, tramplin_9f,
					tramplin_a0, tramplin_a1, tramplin_a2, tramplin_a3, tramplin_a4, tramplin_a5, tramplin_a6, tramplin_a7,
					tramplin_a8, tramplin_a9, tramplin_aa, tramplin_ab, tramplin_ac, tramplin_ad, tramplin_ae, tramplin_af,
					tramplin_b0, tramplin_b1, tramplin_b2, tramplin_b3, tramplin_b4, tramplin_b5, tramplin_b6, tramplin_b7,
					tramplin_b8, tramplin_b9, tramplin_ba, tramplin_bb, tramplin_bc, tramplin_bd, tramplin_be, tramplin_bf,
					tramplin_c0, tramplin_c1, tramplin_c2, tramplin_c3, tramplin_c4, tramplin_c5, tramplin_c6, tramplin_c7,
					tramplin_c8, tramplin_c9, tramplin_ca, tramplin_cb, tramplin_cc, tramplin_cd, tramplin_ce, tramplin_cf,
					tramplin_d0, tramplin_d1, tramplin_d2, tramplin_d3, tramplin_d4, tramplin_d5, tramplin_d6, tramplin_d7,
					tramplin_d8, tramplin_d9, tramplin_da, tramplin_db, tramplin_dc, tramplin_dd, tramplin_de, tramplin_df,
					tramplin_e0, tramplin_e1, tramplin_e2, tramplin_e3, tramplin_e4, tramplin_e5, tramplin_e6, tramplin_e7,
					tramplin_e8, tramplin_e9, tramplin_ea, tramplin_eb, tramplin_ec, tramplin_ed, tramplin_ee, tramplin_ef,
					tramplin_f0, tramplin_f1, tramplin_f2, tramplin_f3, tramplin_f4, tramplin_f5, tramplin_f6, tramplin_f7,
					tramplin_f8, tramplin_f9, tramplin_fa, tramplin_fb, tramplin_fc, tramplin_fd, tramplin_fe, tramplin_ff)

#pragma pack(push, 1)
typedef struct {
	uint16_t IDT_size;
	uint32_t linear_addr_IDT;
} IDTD;
#pragma pack(pop)

void register_handlers()
{
	InterruptDescriptor32* idt = kernel_calloc(sizeof(InterruptDescriptor32), 256);

    for (int i = 0; i < 256; ++i)
    {
		idt[i].offset_1 = (uint16_t) tramplins[i];  // lower bits
		idt[i].offset_2 = (uint16_t) (((uint32_t) tramplins[i]) >> 16);  // upper bits
		idt[i].type_attributes = 0b10001110;
		idt[i].selector = 0b1000;
    }

	IDTD idtd;
	idtd.IDT_size = sizeof(InterruptDescriptor32) * 256 - 1;
	idtd.linear_addr_IDT = idt;

	asm("lidt %0" :: "m"(idtd));
}
