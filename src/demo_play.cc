#include "../include/cir_list.h"

void play() {
    EC_playlist lst = playlist_new();
    for (int i=0; i<20; ++i)
        playlist_insert(lst, i);
    playlist_loopOnce(lst);
    playlist_drop(lst);
}