void Position::_update(int f) {
    Data* data = _player == WHITE ? _data_white : _data_black;
    //update neighbour
    for(int* n = neighbours[f]; *n != 0; ++n) {
        data[*n].neighbour = true;
    }
    //update joint
    for(int* j = joint[f]; *j != 0; j += 3) {
        if(*j >= 0) {
            data[*j].joint = true;
        }
    }
    if(!is_neighbour_move(f)) {
        return;
    }
    int start, end, q[N + 1];
    bool marked[N + 1];
    memset(marked, false, N + 1);
    start = end = 0;
    int mask = field_mask[f];
    marked[f] = true;
    q[end++] = f;
    while(start != end) {
        int t = q[start++];
        for(int* n = neighbours[t]; *n != 0; ++n) {
            if(!marked[*n]) {
                if(_fields[*n] == _player) {
                    mask |= field_mask[*n];
                    marked[*n] = true;
                    q[end++] = *n;
                }
            }
        }
    }
    if((_control[1] == NONE) and ((mask & MASK_CORNER_1) == MASK_CORNER_1) and (mask != MASK_CORNER_1)) {
        _control[1] = _player;
    }
    if((_control[2] == NONE) and ((mask & MASK_CORNER_2) == MASK_CORNER_2) and (mask != MASK_CORNER_2)) {
        _control[2] = _player;
    }
    if((_control[3] == NONE) and ((mask & MASK_CORNER_3) == MASK_CORNER_3) and (mask != MASK_CORNER_3)) {
        _control[3] = _player;
    }
    if((_control[4] == NONE) and ((mask & MASK_CORNER_4) == MASK_CORNER_4) and (mask != MASK_CORNER_4)) {
        _control[4] = _player;
    }
    if((_control[5] == NONE) and ((mask & MASK_CORNER_5) == MASK_CORNER_5) and (mask != MASK_CORNER_5)) {
        _control[5] = _player;
    }
    int c = 0;
    if(_control[1] == _player) {
        ++c;
    }
    if(_control[2] == _player) {
        ++c;
    }
    if(_control[3] == _player) {
        ++c;
    }
    if(_control[4] == _player) {
        ++c;
    }
    if(_control[5] == _player) {
        ++c;
    }
    if(c >= 3) {
        _winner = _player;
    }
}
