#include<iostream>

class BigInteger{
    int digits[40];
    int capacity = 40;

    public:
    BigInteger(){
        for(int i = 0; i < capacity; i++ )
            digits[i] = 0;
    }

    BigInteger(long long val){
        int i = 0;
        while(val){
            digits[i++] = val % 10;
            val /= 10;
        }

        for(; i < capacity; i++ )
            digits[i] = 0;
    }

    friend std::ostream& operator<<(std::ostream& os,const BigInteger &bi){
        for(int i = bi.capacity - 1; i >= 0;  i--){
            if(bi.digits[i])
                os << bi.digits[i] <<  (i%4==0? " " : "");
        }

        return os;
    }

    BigInteger add(const BigInteger &bi){
        BigInteger temp;

        int carry = 0;
        for(int i = 0; i < capacity; i++){
            temp.digits[i] = bi.digits[i] + this->digits[i] + carry;
            carry = temp.digits[i] / 10;
            temp.digits[i] = temp.digits[i] % 10;;
        }

        return temp;
    }

    BigInteger subtract(const BigInteger &bi){
        BigInteger temp;

        int carry = 0;
        for(int i = 0; i < capacity; i++){
            temp.digits[i] =  - bi.digits[i] + this->digits[i] - carry;

            //std::cout << temp.digits[i] << " " << bi.digits[i] << " " << this->digits[i] << std::endl;

            if(temp.digits[i] < 0){
                carry = 1;
                temp.digits[i] += 10;
            }
            else{
                carry= 0;
            }
        }

        return temp;
    }
};

int main(){
    BigInteger a(429);
    BigInteger b(1927);
    BigInteger c(1927429);

    BigInteger d(123456);
    BigInteger e(7);

    std::cout << a << std::endl << b << std::endl << c << std::endl;
    std::cout << a.add(b) << std::endl;
    std::cout << d.subtract(e) << std::endl;
}


