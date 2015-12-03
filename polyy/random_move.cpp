Move Position::get_random_move() const {
    if(_moves == 1) {
        int b = rand() & 1;
        if(b == 0) {
            return SWAP_MOVE;
        }
    }
    Move choices[N + 1];
    int count = 0;
    if(_fields[1] == NONE) {
        choices[count++] = (Move)1;
    }
    if(_fields[2] == NONE) {
        choices[count++] = (Move)2;
    }
    if(_fields[3] == NONE) {
        choices[count++] = (Move)3;
    }
    if(_fields[4] == NONE) {
        choices[count++] = (Move)4;
    }
    if(_fields[5] == NONE) {
        choices[count++] = (Move)5;
    }
    if(_fields[6] == NONE) {
        choices[count++] = (Move)6;
    }
    if(_fields[7] == NONE) {
        choices[count++] = (Move)7;
    }
    if(_fields[8] == NONE) {
        choices[count++] = (Move)8;
    }
    if(_fields[9] == NONE) {
        choices[count++] = (Move)9;
    }
    if(_fields[10] == NONE) {
        choices[count++] = (Move)10;
    }
    if(_fields[11] == NONE) {
        choices[count++] = (Move)11;
    }
    if(_fields[12] == NONE) {
        choices[count++] = (Move)12;
    }
    if(_fields[13] == NONE) {
        choices[count++] = (Move)13;
    }
    if(_fields[14] == NONE) {
        choices[count++] = (Move)14;
    }
    if(_fields[15] == NONE) {
        choices[count++] = (Move)15;
    }
    if(_fields[16] == NONE) {
        choices[count++] = (Move)16;
    }
    if(_fields[17] == NONE) {
        choices[count++] = (Move)17;
    }
    if(_fields[18] == NONE) {
        choices[count++] = (Move)18;
    }
    if(_fields[19] == NONE) {
        choices[count++] = (Move)19;
    }
    if(_fields[20] == NONE) {
        choices[count++] = (Move)20;
    }
    if(_fields[21] == NONE) {
        choices[count++] = (Move)21;
    }
    if(_fields[22] == NONE) {
        choices[count++] = (Move)22;
    }
    if(_fields[23] == NONE) {
        choices[count++] = (Move)23;
    }
    if(_fields[24] == NONE) {
        choices[count++] = (Move)24;
    }
    if(_fields[25] == NONE) {
        choices[count++] = (Move)25;
    }
    if(_fields[26] == NONE) {
        choices[count++] = (Move)26;
    }
    if(_fields[27] == NONE) {
        choices[count++] = (Move)27;
    }
    if(_fields[28] == NONE) {
        choices[count++] = (Move)28;
    }
    if(_fields[29] == NONE) {
        choices[count++] = (Move)29;
    }
    if(_fields[30] == NONE) {
        choices[count++] = (Move)30;
    }
    if(_fields[31] == NONE) {
        choices[count++] = (Move)31;
    }
    if(_fields[32] == NONE) {
        choices[count++] = (Move)32;
    }
    if(_fields[33] == NONE) {
        choices[count++] = (Move)33;
    }
    if(_fields[34] == NONE) {
        choices[count++] = (Move)34;
    }
    if(_fields[35] == NONE) {
        choices[count++] = (Move)35;
    }
    if(_fields[36] == NONE) {
        choices[count++] = (Move)36;
    }
    if(_fields[37] == NONE) {
        choices[count++] = (Move)37;
    }
    if(_fields[38] == NONE) {
        choices[count++] = (Move)38;
    }
    if(_fields[39] == NONE) {
        choices[count++] = (Move)39;
    }
    if(_fields[40] == NONE) {
        choices[count++] = (Move)40;
    }
    if(_fields[41] == NONE) {
        choices[count++] = (Move)41;
    }
    if(_fields[42] == NONE) {
        choices[count++] = (Move)42;
    }
    if(_fields[43] == NONE) {
        choices[count++] = (Move)43;
    }
    if(_fields[44] == NONE) {
        choices[count++] = (Move)44;
    }
    if(_fields[45] == NONE) {
        choices[count++] = (Move)45;
    }
    if(_fields[46] == NONE) {
        choices[count++] = (Move)46;
    }
    if(_fields[47] == NONE) {
        choices[count++] = (Move)47;
    }
    if(_fields[48] == NONE) {
        choices[count++] = (Move)48;
    }
    if(_fields[49] == NONE) {
        choices[count++] = (Move)49;
    }
    if(_fields[50] == NONE) {
        choices[count++] = (Move)50;
    }
    if(_fields[51] == NONE) {
        choices[count++] = (Move)51;
    }
    if(_fields[52] == NONE) {
        choices[count++] = (Move)52;
    }
    if(_fields[53] == NONE) {
        choices[count++] = (Move)53;
    }
    if(_fields[54] == NONE) {
        choices[count++] = (Move)54;
    }
    if(_fields[55] == NONE) {
        choices[count++] = (Move)55;
    }
    if(_fields[56] == NONE) {
        choices[count++] = (Move)56;
    }
    if(_fields[57] == NONE) {
        choices[count++] = (Move)57;
    }
    if(_fields[58] == NONE) {
        choices[count++] = (Move)58;
    }
    if(_fields[59] == NONE) {
        choices[count++] = (Move)59;
    }
    if(_fields[60] == NONE) {
        choices[count++] = (Move)60;
    }
    if(_fields[61] == NONE) {
        choices[count++] = (Move)61;
    }
    if(_fields[62] == NONE) {
        choices[count++] = (Move)62;
    }
    if(_fields[63] == NONE) {
        choices[count++] = (Move)63;
    }
    if(_fields[64] == NONE) {
        choices[count++] = (Move)64;
    }
    if(_fields[65] == NONE) {
        choices[count++] = (Move)65;
    }
    if(_fields[66] == NONE) {
        choices[count++] = (Move)66;
    }
    if(_fields[67] == NONE) {
        choices[count++] = (Move)67;
    }
    if(_fields[68] == NONE) {
        choices[count++] = (Move)68;
    }
    if(_fields[69] == NONE) {
        choices[count++] = (Move)69;
    }
    if(_fields[70] == NONE) {
        choices[count++] = (Move)70;
    }
    if(_fields[71] == NONE) {
        choices[count++] = (Move)71;
    }
    if(_fields[72] == NONE) {
        choices[count++] = (Move)72;
    }
    if(_fields[73] == NONE) {
        choices[count++] = (Move)73;
    }
    if(_fields[74] == NONE) {
        choices[count++] = (Move)74;
    }
    if(_fields[75] == NONE) {
        choices[count++] = (Move)75;
    }
    if(_fields[76] == NONE) {
        choices[count++] = (Move)76;
    }
    if(_fields[77] == NONE) {
        choices[count++] = (Move)77;
    }
    if(_fields[78] == NONE) {
        choices[count++] = (Move)78;
    }
    if(_fields[79] == NONE) {
        choices[count++] = (Move)79;
    }
    if(_fields[80] == NONE) {
        choices[count++] = (Move)80;
    }
    if(_fields[81] == NONE) {
        choices[count++] = (Move)81;
    }
    if(_fields[82] == NONE) {
        choices[count++] = (Move)82;
    }
    if(_fields[83] == NONE) {
        choices[count++] = (Move)83;
    }
    if(_fields[84] == NONE) {
        choices[count++] = (Move)84;
    }
    if(_fields[85] == NONE) {
        choices[count++] = (Move)85;
    }
    if(_fields[86] == NONE) {
        choices[count++] = (Move)86;
    }
    if(_fields[87] == NONE) {
        choices[count++] = (Move)87;
    }
    if(_fields[88] == NONE) {
        choices[count++] = (Move)88;
    }
    if(_fields[89] == NONE) {
        choices[count++] = (Move)89;
    }
    if(_fields[90] == NONE) {
        choices[count++] = (Move)90;
    }
    if(_fields[91] == NONE) {
        choices[count++] = (Move)91;
    }
    if(_fields[92] == NONE) {
        choices[count++] = (Move)92;
    }
    if(_fields[93] == NONE) {
        choices[count++] = (Move)93;
    }
    if(_fields[94] == NONE) {
        choices[count++] = (Move)94;
    }
    if(_fields[95] == NONE) {
        choices[count++] = (Move)95;
    }
    if(_fields[96] == NONE) {
        choices[count++] = (Move)96;
    }
    if(_fields[97] == NONE) {
        choices[count++] = (Move)97;
    }
    if(_fields[98] == NONE) {
        choices[count++] = (Move)98;
    }
    if(_fields[99] == NONE) {
        choices[count++] = (Move)99;
    }
    if(_fields[100] == NONE) {
        choices[count++] = (Move)100;
    }
    if(_fields[101] == NONE) {
        choices[count++] = (Move)101;
    }
    if(_fields[102] == NONE) {
        choices[count++] = (Move)102;
    }
    if(_fields[103] == NONE) {
        choices[count++] = (Move)103;
    }
    if(_fields[104] == NONE) {
        choices[count++] = (Move)104;
    }
    if(_fields[105] == NONE) {
        choices[count++] = (Move)105;
    }
    if(_fields[106] == NONE) {
        choices[count++] = (Move)106;
    }
    int idx = rand() % count;
    Move move = choices[idx];
    return move;
}
