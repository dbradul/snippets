#include <string>
#include <iostream>
#include <cassert>

using namespace std;


/*
Class for BIG integers (> 2^64)
*/
class big_int
{
private:
   string _val;

   void divide(const big_int& limit, big_int& sum, big_int& k)
   {
      if( sum+sum <= limit )
      { 
         big_int curr_sum  = sum;
         big_int curr_k    = k;
         sum += sum;
         k += k;

        //continue doubling until we reach or exceed the limit and then go back
         divide(limit, sum, k);

         // if possible increase the result with the current value
         if( ( curr_sum + sum ) <= limit )
         {
            sum   += curr_sum;
            k     += curr_k;
         }
      }
   }

   void mult(const big_int& limit, big_int& sum, big_int& k)
   {
      if( k+k <= limit )
      { 
         big_int curr_sum  = sum;
         big_int curr_k    = k;
         sum += sum;
         k += k;

         //continue doubling until we reach or exceed the limit and then go back
         mult(limit, sum, k);

         // if possible increase the result with the current value
         if( ( curr_k + k ) <= limit )
         {
            sum   += curr_sum;
            k     += curr_k;
         }
      }
   }

public:
   big_int()
   {
   }

   big_int(const char* str):_val(str)
   {
   }

   big_int(const big_int& rhs):_val(rhs._val)
   {
   }

   ~big_int()
   {
   }

   big_int& operator =(const big_int& rhs)
   {
      if (this != & rhs)
      {
         _val = rhs._val;
      }
      return *this;
   }

   bool operator <(const big_int& rhs)
   {
      bool bResult = ( _val.length()<rhs._val.length() );
      if (_val.length()==rhs._val.length())
      {
         string::const_iterator iter1 = _val.begin();
         string::const_iterator iter2 = rhs._val.begin();

         for ( ; iter1 != _val.end() && *iter1 == *iter2; ++iter1, ++iter2 )
         {
         }

         bResult = ( _val.end()==iter1 ) ? false : ( *iter1 < *iter2 );
      }
      return bResult;
   }

   bool operator >(const big_int& rhs)
   {
      return !(*this<rhs);
   }

   bool operator ==(const big_int& rhs)
   {
      return _val == rhs._val;
   }

   bool operator !=(const big_int& rhs)
   {
      return !(*this == rhs);
   }

   bool operator <=(const big_int& rhs)
   {
      return ( *this<rhs || *this==rhs );
   }

   bool operator >=(const big_int& rhs)
   {
      return ( *this>rhs || *this==rhs );
   }

   big_int& operator +=(const big_int& rhs)
   {
      if ( rhs._val.length() > _val.length() )
      {
         _val.insert(_val.begin(), rhs._val.length() - _val.length(), '0');
      }

      reverse_iterator<string::iterator> riter1 = _val.rbegin();
      reverse_iterator<string::const_iterator> riter2 = rhs._val.rbegin();
      char next_byte_addition = 0;
      for(; riter1 != _val.rend(); ++riter1 )
      {
         char val1 = *(riter1) - '0';
         char val2 = ( riter2 != rhs._val.rend() ) ? *(riter2++) - '0' : 0;
         char res_sum = ( val1 + val2 + next_byte_addition );

         next_byte_addition = 0;
         if ( res_sum > 9 )
         {
            next_byte_addition = 1;
            res_sum %= 10;
         }
         *riter1 = res_sum + '0';
      }
      if ( next_byte_addition )
      {
         _val.insert(0,1,'1');
      }
      return *this;
   }


   big_int& operator /(const big_int& rhs)
   {
      //check the special case when the dividend is less then the divisor => quotient=0, remainder=dividend
      if (*this < rhs)
      {
         *this = "0";
      }
      else
      {
         big_int sum = rhs;
         big_int k = "1";

         divide(*this, sum, k);

         //so far, k is the quotient: sum=rhs*k+remainder
         *this = k;
      }
      return *this;
   }

   big_int& operator *(const big_int& rhs)
   {
      //check the special case 
      if (big_int("1") != rhs)
      {
         big_int sum = rhs;
         big_int k = "1";

         mult(*this, sum, k);

         //so far, sum is the production: sum=rhs*k+remainder
         *this = sum;
      }
      return *this;
   }

   big_int operator+(const big_int& rhs)
   {
      return big_int(*this) += rhs;
   }

   friend ostream& operator<<(ostream& stream, const big_int& rhs)
   {
      return stream << rhs._val;
   }
};



int main( int argc, char* argv[] )
{

   assert( big_int("12300000000000000000009990000000000000000000") 
        == big_int("12300000000000000000009990000000000000000000") );
   assert( big_int("123") <= big_int("124") );
   assert( big_int("124") >  big_int("123") );
   assert( big_int("0")   <  big_int("1") );
   assert( big_int("100") <  big_int("1100") );
   assert( big_int("1000")>  big_int("110") );

   big_int num1 = "111111111111111111111111111111111111111111111111111111123";
   big_int num2 = "111111111111111111111111111111111111111111111111111111456";
   big_int res  = "222222222222222222222222222222222222222222222222222222579";
   assert( res == ( num1+num2 ) );

   num1 = "0";
   num2 = "111111111111111111111111111111111111111111111111111111456";
   res  = "111111111111111111111111111111111111111111111111111111456";
   assert( res == ( num1+num2 ) );

   num1 = "42";
   num2 = "111111111111111111111111111111111111111111111111111111456";
   res  = "111111111111111111111111111111111111111111111111111111498";
   assert( res == ( num1+num2 ) );

   num1 = "42";
   num2 = "0";
   res  = "42";
   assert( res == ( num1+num2 ) );

   num1 =  "999999999999999999999999999999999999999999999999999999999";
   num2 =  "999999999999999999999999999999999999999999999999999999999";
   res  = "1999999999999999999999999999999999999999999999999999999998";
   assert( res == ( num1+num2 ) );

   big_int num3;
   num1 =  "909090909090909090909090909090909090909090909090909090909";
   num2 =   "90909090909090909090909090909090909090909090909090909090";
   num3 =  "999999999999999999999999999999999999999999999999999999999";
   res  = "1999999999999999999999999999999999999999999999999999999998";
   assert( res == ( num1+num2+num3 ) );

   num1 = "11111111111111111111111111111";
   res  = "22222222222222222222222222222";
   num1 += num1;
   assert( res == num1 );

   num1 = "32";
   num2 = "16";
   res  = "2";
   assert( res == ( num1/num2 ) );

   num1 = "41";
   num2 = "42";
   res  = "0";
   assert( res == ( num1/num2 ) );

   num1 = "420000000000000000000000000000000000000000000000000000000";
   num2 = "42";
   res  =  "10000000000000000000000000000000000000000000000000000000";
   assert( num1/num2 == res );

   num1 = "10000000000000000000000000050000000000000000000000000000";
   num2 = "1";
   res  = "10000000000000000000000000050000000000000000000000000000";
   assert( res == ( num1/num2 ) );

   num1 = "10000000000000000000000000000000000000000000000000000000";
   num2 = "10000000000000000000000000000000000000000000000000000000";
   res  = "1";
   assert( res == ( num1/num2 ) );

   num1 = "10000000000000000000000000000000000000000000000000000000";
   num2 = "6";
   res  = "1666666666666666666666666666666666666666666666666666666";
   assert( res == ( num1/num2 ) );

   num1 = "123456790123456790123456790120987654320987654320987654321";
   num2 = "11111111111111111111111111111";
   res  = "11111111111111111111111111111";
   assert( res == ( num1/num2 ) );

   num1 = "45283475823745298719283652734523457238457230945782093480193987";
   num2 = "23354603453495809834504503495803945830495723842734092348209234";
   assert( num1 == (num1*num2)/num2 );

   ////cout << big_int("11111111111111111111111111111") * big_int("11111111111111111111111111111") << endl;

   return 0;
}

