 #ifndef     BIT_MATH
 #define     BIT_MATH

#define clear_bit(register , bit_num)     (register=register & ((0xffff )^( 1u<<bit_num))
#define set_bit(register , bit_num)       (register=register | (1u<<bit_num))
#define toggle_bit(register , bit_num)    (register=register ^ (1u<<bit_num))


 #endif
