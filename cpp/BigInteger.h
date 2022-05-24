#include <iostream>
#include <cstdint>
#include <cstring>

#define SIZE_OF_BYTE 8
#define INFO_SIZE 128

using namespace std;

typedef uint16_t UINT_16;

UINT_16 get_int_no_of_bits()
{
    /// e.g. 16
    return sizeof(UINT_16) * SIZE_OF_BYTE;
}

void print_uint16_bits(UINT_16 e)
{
    UINT_16 no_of_bits = get_int_no_of_bits(); /// e.g. 16

    for(UINT_16 i = (1 << (no_of_bits - 1)); i != 0; i >>= 1)
    {
        /// extracts MSB digits one after another
        UINT_16 bit_i = ((e & i) != 0);
        cout << bit_i;
    }
}

/// Base class that must be inherited, functions of which must be overriden.
class BigInteger
{
private:
    char INFO[INFO_SIZE]; /// Stores some information of the Integer (e.g. size, bit_str etc.) as a string

protected:

    /// Empty Constructor: Stores "?" as information of the Integer
    BigInteger()
    {
        INFO[0] = '?';
        INFO[1] = '\0';
    }

    /// Parameterized Constructor: Stores the passed string as information of the Integer
    BigInteger(const char *info)
    {
        strcpy(INFO, info);
    }

    ///
    /// The following functions should be overridden in the derived classes.
    ///

    /// Stores the passed bit string as information of the Integer and does necessary adjustments to the member attributes
    void Set_bit_str(const char* bit_str);

    /// Generates and returns the equivalent bit string of the Integer
    const char* Generate_bit_str();

    /// Shifts the Integer to the Left by k bits
    void ShiftLeft(UINT_16 k);

    /// Shifts the Integer to the Right by k bits
    void ShiftRight(UINT_16 k);

    /// Rotates the Integer Clockwise (to the Left) by k bits
    void RotateClockwise(UINT_16 k);

    /// Rotates the Integer AntiClockwise (to the Right) by k bits
    void RotateAntiClockwise(UINT_16 k);

    /// Adds n to the Integer
    void Add(UINT_16 n);

    /// Increments the Integer by 1
    void Increment();

    /// Prints the equivalent bit string of the Integer. It may need to use Generate_bit_str()
    void Print_bit_str();

public:
    /// Some getters and setters.

    /// Returns the stored information of the Integer as a string
    const char* getInfo()
    {
        return INFO;
    }

    /// Copies the stored information of the Integer into the passed string
    void getInfo(char *info)
    {
        strcpy(info, INFO);
    }

    /// Stores the passed string as information of the Integer
    void setInfo(const char *info)
    {
        strcpy(INFO, info);
    }
};


/// A class that will be used to model 32 bit unsigned integers. It inherits the BigInteger class.
class UINT_32 : public BigInteger
{
private:
    /// Necessary member attributes to store a 32 bit unsigned integer using only 16 bit unsigned integers.
    UINT_16 u;
    UINT_16 l;

public:

    /// TODO
    /// - A constructor that takes two UINT_16 parameters and does appropriate works. It may need to use a suitable constructor of the parent.
    UINT_32(UINT_16 u, UINT_16 l){
        this->u = u;
        this->l = l;
    }
    /// - A constructor that takes two UINT_16 and one info string as parameters and does appropriate works. It may need to use a suitable constructor of the parent.
    UINT_32(UINT_16 u, UINT_16 l, const char *info): UINT_32(u,l), BigInteger(info){

    }
    /// - A constructor that takes one string of bits as parameter and does appropriate works. It may need to use a suitable constructor of the parent.
    UINT_32(const char *str){
        Set_bit_str(str);
    }

    /// Some getters and setters.

    void set_u(UINT_16 u)
    {
        this->u = u;
    };

    void set_l(UINT_16 l)
    {
        this->l = l;
    };

    void set_ul(UINT_16 u, UINT_16 l)
    {
        set_u(u);
        set_l(l);
    };

    UINT_16 get_u()
    {
        return u;
    };

    UINT_16 get_l()
    {
        return l;
    };

    void get_ul(UINT_16 &u, UINT_16 &l)
    {
        u = get_u();
        l = get_l();
    };

    /// TODO
    /// The functions derived from the parent class that must be overriden:
    ///     void Set_bit_str(const char* bit_str);
    ///     const char* Generate_bit_str();
    ///     void ShiftLeft(UINT_16 k);
    ///     void ShiftRight(UINT_16 k);
    ///     void RotateClockwise(UINT_16 k);
    ///     void RotateAntiClockwise(UINT_16 k);
    ///     void Add(UINT_16 n);
    ///     void Increment();
    ///     void Print_bit_str();
    void Set_bit_str(const char* bit_str){
        u = 0;
        for(int i = 0; i < 16; i++){
            u = 2*u + bit_str[i] - '0';
        }
        l = 0;
        for(int i = 16; i < 32; i++){
            l = 2*l + bit_str[i] - '0';
        }
    }

    /// Generates and returns the equivalent bit string of the Integer
    const char* Generate_bit_str(){
        char bits[33];

        bits[32] = '\0';
        for(int i = 0;i < 16; i++){
            bits[31-i] = ( (l & (1<<i)) >>i )+ '0';
        }
        for(int i = 0; i < 16; i++){
            bits[15-i] = ( (u & (1<<i)) >>i )+ '0';
        }

        return bits;
    }

    /// Shifts the Integer to the Left by k bits
    void ShiftLeft(UINT_16 k){
        UINT_16 t = ~(~0 >> k) & l;
        t = t >> (16-k);

        u <<= k;
        l <<= k;
        u |= t;
    }

    /// Shifts the Integer to the Right by k bits
    void ShiftRight(UINT_16 k){
        UINT_16 t = ~(~0 << k) & u;
        t = t << (16-k);

        u >>= k;
        l >>= k;
        l |= t;
    }

    /// Rotates the Integer Clockwise (to the Left) by k bits
    void RotateClockwise(UINT_16 k){
        UINT_16 t = ~(~0 << k) & l;
        t = t << (16-k);

        ShiftRight(k);
        u |= t;
    }

    /// Rotates the Integer AntiClockwise (to the Right) by k bits
    void RotateAntiClockwise(UINT_16 k){
        UINT_16 t = ~(~0 >> k) & u;
        t = t >> (16-k);

        ShiftLeft(k);
        l |= t;
    }

    /// Adds n to the Integer
    void Add(UINT_16 n){
        UINT_32 a(0, n);
        this->Add(a);
    }

    /// Increments the Integer by 1
    void Increment(){
        this->Add(1);
    }


    /// Adds another UINT_32 to the Integer
    void Add(const UINT_32& n)
    {
        UINT_16 tl = l + n.l;

        if(tl < l && tl < n.l){ // has overflow
            u = u + n.u + 1;
        }else{
            u = u + n.u;
        }

        l = tl;
    }

    /// BONUS TODO
    /// The following operators must be overloaded:
    ///     shift left (<<)
    ///     shift right (>>)
    ///     postfix increment (e.g. n++)
    ///     prefix increment (e.g. ++n)
    ///     addition (+) with an UINT_16
    ///     addition (+) with another UINT_32
    ///     casting operator uint32_t()
};

/// A class that will be used to model 64 bit unsigned integers. It inherits the BigInteger class.
class UINT_64 : public BigInteger
{
private:
    /// TODO
    /// Necessary member attributes to store a 64 bit unsigned integer using only 16 bit unsigned integers.
    UINT_16 a,b, c,d;

public:

    /// TODO
    /// - A constructor that takes necessary number of UINT_16 parameters and does appropriate works. It may need to use a suitable constructor of the parent.
    UINT_64(UINT_16 a, UINT_16 a, UINT_16 a, UINT_16 a){
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
    /// - A constructor that takes necessary number of UINT_16 and one info string as parameters and does appropriate works. It may need to use a suitable constructor of the parent.
    UINT_64(UINT_16 a, UINT_16 a, UINT_16 a, UINT_16 a, const char * str)
        : UINT_64(a, b, c, d), BigInteger(str);
    {

    }
    /// - A constructor that takes one string of bits as parameter and does appropriate works. It may need to use a suitable constructor of the parent.
    UINT_64(const char *bit_str){
        Set_bit_str(bit_str);
    }

    /// TODO
    /// Appropriate getters and setters.

    /// TODO
    /// The functions derived from the parent class that must be overriden:
    ///     void Set_bit_str(const char* bit_str);
    ///     const char* Generate_bit_str();
    ///     void ShiftLeft(UINT_16 k);
    ///     void ShiftRight(UINT_16 k);
    ///     void RotateClockwise(UINT_16 k);
    ///     void RotateAntiClockwise(UINT_16 k);
    ///     void Add(UINT_16 n);
    ///     void Increment();
    ///     void Print_bit_str();
    /// Stores the passed bit string as information of the Integer and does necessary adjustments to the member attributes
    void Set_bit_str(const char* bit_str){
        a = 0;
        for(int i = 0; i < 16; i++){
            a = a*2 + bit_str[i] - '0';
        }

        b = 0;
        for(int i = 16; i < 32; i++){
            b = b*2 + bit_str[i] - '0';
        }

        c = 0;
        for(int i = 32; i < 48; i++){
            c = c*2 + bit_str[i] - '0';
        }

        d = 0;
        for(int i = 48; i < 64; i++){
            d = d*2 + bit_str[i] - '0';
        }
    }

    /// Generates and returns the equivalent bit string of the Integer
    const char* Generate_bit_str(){
        char str[65];
        str[64] = '\0';

        for(int i = 0; i < 16; i++){
            str[63-i] = ( (a & (1<<i)) >>i )+ '0';
        }
        for(int i = 0; i < 16; i++){
            str[47-i] = ( (b & (1<<i)) >>i )+ '0';
        }
        for(int i = 0; i < 16; i++){
            str[31-i] = ( (c & (1<<i)) >>i )+ '0';
        }
        for(int i = 0; i < 16; i++){
            str[15-i] = ( (d & (1<<i)) >>i )+ '0';
        }

    }

    /// Shifts the Integer to the Left by k bits
    void ShiftLeft(UINT_16 k){
        UINT_16 t1 = ~(~0 >> k) & d;
        t1 = t1 >> (16-k);

        UINT_16 t2 = ~(~0 >> k) & c;
        t2 = t2 >> (16-k);

        UINT_16 t3 = ~(~0 >> k) & b;
        t3 = t3 >> (16-k);

        a <<= k;
        b <<= k;
        c <<= k;
        d <<= k;
        
        a |= t3;
        b |= t2;
        c |= t1;
    }

    /// Shifts the Integer to the Right by k bits
    void ShiftRight(UINT_16 k){
        UINT_16 t1 = ~(~0 << k) & a;
        t1 = t1 << (16-k);

        UINT_16 t2 = ~(~0 << k) & b;
        t2 = t2 << (16-k);

        UINT_16 t3 = ~(~0 << k) & c;
        t3 = t3 << (16-k);

        a >>= k;
        b >>= k;
        c >>= k;
        d >>= k;
        
        b |= t1;
        c |= t2;
        d |= t3;
    }

    /// Rotates the Integer Clockwise (to the Left) by k bits
    void RotateClockwise(UINT_16 k){
        UINT_16 t = ~(~0 << k) & d;
        t = t << (16-k);

        ShiftRight(k);
        a |= t;
    }

    /// Rotates the Integer AntiClockwise (to the Right) by k bits
    void RotateAntiClockwise(UINT_16 k){
        UINT_16 t = ~(~0 >> k) & a;
        t = t >> (16-k);

        ShiftLeft(k);
        d |= t;
    }

    /// Adds n to the Integer
    void Add(UINT_16 n){
        Add(UINT_64(0,0,0,n));
    }

    /// Increments the Integer by 1
    void Increment(){
        Add(1);
    }

    /// Prints the equivalent bit string of the Integer. It may need to use Generate_bit_str()
    void Print_bit_str(){
        cout << Generate_bit_str() << endl;
    }

    

    /// Adds another UINT_64 to the Integer
    void Add(const UINT_64& n)
    {
        UINT_16 t = d + n.d;
        UINT_16 carry = 0;
        if(t < d && t < n.d){
            carry = 1;
        }

        d = t;
        t = c + n.c + carry;
        carry = 0;
        if(t < c && t < n.c){
            carry = 1;
        }

        c = t;
        t = b + b.c + carry;
        carry = 0;
        if(t < b && t < n.b){
            carry = 1;
        }

        b = t;
        a = a + n.c + carry;
    }

    /// BONUS TODO
    /// The following operators must be overloaded:
    ///     shift left (<<)
    ///     shift right (>>)
    ///     postfix increment (e.g. n++)
    ///     prefix increment (e.g. ++n)
    ///     addition (+) with an UINT_16
    ///     addition (+) with another UINT_64
    ///     casting operator uint64_t()
};
