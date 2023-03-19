#------------------GLOBAL--------------------#
set_global_assignment -name RESERVE_ALL_UNUSED_PINS "AS INPUT TRI-STATED"
set_global_assignment -name ENABLE_INIT_DONE_OUTPUT OFF

#��λ����
set_location_assignment	PIN_25	-to RESET

#ʱ������ 50M
set_location_assignment	PIN_23	-to CLOCK 

#EPCS����
set_location_assignment	PIN_13	-to DATA0
set_location_assignment	PIN_12	-to DCLK
set_location_assignment	PIN_8	-to SCE
set_location_assignment	PIN_6	-to SDO

#SDRAM����
set_location_assignment	PIN_28	-to S_DB[0]
set_location_assignment	PIN_30	-to S_DB[1]
set_location_assignment	PIN_31 -to S_DB[2]
set_location_assignment	PIN_32	-to S_DB[3]
set_location_assignment	PIN_33	-to S_DB[4]
set_location_assignment	PIN_34	-to S_DB[5]
set_location_assignment	PIN_38	-to S_DB[6]
set_location_assignment	PIN_39	-to S_DB[7]
set_location_assignment	PIN_54	-to S_DB[8]
set_location_assignment	PIN_53  -to S_DB[9]
set_location_assignment	PIN_52	-to S_DB[10]
set_location_assignment	PIN_51	-to S_DB[11]
set_location_assignment	PIN_50	-to S_DB[12]
set_location_assignment	PIN_49	-to S_DB[13]
set_location_assignment	PIN_46	-to S_DB[14]
set_location_assignment	PIN_44	-to S_DB[15]

set_location_assignment	PIN_76	-to S_A[0]
set_location_assignment	PIN_77	-to S_A[1]
set_location_assignment	PIN_80	-to S_A[2]
set_location_assignment	PIN_83	-to S_A[3]
set_location_assignment	PIN_68	-to S_A[4]
set_location_assignment	PIN_67	-to S_A[5]
set_location_assignment	PIN_66	-to S_A[6]
set_location_assignment	PIN_65	-to S_A[7]
set_location_assignment	PIN_64	-to S_A[8]
set_location_assignment	PIN_60	-to S_A[9]
set_location_assignment	PIN_75	-to S_A[10]
set_location_assignment	PIN_59	-to S_A[11]


set_location_assignment	PIN_43	-to S_CLK
set_location_assignment	PIN_73	-to S_BA[0]
set_location_assignment	PIN_74	-to S_BA[1]
set_location_assignment	PIN_70	-to S_NCAS
set_location_assignment	PIN_58	-to S_CKE
set_location_assignment	PIN_71	-to S_NRAS
set_location_assignment	PIN_69	-to S_NWE
set_location_assignment	PIN_72	-to S_NCS
set_location_assignment	PIN_55	-to S_DQM[1]
set_location_assignment	PIN_42	-to S_DQM[0]

#VGA��Ӧ������
#VGAR[0..4]
set_location_assignment	PIN_10	-to VGAD[0]
set_location_assignment	PIN_3	-to VGAD[1]
set_location_assignment	PIN_2	-to VGAD[2]
set_location_assignment	PIN_1	-to VGAD[3]
set_location_assignment	PIN_144	-to VGAD[4]
#VGAG[0..5]
set_location_assignment	PIN_143	-to VGAD[5]
set_location_assignment	PIN_142	-to VGAD[6]
set_location_assignment	PIN_141	-to VGAD[7]
set_location_assignment	PIN_138	-to VGAD[8]
set_location_assignment	PIN_137	-to VGAD[9]
set_location_assignment	PIN_136	-to VGAD[10]
#VGAB[0..4]
set_location_assignment	PIN_135	-to VGAD[11]
set_location_assignment	PIN_133	-to VGAD[12]
set_location_assignment	PIN_132	-to VGAD[13]
set_location_assignment	PIN_129	-to VGAD[14]
set_location_assignment	PIN_128	-to VGAD[15]

set_location_assignment	PIN_11	-to VGA_HSYNC
set_location_assignment	PIN_7	-to VGA_VSYNC



#OV7670
set_location_assignment	PIN_106	-to CMOS_DB[0]
set_location_assignment	PIN_105	-to CMOS_DB[1]
set_location_assignment	PIN_104	-to CMOS_DB[2]
set_location_assignment	PIN_103	-to CMOS_DB[3]
set_location_assignment	PIN_101	-to CMOS_DB[4]
set_location_assignment	PIN_100	-to CMOS_DB[5]
set_location_assignment	PIN_99	-to CMOS_DB[6]
set_location_assignment	PIN_98	-to CMOS_DB[7]

set_location_assignment	PIN_87	-to CMOS_XCLK
set_location_assignment	PIN_90	-to CMOS_PCLK
set_location_assignment	PIN_88	-to CMOS_VSYNC
set_location_assignment	PIN_84	-to CMOS_SCLK
set_location_assignment	PIN_85	-to CMOS_SDAT
set_location_assignment	PIN_89	-to CMOS_HREF






