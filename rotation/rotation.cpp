vector<int> solution(vector<int> &A, int K) {
    
    if( A.size() == 0 )
    {
        return A;
    }
    
    int Km = K % A.size();
    
    if ( Km == 0 ) return A;
    
    vector<int> B;
    
    auto leftIter = A.end() - Km;
    
    while( leftIter < A.end() )
    {
        B.push_back( *leftIter );      
        leftIter += 1;
    }
    
    leftIter = A.begin();
    
    int rightEdge = A.size() - Km - 1;
    auto edgeIter = A.begin() + rightEdge;
    
    while( leftIter <= edgeIter )
    {
        B.push_back( *leftIter );
        leftIter += 1;
    }
    
    return B;
}
