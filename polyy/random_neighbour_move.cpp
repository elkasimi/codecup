#include "position.h"

Move Position::get_random_neighbour_move() const {
	const Data* data = _player == WHITE ? _data_white : _data_black;
	int count = 0;
	Move choices[N];
	if((_fields[1] == NONE) and (data[1].neighbour)) {
		choices[count++] = (Move)1;
	}
	if((_fields[2] == NONE) and (data[2].neighbour)) {
		choices[count++] = (Move)2;
	}
	if((_fields[3] == NONE) and (data[3].neighbour)) {
		choices[count++] = (Move)3;
	}
	if((_fields[4] == NONE) and (data[4].neighbour)) {
		choices[count++] = (Move)4;
	}
	if((_fields[5] == NONE) and (data[5].neighbour)) {
		choices[count++] = (Move)5;
	}
	if((_fields[6] == NONE) and (data[6].neighbour)) {
		choices[count++] = (Move)6;
	}
	if((_fields[7] == NONE) and (data[7].neighbour)) {
		choices[count++] = (Move)7;
	}
	if((_fields[8] == NONE) and (data[8].neighbour)) {
		choices[count++] = (Move)8;
	}
	if((_fields[9] == NONE) and (data[9].neighbour)) {
		choices[count++] = (Move)9;
	}
	if((_fields[10] == NONE) and (data[10].neighbour)) {
		choices[count++] = (Move)10;
	}
	if((_fields[11] == NONE) and (data[11].neighbour)) {
		choices[count++] = (Move)11;
	}
	if((_fields[12] == NONE) and (data[12].neighbour)) {
		choices[count++] = (Move)12;
	}
	if((_fields[13] == NONE) and (data[13].neighbour)) {
		choices[count++] = (Move)13;
	}
	if((_fields[14] == NONE) and (data[14].neighbour)) {
		choices[count++] = (Move)14;
	}
	if((_fields[15] == NONE) and (data[15].neighbour)) {
		choices[count++] = (Move)15;
	}
	if((_fields[16] == NONE) and (data[16].neighbour)) {
		choices[count++] = (Move)16;
	}
	if((_fields[17] == NONE) and (data[17].neighbour)) {
		choices[count++] = (Move)17;
	}
	if((_fields[18] == NONE) and (data[18].neighbour)) {
		choices[count++] = (Move)18;
	}
	if((_fields[19] == NONE) and (data[19].neighbour)) {
		choices[count++] = (Move)19;
	}
	if((_fields[20] == NONE) and (data[20].neighbour)) {
		choices[count++] = (Move)20;
	}
	if((_fields[21] == NONE) and (data[21].neighbour)) {
		choices[count++] = (Move)21;
	}
	if((_fields[22] == NONE) and (data[22].neighbour)) {
		choices[count++] = (Move)22;
	}
	if((_fields[23] == NONE) and (data[23].neighbour)) {
		choices[count++] = (Move)23;
	}
	if((_fields[24] == NONE) and (data[24].neighbour)) {
		choices[count++] = (Move)24;
	}
	if((_fields[25] == NONE) and (data[25].neighbour)) {
		choices[count++] = (Move)25;
	}
	if((_fields[26] == NONE) and (data[26].neighbour)) {
		choices[count++] = (Move)26;
	}
	if((_fields[27] == NONE) and (data[27].neighbour)) {
		choices[count++] = (Move)27;
	}
	if((_fields[28] == NONE) and (data[28].neighbour)) {
		choices[count++] = (Move)28;
	}
	if((_fields[29] == NONE) and (data[29].neighbour)) {
		choices[count++] = (Move)29;
	}
	if((_fields[30] == NONE) and (data[30].neighbour)) {
		choices[count++] = (Move)30;
	}
	if((_fields[31] == NONE) and (data[31].neighbour)) {
		choices[count++] = (Move)31;
	}
	if((_fields[32] == NONE) and (data[32].neighbour)) {
		choices[count++] = (Move)32;
	}
	if((_fields[33] == NONE) and (data[33].neighbour)) {
		choices[count++] = (Move)33;
	}
	if((_fields[34] == NONE) and (data[34].neighbour)) {
		choices[count++] = (Move)34;
	}
	if((_fields[35] == NONE) and (data[35].neighbour)) {
		choices[count++] = (Move)35;
	}
	if((_fields[36] == NONE) and (data[36].neighbour)) {
		choices[count++] = (Move)36;
	}
	if((_fields[37] == NONE) and (data[37].neighbour)) {
		choices[count++] = (Move)37;
	}
	if((_fields[38] == NONE) and (data[38].neighbour)) {
		choices[count++] = (Move)38;
	}
	if((_fields[39] == NONE) and (data[39].neighbour)) {
		choices[count++] = (Move)39;
	}
	if((_fields[40] == NONE) and (data[40].neighbour)) {
		choices[count++] = (Move)40;
	}
	if((_fields[41] == NONE) and (data[41].neighbour)) {
		choices[count++] = (Move)41;
	}
	if((_fields[42] == NONE) and (data[42].neighbour)) {
		choices[count++] = (Move)42;
	}
	if((_fields[43] == NONE) and (data[43].neighbour)) {
		choices[count++] = (Move)43;
	}
	if((_fields[44] == NONE) and (data[44].neighbour)) {
		choices[count++] = (Move)44;
	}
	if((_fields[45] == NONE) and (data[45].neighbour)) {
		choices[count++] = (Move)45;
	}
	if((_fields[46] == NONE) and (data[46].neighbour)) {
		choices[count++] = (Move)46;
	}
	if((_fields[47] == NONE) and (data[47].neighbour)) {
		choices[count++] = (Move)47;
	}
	if((_fields[48] == NONE) and (data[48].neighbour)) {
		choices[count++] = (Move)48;
	}
	if((_fields[49] == NONE) and (data[49].neighbour)) {
		choices[count++] = (Move)49;
	}
	if((_fields[50] == NONE) and (data[50].neighbour)) {
		choices[count++] = (Move)50;
	}
	if((_fields[51] == NONE) and (data[51].neighbour)) {
		choices[count++] = (Move)51;
	}
	if((_fields[52] == NONE) and (data[52].neighbour)) {
		choices[count++] = (Move)52;
	}
	if((_fields[53] == NONE) and (data[53].neighbour)) {
		choices[count++] = (Move)53;
	}
	if((_fields[54] == NONE) and (data[54].neighbour)) {
		choices[count++] = (Move)54;
	}
	if((_fields[55] == NONE) and (data[55].neighbour)) {
		choices[count++] = (Move)55;
	}
	if((_fields[56] == NONE) and (data[56].neighbour)) {
		choices[count++] = (Move)56;
	}
	if((_fields[57] == NONE) and (data[57].neighbour)) {
		choices[count++] = (Move)57;
	}
	if((_fields[58] == NONE) and (data[58].neighbour)) {
		choices[count++] = (Move)58;
	}
	if((_fields[59] == NONE) and (data[59].neighbour)) {
		choices[count++] = (Move)59;
	}
	if((_fields[60] == NONE) and (data[60].neighbour)) {
		choices[count++] = (Move)60;
	}
	if((_fields[61] == NONE) and (data[61].neighbour)) {
		choices[count++] = (Move)61;
	}
	if((_fields[62] == NONE) and (data[62].neighbour)) {
		choices[count++] = (Move)62;
	}
	if((_fields[63] == NONE) and (data[63].neighbour)) {
		choices[count++] = (Move)63;
	}
	if((_fields[64] == NONE) and (data[64].neighbour)) {
		choices[count++] = (Move)64;
	}
	if((_fields[65] == NONE) and (data[65].neighbour)) {
		choices[count++] = (Move)65;
	}
	if((_fields[66] == NONE) and (data[66].neighbour)) {
		choices[count++] = (Move)66;
	}
	if((_fields[67] == NONE) and (data[67].neighbour)) {
		choices[count++] = (Move)67;
	}
	if((_fields[68] == NONE) and (data[68].neighbour)) {
		choices[count++] = (Move)68;
	}
	if((_fields[69] == NONE) and (data[69].neighbour)) {
		choices[count++] = (Move)69;
	}
	if((_fields[70] == NONE) and (data[70].neighbour)) {
		choices[count++] = (Move)70;
	}
	if((_fields[71] == NONE) and (data[71].neighbour)) {
		choices[count++] = (Move)71;
	}
	if((_fields[72] == NONE) and (data[72].neighbour)) {
		choices[count++] = (Move)72;
	}
	if((_fields[73] == NONE) and (data[73].neighbour)) {
		choices[count++] = (Move)73;
	}
	if((_fields[74] == NONE) and (data[74].neighbour)) {
		choices[count++] = (Move)74;
	}
	if((_fields[75] == NONE) and (data[75].neighbour)) {
		choices[count++] = (Move)75;
	}
	if((_fields[76] == NONE) and (data[76].neighbour)) {
		choices[count++] = (Move)76;
	}
	if((_fields[77] == NONE) and (data[77].neighbour)) {
		choices[count++] = (Move)77;
	}
	if((_fields[78] == NONE) and (data[78].neighbour)) {
		choices[count++] = (Move)78;
	}
	if((_fields[79] == NONE) and (data[79].neighbour)) {
		choices[count++] = (Move)79;
	}
	if((_fields[80] == NONE) and (data[80].neighbour)) {
		choices[count++] = (Move)80;
	}
	if((_fields[81] == NONE) and (data[81].neighbour)) {
		choices[count++] = (Move)81;
	}
	if((_fields[82] == NONE) and (data[82].neighbour)) {
		choices[count++] = (Move)82;
	}
	if((_fields[83] == NONE) and (data[83].neighbour)) {
		choices[count++] = (Move)83;
	}
	if((_fields[84] == NONE) and (data[84].neighbour)) {
		choices[count++] = (Move)84;
	}
	if((_fields[85] == NONE) and (data[85].neighbour)) {
		choices[count++] = (Move)85;
	}
	if((_fields[86] == NONE) and (data[86].neighbour)) {
		choices[count++] = (Move)86;
	}
	if((_fields[87] == NONE) and (data[87].neighbour)) {
		choices[count++] = (Move)87;
	}
	if((_fields[88] == NONE) and (data[88].neighbour)) {
		choices[count++] = (Move)88;
	}
	if((_fields[89] == NONE) and (data[89].neighbour)) {
		choices[count++] = (Move)89;
	}
	if((_fields[90] == NONE) and (data[90].neighbour)) {
		choices[count++] = (Move)90;
	}
	if((_fields[91] == NONE) and (data[91].neighbour)) {
		choices[count++] = (Move)91;
	}
	if((_fields[92] == NONE) and (data[92].neighbour)) {
		choices[count++] = (Move)92;
	}
	if((_fields[93] == NONE) and (data[93].neighbour)) {
		choices[count++] = (Move)93;
	}
	if((_fields[94] == NONE) and (data[94].neighbour)) {
		choices[count++] = (Move)94;
	}
	if((_fields[95] == NONE) and (data[95].neighbour)) {
		choices[count++] = (Move)95;
	}
	if((_fields[96] == NONE) and (data[96].neighbour)) {
		choices[count++] = (Move)96;
	}
	if((_fields[97] == NONE) and (data[97].neighbour)) {
		choices[count++] = (Move)97;
	}
	if((_fields[98] == NONE) and (data[98].neighbour)) {
		choices[count++] = (Move)98;
	}
	if((_fields[99] == NONE) and (data[99].neighbour)) {
		choices[count++] = (Move)99;
	}
	if((_fields[100] == NONE) and (data[100].neighbour)) {
		choices[count++] = (Move)100;
	}
	if((_fields[101] == NONE) and (data[101].neighbour)) {
		choices[count++] = (Move)101;
	}
	if((_fields[102] == NONE) and (data[102].neighbour)) {
		choices[count++] = (Move)102;
	}
	if((_fields[103] == NONE) and (data[103].neighbour)) {
		choices[count++] = (Move)103;
	}
	if((_fields[104] == NONE) and (data[104].neighbour)) {
		choices[count++] = (Move)104;
	}
	if((_fields[105] == NONE) and (data[105].neighbour)) {
		choices[count++] = (Move)105;
	}
	if((_fields[106] == NONE) and (data[106].neighbour)) {
		choices[count++] = (Move)106;
	}
	if(count > 0) {
		int idx = rand() % count;
		return choices[idx];
	} else {
		return UNKNOWN_MOVE;
	}
}

