#ifndef __DATA_H__
#define __DATA_H__

extern Int neighbors[NXN][5];
extern Bool are_neighbors[NXN][NXN];

extern UInt zobrist_hash_init_value;
extern UInt zobrist_hash_player;
extern UInt zobrist_hash_field[NXN][2];

extern UInt zobrist_lock_init_value;
extern UInt zobrist_lock_player;
extern UInt zobrist_lock_field[NXN][2];

extern Int infinite_distance[NXN];

#endif
