#pragma once 
class vector_2d  
{

public :
    float x,y  ; 
    vector_2d ();
    vector_2d ( float x , float y );
    vector_2d & add (const vector_2d & vec ) ;

 //  vector_2d & add (const vector_2d & vec  ) ;
    vector_2d & subtract (const vector_2d & vec ) ;
    vector_2d & multiply (const vector_2d & vec ) ;
    vector_2d & divide   (const vector_2d & vec ) ;
    friend vector_2d operator + (vector_2d & v1 , vector_2d & v2);
    friend vector_2d operator - (vector_2d & v1 , vector_2d & v2);
    friend vector_2d operator * (vector_2d & v1 , vector_2d & v2);
    friend vector_2d operator /  (vector_2d & v1 , vector_2d & v2);
    vector_2d &operator += ( const vector_2d & vec);
    vector_2d &operator -= ( const vector_2d & vec);
    vector_2d &operator *= ( const vector_2d & vec);
    vector_2d &operator /= ( const vector_2d & vec);
    
    }; 