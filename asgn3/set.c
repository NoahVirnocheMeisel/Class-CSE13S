#include "set.h"
//returns a set with value 0, empty
Set set_empty(void) {
    Set empty = 0;
    return empty;
}
//returns a set with value 255, or 11111111, a full set
Set set_universal(void) {
    Set full = 255;
    return full;
}
//inserts an element into the set at specified index.
Set set_insert(Set s, int x) {
    Set returned = (s | (1 << x));
    return returned;
}
//removes an element from the set at specified index.
Set set_remove(Set s, int x) {
    Set returned = (s & ~(1 << x));
    return returned;
}

//checks if x is a member of set s by performing a right shift on s x times and then using a bitwise and operator to check if the value is in the set. returns true or false depending on the result. This method taken from Jess's tutor section.
bool set_member(Set s, int x) {
    int result = ((s >> x) & 1);
    if (result > 0) {
        return true;
    }
    return false;
}
//combines returns the union of two sets
Set set_union(Set s, Set t) {
    Set returned = (s | t);
    return returned;
}
//returns the intersection of two sets
Set set_intersect(Set s, Set t) {
    Set returned = (s & t);
    return returned;
}
//returns the difference of set s - set t
Set set_difference(Set s, Set t) {
    Set returned = (s & (~t));
    return returned;
}

Set set_complement(Set s) {
    return ~s;
}
