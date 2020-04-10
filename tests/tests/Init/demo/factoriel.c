int main ()
{
    int a = 10 ; 
    int fact = 1 ; 
    while ( a>1)
    {
        fact = fact * (a--);
        if (a==1)
        {
            break;
        }
    }
    return fact;
}