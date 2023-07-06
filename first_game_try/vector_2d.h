class vector_2d  
{

public :
    float x,y  ; 
    vector_2d ();
    vector_2d ( float x , float y );
    // retutn by ref functions 
    vector_2d & add (const vector_2d & vec ) ; 
    vector_2d & subtract (const vector_2d & vec ) ;
    vector_2d & multiply (const vector_2d & vec ) ;
    vector_2d & divide   (const vector_2d & vec ) ;
    // frind functions to edit the vector_2d 
    friend vector_2d operator + (vector_2d & v1 , vector_2d & v2);
    friend vector_2d operator - (vector_2d & v1 , vector_2d & v2);
    friend vector_2d operator * (vector_2d & v1 , vector_2d & v2);
    friend vector_2d operator /  (vector_2d & v1 , vector_2d & v2);
    vector_2d &operator += ( const vector_2d & vec);
    vector_2d &operator -= ( const vector_2d & vec);
    vector_2d &operator *= ( const vector_2d & vec);
    vector_2d &operator /= ( const vector_2d & vec);
    vector_2d & operator * (const int & i );
    void operator = (const vector_2d & vec); //  
    friend bool operator != ( const vector_2d & vec1 , const vector_2d & vec2 ); 
    vector_2d & zero () ;
    }; 