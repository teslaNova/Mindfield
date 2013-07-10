#ifndef X86_GATES_H_
#define X86_GATES_H_

#define DEF_INT_GATE(snum, num) __asm__ ("_int_gate" snum ": pusha; popa; hlt;");

DEF_INT_GATE("0", 0);
DEF_INT_GATE("1", 1);
DEF_INT_GATE("2", 2);
DEF_INT_GATE("3", 3);
DEF_INT_GATE("4", 4);
DEF_INT_GATE("5", 5);
DEF_INT_GATE("6", 6);
DEF_INT_GATE("7", 7);
DEF_INT_GATE("8", 8);
DEF_INT_GATE("9", 9);
DEF_INT_GATE("10", 10);
DEF_INT_GATE("11", 11);
DEF_INT_GATE("12", 12);
DEF_INT_GATE("13", 13);
DEF_INT_GATE("14", 14);
DEF_INT_GATE("15", 15);
DEF_INT_GATE("16", 16);
DEF_INT_GATE("17", 17);
DEF_INT_GATE("18", 18);
DEF_INT_GATE("19", 19);
DEF_INT_GATE("20", 20);
DEF_INT_GATE("21", 21);
DEF_INT_GATE("22", 22);
DEF_INT_GATE("23", 23);
DEF_INT_GATE("24", 24);
DEF_INT_GATE("25", 25);
DEF_INT_GATE("26", 26);
DEF_INT_GATE("27", 27);
DEF_INT_GATE("28", 28);
DEF_INT_GATE("29", 29);
DEF_INT_GATE("30", 30);
DEF_INT_GATE("31", 31);
DEF_INT_GATE("32", 32);
DEF_INT_GATE("33", 33);
DEF_INT_GATE("34", 34);
DEF_INT_GATE("35", 35);
DEF_INT_GATE("36", 36);
DEF_INT_GATE("37", 37);
DEF_INT_GATE("38", 38);
DEF_INT_GATE("39", 39);
DEF_INT_GATE("40", 40);
DEF_INT_GATE("41", 41);
DEF_INT_GATE("42", 42);
DEF_INT_GATE("43", 43);
DEF_INT_GATE("44", 44);
DEF_INT_GATE("45", 45);
DEF_INT_GATE("46", 46);
DEF_INT_GATE("47", 47);
DEF_INT_GATE("48", 48);
DEF_INT_GATE("49", 49);
DEF_INT_GATE("50", 50);
DEF_INT_GATE("51", 51);
DEF_INT_GATE("52", 52);
DEF_INT_GATE("53", 53);
DEF_INT_GATE("54", 54);
DEF_INT_GATE("55", 55);
DEF_INT_GATE("56", 56);
DEF_INT_GATE("57", 57);
DEF_INT_GATE("58", 58);
DEF_INT_GATE("59", 59);
DEF_INT_GATE("60", 60);
DEF_INT_GATE("61", 61);
DEF_INT_GATE("62", 62);
DEF_INT_GATE("63", 63);
DEF_INT_GATE("64", 64);
DEF_INT_GATE("65", 65);
DEF_INT_GATE("66", 66);
DEF_INT_GATE("67", 67);
DEF_INT_GATE("68", 68);
DEF_INT_GATE("69", 69);
DEF_INT_GATE("70", 70);
DEF_INT_GATE("71", 71);
DEF_INT_GATE("72", 72);
DEF_INT_GATE("73", 73);
DEF_INT_GATE("74", 74);
DEF_INT_GATE("75", 75);
DEF_INT_GATE("76", 76);
DEF_INT_GATE("77", 77);
DEF_INT_GATE("78", 78);
DEF_INT_GATE("79", 79);
DEF_INT_GATE("80", 80);
DEF_INT_GATE("81", 81);
DEF_INT_GATE("82", 82);
DEF_INT_GATE("83", 83);
DEF_INT_GATE("84", 84);
DEF_INT_GATE("85", 85);
DEF_INT_GATE("86", 86);
DEF_INT_GATE("87", 87);
DEF_INT_GATE("88", 88);
DEF_INT_GATE("89", 89);
DEF_INT_GATE("90", 90);
DEF_INT_GATE("91", 91);
DEF_INT_GATE("92", 92);
DEF_INT_GATE("93", 93);
DEF_INT_GATE("94", 94);
DEF_INT_GATE("95", 95);
DEF_INT_GATE("96", 96);
DEF_INT_GATE("97", 97);
DEF_INT_GATE("98", 98);
DEF_INT_GATE("99", 99);
DEF_INT_GATE("100", 100);
DEF_INT_GATE("101", 101);
DEF_INT_GATE("102", 102);
DEF_INT_GATE("103", 103);
DEF_INT_GATE("104", 104);
DEF_INT_GATE("105", 105);
DEF_INT_GATE("106", 106);
DEF_INT_GATE("107", 107);
DEF_INT_GATE("108", 108);
DEF_INT_GATE("109", 109);
DEF_INT_GATE("110", 110);
DEF_INT_GATE("111", 111);
DEF_INT_GATE("112", 112);
DEF_INT_GATE("113", 113);
DEF_INT_GATE("114", 114);
DEF_INT_GATE("115", 115);
DEF_INT_GATE("116", 116);
DEF_INT_GATE("117", 117);
DEF_INT_GATE("118", 118);
DEF_INT_GATE("119", 119);
DEF_INT_GATE("120", 120);
DEF_INT_GATE("121", 121);
DEF_INT_GATE("122", 122);
DEF_INT_GATE("123", 123);
DEF_INT_GATE("124", 124);
DEF_INT_GATE("125", 125);
DEF_INT_GATE("126", 126);
DEF_INT_GATE("127", 127);
DEF_INT_GATE("128", 128);
DEF_INT_GATE("129", 129);
DEF_INT_GATE("130", 130);
DEF_INT_GATE("131", 131);
DEF_INT_GATE("132", 132);
DEF_INT_GATE("133", 133);
DEF_INT_GATE("134", 134);
DEF_INT_GATE("135", 135);
DEF_INT_GATE("136", 136);
DEF_INT_GATE("137", 137);
DEF_INT_GATE("138", 138);
DEF_INT_GATE("139", 139);
DEF_INT_GATE("140", 140);
DEF_INT_GATE("141", 141);
DEF_INT_GATE("142", 142);
DEF_INT_GATE("143", 143);
DEF_INT_GATE("144", 144);
DEF_INT_GATE("145", 145);
DEF_INT_GATE("146", 146);
DEF_INT_GATE("147", 147);
DEF_INT_GATE("148", 148);
DEF_INT_GATE("149", 149);
DEF_INT_GATE("150", 150);
DEF_INT_GATE("151", 151);
DEF_INT_GATE("152", 152);
DEF_INT_GATE("153", 153);
DEF_INT_GATE("154", 154);
DEF_INT_GATE("155", 155);
DEF_INT_GATE("156", 156);
DEF_INT_GATE("157", 157);
DEF_INT_GATE("158", 158);
DEF_INT_GATE("159", 159);
DEF_INT_GATE("160", 160);
DEF_INT_GATE("161", 161);
DEF_INT_GATE("162", 162);
DEF_INT_GATE("163", 163);
DEF_INT_GATE("164", 164);
DEF_INT_GATE("165", 165);
DEF_INT_GATE("166", 166);
DEF_INT_GATE("167", 167);
DEF_INT_GATE("168", 168);
DEF_INT_GATE("169", 169);
DEF_INT_GATE("170", 170);
DEF_INT_GATE("171", 171);
DEF_INT_GATE("172", 172);
DEF_INT_GATE("173", 173);
DEF_INT_GATE("174", 174);
DEF_INT_GATE("175", 175);
DEF_INT_GATE("176", 176);
DEF_INT_GATE("177", 177);
DEF_INT_GATE("178", 178);
DEF_INT_GATE("179", 179);
DEF_INT_GATE("180", 180);
DEF_INT_GATE("181", 181);
DEF_INT_GATE("182", 182);
DEF_INT_GATE("183", 183);
DEF_INT_GATE("184", 184);
DEF_INT_GATE("185", 185);
DEF_INT_GATE("186", 186);
DEF_INT_GATE("187", 187);
DEF_INT_GATE("188", 188);
DEF_INT_GATE("189", 189);
DEF_INT_GATE("190", 190);
DEF_INT_GATE("191", 191);
DEF_INT_GATE("192", 192);
DEF_INT_GATE("193", 193);
DEF_INT_GATE("194", 194);
DEF_INT_GATE("195", 195);
DEF_INT_GATE("196", 196);
DEF_INT_GATE("197", 197);
DEF_INT_GATE("198", 198);
DEF_INT_GATE("199", 199);
DEF_INT_GATE("200", 200);
DEF_INT_GATE("201", 201);
DEF_INT_GATE("202", 202);
DEF_INT_GATE("203", 203);
DEF_INT_GATE("204", 204);
DEF_INT_GATE("205", 205);
DEF_INT_GATE("206", 206);
DEF_INT_GATE("207", 207);
DEF_INT_GATE("208", 208);
DEF_INT_GATE("209", 209);
DEF_INT_GATE("210", 210);
DEF_INT_GATE("211", 211);
DEF_INT_GATE("212", 212);
DEF_INT_GATE("213", 213);
DEF_INT_GATE("214", 214);
DEF_INT_GATE("215", 215);
DEF_INT_GATE("216", 216);
DEF_INT_GATE("217", 217);
DEF_INT_GATE("218", 218);
DEF_INT_GATE("219", 219);
DEF_INT_GATE("220", 220);
DEF_INT_GATE("221", 221);
DEF_INT_GATE("222", 222);
DEF_INT_GATE("223", 223);
DEF_INT_GATE("224", 224);
DEF_INT_GATE("225", 225);
DEF_INT_GATE("226", 226);
DEF_INT_GATE("227", 227);
DEF_INT_GATE("228", 228);
DEF_INT_GATE("229", 229);
DEF_INT_GATE("230", 230);
DEF_INT_GATE("231", 231);
DEF_INT_GATE("232", 232);
DEF_INT_GATE("233", 233);
DEF_INT_GATE("234", 234);
DEF_INT_GATE("235", 235);
DEF_INT_GATE("236", 236);
DEF_INT_GATE("237", 237);
DEF_INT_GATE("238", 238);
DEF_INT_GATE("239", 239);
DEF_INT_GATE("240", 240);
DEF_INT_GATE("241", 241);
DEF_INT_GATE("242", 242);
DEF_INT_GATE("243", 243);
DEF_INT_GATE("244", 244);
DEF_INT_GATE("245", 245);
DEF_INT_GATE("246", 246);
DEF_INT_GATE("247", 247);
DEF_INT_GATE("248", 248);
DEF_INT_GATE("249", 249);
DEF_INT_GATE("250", 250);
DEF_INT_GATE("251", 251);
DEF_INT_GATE("252", 252);
DEF_INT_GATE("253", 253);
DEF_INT_GATE("254", 254);

#endif /* X86_GATES_H_ */
