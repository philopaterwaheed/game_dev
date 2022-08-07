#include "vector_2d.h"


    vector_2d :: vector_2d(){
        x= y = 0.0f;



 }

 vector_2d :: vector_2d (float x , float y )

            {
                    this -> x =x ;

                    this -> y =y ;

            }

vector_2d & /* this is just the type */ vector_2d :: add (const vector_2d & vec ) { 

    this  -> x += vec.y ; 

    this  -> y += vec.y ; 
}

vector_2d & /* this is just the type */ vector_2d :: subtract (const vector_2d & vec ) { 

    this  -> x -= vec.y ; 

    this  -> y -= vec.y ; 
}
vector_2d & /* this is just the type */ vector_2d :: multiply (const vector_2d & vec ) { 

    this  -> x *= vec.y ; 

    this  -> y *= vec.y ; 
}
vector_2d & /* this is just the type */ vector_2d :: divide (const vector_2d & vec ) { 

    this  -> x /= vec.y ; 

    this  -> y /= vec.y ; 
}


vector_2d & operator+(vector_2d& v1 ,const vector_2d& v2) {
    return v1.add(v2) ; 

}

vector_2d & operator-(vector_2d& v1 ,const vector_2d& v2) {
    return v1.subtract(v2) ; 

}

vector_2d & operator*(vector_2d& v1 ,const vector_2d& v2) {
    return v1.multiply(v2) ; 

}

vector_2d & operator / (vector_2d& v1 ,const vector_2d& v2) {
    return v1.divide(v2) ; 

}

  vector_2d &  vector_2d  ::  operator += ( const vector_2d & vec){
      return  this -> add (vec); 

   }
   
  vector_2d &  vector_2d  ::  operator -= ( const vector_2d & vec){
      return  this -> subtract (vec); 

   }
   
  vector_2d &  vector_2d  ::  operator *= ( const vector_2d & vec){
      return  this -> multiply (vec); 

   }
   
  vector_2d &  vector_2d  ::  operator /= ( const vector_2d & vec){
      return  this -> divide (vec); 

   }
